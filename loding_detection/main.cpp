#include<iostream>
#include "wavelet.h"
#include "DBSCAN.h"
#include "glcm.h"
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using namespace cv;
ros::Subscriber subRGB;
void morphologyProcess(Mat& cluster_lodging);
Mat kmeans_lodging(Mat& LH_Img);
void DBSCAN_class(Mat& cluster_lodging);
void hullcount_cal(Mat& cluster_lodging,Mat& src);

struct cmp{
    bool operator()(vector<int> & a,vector<int>& b) {
        return a.size() > b.size();
    }
};

struct cmp_convex{
    bool operator()(vector<Point> & a,vector<Point>& b) {
        return contourArea(a, false) > contourArea(b, false);
    }
};

void loding_detection_rgb (const sensor_msgs::ImageConstPtr& rgb) {
    Mat src;
    cv_bridge::CvImageConstPtr cv_ptrRGB;
    cv_ptrRGB = cv_bridge::toCvShare(rgb);
    src = cv_ptrRGB->image;
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            Vec3b temp = src.at<Vec3b>(i, j);
            src.at<Vec3b>(i, j)[0] = temp[2];
            src.at<Vec3b>(i, j)[2] = temp[0];
        }
    }
    Mat ROI=src(Rect(0,224,256,256));
    Mat clone_ROI=ROI.clone();

    std::vector<cv::Mat> rgbChannels(3);
    split(ROI, rgbChannels);//分为三个通道
    ROI=rgbChannels[1];

    //灰度共生矩阵判断是否倒伏
//    GLCM glcm;
//    Mat gray_glcm=Mat::zeros(ROI.size(),ROI.type());
//    glcm.GrayMagnitude(ROI,gray_glcm,GRAY_16);
//
//    Mat imgEnergy, imgContrast, imgHomogenity, imgEntropy;
//    glcm.CalcuTextureImages(gray_glcm, imgEnergy, imgContrast, imgHomogenity, imgEntropy, 5, GRAY_16, true);
//
//    threshold(imgEnergy, imgEnergy, 70, 255, CV_THRESH_BINARY);
//    cv::medianBlur(imgEnergy,imgEnergy,3);
//    imshow("Energy_bre", imgEnergy);
//
//    std::vector<vector<Point> > contours;
//    std::vector<Vec4i> hierarchy;
//    findContours(imgEnergy, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//    vector<Point> points;
//    vector<vector<Point> > convexs(contours.size());
//    for (size_t i = 0; i < contours.size(); i++) {
//        convexHull(Mat(contours[i]), convexs[i], false, true);
//    }
//    vector<Vec4i> empty(0);
//    for (size_t k = 0; k < contours.size(); k++) {
//        drawContours(imgEnergy, convexs, k, 255, 2, LINE_8, empty, 0, Point(0, 0));
//    }
//    int sum_GLCM_lodgingOrNot=0;
//    for(int i=0;i<convexs.size();i++)
//    {
//        sum_GLCM_lodgingOrNot+=contourArea(convexs[i], false);
//    }
//    putText(imgEnergy,to_string(sum_GLCM_lodgingOrNot),Point(50,60),FONT_HERSHEY_SIMPLEX,1,255,4,8);
//    imshow("ROI",ROI);
//    imshow("Energy", imgEnergy);

    Daubechies db(ROI);  //小波变换,LH效果较好
    db.Daub4b(ROI);

    Daubechies dbLH(db.LH_Img); //对LH图像再次小波变换
    dbLH.Daub4b(db.LH_Img);

    for (int i = 250; i < dbLH.LH_Img.rows; i++) {
        for (int j = 0; j < dbLH.LH_Img.cols; j++) {
            dbLH.LH_Img.at<uchar >(i,j)=0;
        }
    }

    cv::imshow("0LH_Img", dbLH.LH_Img);

    Mat cluster_lodging = kmeans_lodging(dbLH.LH_Img);
    cv::imshow("1cluster_lodging", cluster_lodging);

    DBSCAN_class(cluster_lodging);

    morphologyProcess(cluster_lodging);

    hullcount_cal(cluster_lodging,src);

    cv::rectangle(src, Rect(0,224,256,256), Scalar(0, 0, 255),1, LINE_8,0);
    cv::imshow("5src",src);

    waitKey(1);
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "loding_detection");
    ros::NodeHandle nh;
    subRGB = nh.subscribe<sensor_msgs::Image>("/realsense_sr300/ylx/rgb", 1, &loding_detection_rgb);
    ros::spin();
}

