
//
// Created by yangzt on 2021/5/27.
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

/*
 * The size of Yanmar lodging data is 1280 * 720
 * Hence the inner matrix should be adjusted
 *
 *
 * */

image_transport::Publisher image_pub;
ros::Publisher pointcloud_pub;

//  K matrix in lingang and gaoyou
const double camera_fx = 615.372;
const double camera_fy = 615.312;
const double camera_cx = 232.171;
const double camera_cy = 232.171;

// K matrix in Yanmar lodging data
const double camera_fx_yanmar = 2.0 * camera_fx;
const double camera_fy_yanmar = 1.5 * camera_fy;
const double camera_cx_yanmar = 2.0 * camera_cx;
const double camera_cy_yanmar = 1.5 * camera_cy;

using namespace std;
using namespace cv;
void boud_RGBD(const sensor_msgs::ImageConstPtr& rgbimg,const sensor_msgs::ImageConstPtr& depthimg);
void transform_to_pointcloud(Mat& rgb,Mat& depth,pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloudin);

int main(int argc, char** argv){
    ros::init(argc,argv,"simple_test");
    ros::NodeHandle nh;
    image_transport::ImageTransport transport(nh);
    image_pub= transport.advertise("/boud_depth", 1);

    message_filters::Subscriber<sensor_msgs::Image> rgb_sub(nh, "/device_0/sensor_1/Color_0/image/data", 1);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub(nh, "/device_0/sensor_0/Depth_0/image/data", 1);
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> sync_pol;
    message_filters::Synchronizer<sync_pol> sync(sync_pol(10), rgb_sub,depth_sub);
    sync.registerCallback(boost::bind(&boud_RGBD,_1,_2));
    pointcloud_pub = nh.advertise<sensor_msgs::PointCloud2>("height_depth", 1000);

    ros::spin();
    return 0;
}

void boud_RGBD(const sensor_msgs::ImageConstPtr& rgbimg,const sensor_msgs::ImageConstPtr& depthimg){
    //图像预处理，深度信息,颜色信息
    Mat depth_raw;
    cv_bridge::CvImageConstPtr cv_ptrdepth;
    cv_ptrdepth = cv_bridge::toCvShare(depthimg);
    depth_raw = cv_ptrdepth->image;
    //
//    cv::imshow("Depth Image", depth_raw);

    Mat rgb;
    cv_bridge::CvImageConstPtr cv_ptrrgb;
    cv_ptrrgb = cv_bridge::toCvShare(rgbimg);
    rgb = cv_ptrrgb->image;
    //
    cv::imshow("Rgb img", rgb);
    cv::waitKey(1);

    Mat depth(depth_raw.size(),CV_16UC1);
    for(int row=0;row<rgb.rows;row++){
        for(int col=0;col<rgb.cols;col++ ) {
            float z = float(depth_raw.at<float>(row, col)) * 1000;
            depth.at<ushort>(row, col) = z;
            cout<<z<<endl;

            Vec3b temp = rgb.at<Vec3b>(row, col);
            rgb.at<Vec3b>(row, col)[0] = temp[2];
            rgb.at<Vec3b>(row, col)[2] = temp[0];
        }
    }
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudIn;
//    transform_to_pointcloud(rgb, depth, cloudIn);

//    waitKey(1);
}

void transform_to_pointcloud(Mat& rgb,Mat& depth,pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloudin)
{
    cloudin->header.frame_id="/frame";
    pcl::PointXYZRGB Point;
    for(int row=0;row<rgb.rows;row++)
        for(int col=0;col<rgb.cols;col++ )
        {
            float z = float(depth.at<ushort>(row,col))/1000;
            float y = (row - camera_cy_yanmar) * z / camera_fy_yanmar;
            float x = (col - camera_cx_yanmar) * z / camera_fx_yanmar;

//            if(y>0 && z<10)  //根据相机坐标系,只选择向下的点云,z方向十米以内的点云;
            if(true)
            {
                Point.x=x;
                Point.y=y;
                Point.z=z;
                Point.b=rgb.ptr<uchar>(row)[col*3];
                Point.g=rgb.ptr<uchar>(row)[col*3+1];
                Point.r=rgb.ptr<uchar>(row)[col*3+2];
                cloudin->points.push_back(Point);
            }
        }
    pointcloud_pub.publish(cloudin);
}
