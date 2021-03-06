//
// Created by lu on 19-5-11.
//

#ifndef ORB_DTM_DTMUNIT_H
#define ORB_DTM_DTMUNIT_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>

#include "include/ORBextractor.h"
#include "include/Vertex.h"
#include "include/triangle.h"
#include "include/delaunay.h"

using namespace std;
using namespace cv;
using namespace ORB_SLAM2;

#define sizeofEdgeMatrix 500
#define MAX_ARROR_SIZE  200
/**
 * @brief 构建DTM的基本函数
 * @param initGood_matches
 * @param mvKeys
 * @param feature
 * @return newGood_matches
 */
vector<DMatch> ComputeDTMunit(int threshold,
                              const vector<DMatch> &initGood_matches ,
                              const vector<cv::KeyPoint> &mvKeys1,
                              const vector<cv::KeyPoint> &mvKeys2,
                              cv::Mat &feature1,
                              cv::Mat &feature2 );

/**
 * @brief 获取剩余点集
 *
 * 输入
 * @param sizeofLevel             剩余点个数
 * @param good_matches
 * @param mvKeys1
 * @param mvKeys2
 * @param mDes1
 * @param mDes2
 *
 * 输出
 * @param mvKeys1_new
 * @param mvKeys2_new
 * @param mDes1_new
 * @param mDes2_new
 */
void UpdateKey(const vector<DMatch> &good_matches,
               const vector<cv::KeyPoint> &mvKeys1,
               const vector<cv::KeyPoint> &mvKeys2,
               const cv::Mat &mDes1,
               const cv::Mat &mDes2,
               vector<cv::KeyPoint> &mvKeys1_new,
               vector<cv::KeyPoint> &mvKeys2_new,
               cv::Mat &mDes1_new,
               cv::Mat &mDes2_new);

/**
 * @brief 计算两个描述子之间的汉明距离
 * @param a
 * @param b
 * @return
 */
static int DescriptorDistance(const cv::Mat &a, const cv::Mat &b);

/**
 * @brief 使用BF匹配
 * @param mDes1
 * @param mDes2
 * @return
 */
vector<DMatch> BFmatchFunc(const cv::Mat &mDes1, const cv::Mat &mDes2, int threshold);

/**
 * @brief 使用KNN匹配
 * @param mDes1
 * @param mDes2
 * @return
 */
vector<DMatch> KNNmatchFunc(cv::Mat &mDes1_, cv::Mat &mDes2_);

/**
 * @brief 封装成函数
 *
 * 输入：debugOne,mvKeys1,debugTwo,mvKeys2,control_matches
 * 输出：筛选后的匹配数目
 */
void UsingRansac(int threshold_value,
                 const cv::Mat &feature1,
                 const cv::Mat &feature2,
                 const vector<cv::KeyPoint> &mvKeys1,
                 const vector<cv::KeyPoint> &mvKeys2,
                 const cv::Mat &mDes1,
                 const cv::Mat &mDes2,
                 const vector<DMatch> &control_matches);





#endif //ORB_DTM_DTMUNIT_H