void morphologyProcess(Mat& cluster_lodging)
{
    for (int row = 0; row < cluster_lodging.rows; row++)
    {
        for (int col = 0; col < cluster_lodging.cols; col++)
        {
            if((int)cluster_lodging.at<uchar>(row, col)==50)
                cluster_lodging.at<uchar>(row, col)=0;
        }
    }
    cv::imshow("2dbscan", cluster_lodging);
    cv::medianBlur(cluster_lodging,cluster_lodging,3);

    cv::imshow("3cluster_lodging_median", cluster_lodging);

    cv::Mat element_close = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    morphologyEx(cluster_lodging,cluster_lodging, cv::MORPH_CLOSE, element_close);

    cv::imshow("4cluster_lodging_close", cluster_lodging);
}

//第一次聚类,kmeans
Mat kmeans_lodging(Mat& LH_Img)
{
    int width = LH_Img.cols;
    int height = LH_Img.rows;
    int dims = LH_Img.channels();
    int sampleCount = width*height;
    int clusterCount = 2;
    Mat points(sampleCount, dims, CV_32F, Scalar(10));
    Mat labels;
    Mat centers(clusterCount, 1, points.type());
    int index = 0;
    for (int row = 0; row < height; row++) {    //RGB数据转换到样本数据
        for (int col = 0; col < width; col++) {
            index = row*width + col;
            uchar bgr = LH_Img.at<uchar>(row, col);
            points.at<float>(index, 0) = static_cast<int>(bgr);
        }
    }
    //运行Kmeans
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 5, 0.01); //迭代停止条件
    kmeans(points, clusterCount, labels, criteria, 3, KMEANS_PP_CENTERS, centers);
    //显示图像分割结果，要把样本数据点转换回去

    //保证图像背景黑色
    int count_background=0;
    Mat result = Mat::zeros(LH_Img.size(),LH_Img.type());
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            index = row*width + col;
            int label = labels.at<int>(index, 0);
            if(label==1) count_background++;
        }
    }

    if(count_background > height*width/2)
    {
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                index = row*width + col;
                int label = labels.at<int>(index, 0);
                if(label==0) result.at<uchar>(row, col) = 50;
            }
        }
    }
    else
    {
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                index = row*width + col;
                int label = labels.at<int>(index, 0);
                if(label==1) result.at<uchar>(row, col) = 50;
            }
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if(int(result.at<uchar>(row, col)) != 50)
                result.at<uchar>(row, col)=0;
        }
    }
    return result;
}

//基于密度聚类
void DBSCAN_class(Mat& cluster_lodging)
{
    int n=2; double eps=10; int minPts=35;
    vector<Point_in> points;
    for (int row = 0; row < cluster_lodging.rows; row++)
    {
        for (int col = 0; col < cluster_lodging.cols; col++)
        {
            if((int)cluster_lodging.at<uchar>(row,col)==50)
                points.push_back({row,col,0,NOT_CLASSIFIED});
        }
    }
    DBCAN dbScan(n,eps,minPts,points);
    dbScan.run();

    vector<vector<int> > cluster = dbScan.getCluster();
    sort(cluster.begin(), cluster.end(),cmp());

    int row_cluster=0;int col_cluster=0;
    for(int i=0;i<cluster.size();i++)
    {
        for(int j=0;j<cluster[i].size();j++)
        {
            row_cluster=points[cluster[i][j]].x;
            col_cluster=points[cluster[i][j]].y;
            cluster_lodging.at<uchar>(row_cluster,col_cluster)=255;
        }
    }
    return;
}

