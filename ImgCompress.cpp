//
//  ImgCompress.cpp
//  OpencvDemoNew
//
//  Created by wangzy on 2018/5/9.
//  Copyright © 2018年 wangzy. All rights reserved.
//
//#include "Tool.hpp"
//using namespace std;
//using namespace cv;

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace  std;
using namespace cv;
using namespace ml;
int main(){
    
    Mat img=imread("/Users/wangzy/Desktop/test.jpg");
   
    
    int width=img.cols;
    int height=img.rows;
    
    Mat dst(height, width, img.channels());
    
    printf("img width:%d,height:%d",width,height);
    
    
    Scalar scalar(img.channels());
    
    
    

    
    imwrite("/Users/wangzy/Desktop/test_compress.jpg",img);
//
//
    vector<int> compression_params;
//
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
    compression_params.push_back(9); //在这个填入你要的图片质量
//
//
//
    imwrite("/Users/wangzy/Desktop/test_compress.jpg",img,compression_params);

    printf("==========over===========\n");
    
    return 0;
}
