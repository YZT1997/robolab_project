//
// Created by yangzt on 2021/8/26.
//
#include <iostream>
#include <string.h>
#include <pcl/point_types.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointField.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <Eigen/Core>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/surface/mls.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <pcl/kdtree/kdtree_flann.h>

#include <pcl/filters/extract_indices.h>

using namespace std;
using namespace cv;

ros::Publisher pointcloud_pub;

void rgb_depth_sub(const sensor_msgs::ImageConstPtr& rgbimg,const sensor_msgs::ImageConstPtr& depthimg){
    //图像预处理,rgb,depth信息
    Mat depth_raw;
    cv_bridge::CvImageConstPtr cv_ptrdepth;
    cv_ptrdepth = cv_bridge::toCvShare(depthimg);
    depth_raw = cv_ptrdepth->image;

    Mat rgb;
    cv_bridge::CvImageConstPtr cv_ptrrgb;
    cv_ptrrgb = cv_bridge::toCvShare(rgbimg);
    rgb = cv_ptrrgb->image;

    Mat depth(depth_raw.size(),CV_16UC1);
    for(int row=0;row<rgb.rows;row++){
        for(int col=0;col<rgb.cols;col++ ) {
            float z = float(depth_raw.at<float>(row, col)) * 1000; //深度图之前是32FC1编码
            depth.at<ushort>(row, col) = z;  //转成16位编码

            Vec3b temp = rgb.at<Vec3b>(row, col);
            rgb.at<Vec3b>(row, col)[0] = temp[2];
            rgb.at<Vec3b>(row, col)[2] = temp[0];
        }
    }

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudin (new pcl::PointCloud<pcl::PointXYZRGB>);

    // Transform to point cloud;
    cloudin->header.frame_id="/frame";
    pcl::PointXYZRGB Point;
    for(int row=0;row<rgb.rows;row+=1) {
        //row,col这里做了稀疏化,就不用滤波稀疏了
        for(int col=0;col<rgb.cols ;col+=1){
            float z = float(depth.at<ushort>(row,col))/1000;
            float y = (row - 232.171) * z / 615.312;
            float x = (col - 323.844) * z / 615.372;
//            // For Vzense Camera
//            float z = float(depth.at<ushort>(row,col))/1000;
//            float y = (row - 245.039) * z / 710.304;
//            float x = (col - 330.582) * z / 707.547;

            //            if(y>0 && z<10)  //根据相机坐标系,只选择向下的点云,z方向十米以内的点云;
            if(z < 10.0f){
                Point.x=x;
                Point.y=y;
                Point.z=z;
                Point.b=rgb.ptr<uchar>(row)[col*3];
                Point.g=rgb.ptr<uchar>(row)[col*3+1];
                Point.r=rgb.ptr<uchar>(row)[col*3+2];
                cloudin->points.push_back(Point);
            }


        }
    }
    pointcloud_pub.publish(cloudin);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "point_cloud");
    ros::NodeHandle nh;
    pointcloud_pub = nh.advertise<sensor_msgs::PointCloud2>("/pointcloud", 1000);

    //同步接收rgb,depth
    message_filters::Subscriber<sensor_msgs::Image> rgb_sub(nh, "/realsense_sr300/ylx/rgb", 1);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub(nh, "/realsense_sr300/ylx/depth", 1);
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> sync_pol;
    message_filters::Synchronizer<sync_pol> sync(sync_pol(10), rgb_sub,depth_sub);

    sync.registerCallback(boost::bind(&rgb_depth_sub, _1, _2));
    ros::spin();
    return 0;

}