//凸包检测,绘制结果图
void hullcount_cal(Mat& cluster_lodging,Mat& src)
{
    std::vector<vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours(cluster_lodging, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector<Point> points;

    vector<vector<Point> > convexs(contours.size());
    for (size_t i = 0; i < contours.size(); i++) {
        convexHull(Mat(contours[i]), convexs[i], false, true);
    }

    for (unsigned int i = 0; i < convexs.size(); i++)
    {
        if(contourArea(convexs[i], false) < 5) continue;
        for(unsigned int j=0;j<convexs[i].size();j++)
            points.push_back(convexs[i][j]);
    }
    vector<Point> convex_all;
    convexHull(Mat(points), convex_all, true);
    //如果占比过大,则可认为小波变换方差小,没有倒伏
    vector<vector<Point> > points_any; //不同凸包包含的点
    vector<vector<pair<Point,int> > > centers_any; //不同凸包所包含小凸包的中心点
    sort(convexs.begin(),convexs.end(),cmp_convex()); //按凸包面积排序

    if(contourArea(convex_all, false)/(cluster_lodging.cols*cluster_lodging.rows*1.0)<0.7)
    {
        for (unsigned int i = 0; i < convexs.size(); i++)
        {
            points.clear();
            if(contourArea(convexs[i], false) < 50) break;
            else
            {
                if(centers_any.size()==0 && contourArea(convexs[i], false) > 100)
                {
                    Point center_one;
                    pair<Point,int> center_one_index;
                    vector<pair<Point,int> > centers_one;
                    for(int j=0;j<convexs[i].size();j++)
                    {
                        center_one.x+=convexs[i][j].x;
                        center_one.y+=convexs[i][j].y;
                        points.push_back(convexs[i][j]);
                    }
                    center_one.x=center_one.x/convexs[i].size();
                    center_one.y=center_one.y/convexs[i].size();
                    center_one_index.first=center_one;
                    center_one_index.second=i;
                    centers_one.push_back(center_one_index);
                    centers_any.push_back(centers_one);
                    points_any.push_back(points);
                }
                else
                {
                    Point center_one;
                    bool flag=false;
                    pair<Point,int> center_one_index;
                    for(int j=0;j<convexs[i].size();j++)
                    {
                        center_one.x+=convexs[i][j].x;
                        center_one.y+=convexs[i][j].y;
                        points.push_back(convexs[i][j]);
                    }
                    center_one.x=center_one.x/convexs[i].size();
                    center_one.y=center_one.y/convexs[i].size();
                    for(int m=0;m<centers_any.size();m++)
                    {
                        for(int n=0;n<centers_any[m].size();n++)
                        {
                            if(sqrt( (centers_any[m][n].first.x-center_one.x) * (centers_any[m][n].first.x-center_one.x)
                                     +(centers_any[m][n].first.y-center_one.y) * (centers_any[m][n].first.y-center_one.y))
                               -sqrt(contourArea(convexs[centers_any[m][n].second], false))
                               -sqrt(contourArea(convexs[i], false)) < 0.5 )
                            {
                                flag=true;
                                for(int j=0;j<convexs[i].size();j++)
                                {
                                    points_any[m].push_back(convexs[i][j]);
                                }
                                center_one_index.first=center_one;
                                center_one_index.second=i;
                                centers_any[m].push_back(center_one_index);
                                break;
                            }
                        }
                        if(flag) break;
                    }
                    if(flag==false && contourArea(convexs[i], false) > 100)
                    {
                        center_one_index.first=center_one;
                        center_one_index.second=i;
                        vector<pair<Point,int> > centers_one;
                        centers_one.push_back(center_one_index);
                        centers_any.push_back(centers_one);
                        points_any.push_back(points);
                    }
                }
            }
        }
        vector<vector<int> >hull_cal(points_any.size());
        for(int m=0;m<points_any.size();m++)
        {
            convexHull(Mat(points_any[m]), hull_cal[m], true);

            int hullcount = (int)hull_cal[m].size();//凸包的边数
            Point point0 = points_any[m][hull_cal[m][hullcount - 1]]; //连接凸包边的坐标点
            point0.y=point0.y+224;
            //绘制凸包的边
            for (int i = 0; i < hullcount; i++)
            {
                Point point = points_any[m][hull_cal[m][i]];
                point.y=point.y+224;
                line(src, point0, point, Scalar(255, 255, 100), 2, LINE_AA);
                point0 = point;
            }
        }

        for(int i=0;i<convexs.size();i++)
        {
            for(int j=0;j<convexs[i].size();j++)
                convexs[i][j].y+=224;
        }

        vector<Vec4i> empty(0);
        for (size_t k = 0; k < contours.size(); k++) {
            drawContours(src, convexs, k, Scalar(100, 255, 100), 2, LINE_8, empty, 0, Point(0, 0));
        }
    }
}



