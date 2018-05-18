//
//#include <iostream>	// for standard I/O
//#include <string>   // for strings
//#include <iomanip>  // for controlling float print precision
//#include <sstream>  // string to number conversion
//
//#include "headers.hpp"
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char *argv[])
//{
//    int delay = 1;
//    char c;
//    int frameNum = -1;			// Frame counter
//    bool lastImgHasHand=false;
//    
//    int previousX=0;
//    int previousY=0;
//    
//    
//    VideoCapture videoCapture(0);
//    
//    //Size refS = Size( (int) captRefrnc.get(CV_CAP_PROP_FRAME_WIDTH),
//    //	(int) captRefrnc.get(CV_CAP_PROP_FRAME_HEIGHT) );
//    
//    bool bHandFlag = false;
//    
//    const char* WIN_SRC = "Source";
//    const char* WIN_RESULT = "Result";
//    
//    // Windows
//    namedWindow(WIN_SRC, CV_WINDOW_AUTOSIZE );
//    namedWindow(WIN_RESULT, CV_WINDOW_AUTOSIZE);
//    
//    Mat frame;	// 输入视频帧序列
//    Mat frameHSV;	// hsv空间
//    Mat mask(frame.rows, frame.cols, CV_8UC1);	// 2值掩膜
//    Mat dst(frame);	// 输出图像
//    
//    // 	Mat frameSplit[4];
//    
//    vector< vector<Point> > contours;	// 轮廓
//    vector< vector<Point> > filterContours;	// 筛选后的轮廓
//    vector< Vec4i > hierarchy;	// 轮廓的结构信息
//    vector< Point > hull;	// 凸包络的点集
//    
//    bool movement=false;
//    int count=0;
//    
//    int presentX=0;
//    int presentY=0;
//    
//    while(true) //Show the image captured in the window and repeat
//    {
//        //captRefrnc >> frame;
//        int minX=320;//屏幕的一半
//        int maxX=240;
//        int minY=320;
//        int maxY=240;
//        
//        videoCapture>>frame;
//        
//        if( frame.empty() )
//        {
//            cout << " < < <  Game over!  > > > ";
//            break;
//        }
//        imshow( WIN_SRC, frame);
//        
//        // Begin
//        
//        // 中值滤波，去除椒盐噪声
//        medianBlur(frame, frame, 5);
//        cvtColor( frame, frameHSV, CV_BGR2HSV );
//        
//        Mat dstTemp1(frame.rows, frame.cols, CV_8UC1);
//        Mat dstTemp2(frame.rows, frame.cols, CV_8UC1);
//        // 对HSV空间进行量化，得到2值图像，亮的部分为手的形状
//        inRange(frameHSV, Scalar(0,30,30), Scalar(40,170,256), dstTemp1);
//        inRange(frameHSV, Scalar(156,30,30), Scalar(180,170,256), dstTemp2);
//        bitwise_or(dstTemp1, dstTemp2, mask);
//        //	inRange(frameHSV, Scalar(0,30,30), Scalar(180,170,256), dst);
//        
//        // 形态学操作，去除噪声，并使手的边界更加清晰
//        Mat element = getStructuringElement(MORPH_RECT, Size(3,3));
//        erode(mask, mask, element);
//        morphologyEx(mask, mask, MORPH_OPEN, element);
//        dilate(mask, mask, element);
//        morphologyEx(mask, mask, MORPH_CLOSE, element);
//        frame.copyTo(dst, mask);
//        contours.clear();
//        hierarchy.clear();
//        filterContours.clear();
//        // 得到手的轮廓
//        findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//        // 去除伪轮廓
//        
//        for (size_t i = 0; i < contours.size(); i++)
//        {
//            //	approxPolyDP(Mat(contours[i]), Mat(approxContours[i]), arcLength(Mat(contours[i]), true)*0.02, true);
//            if (fabs(contourArea(Mat(contours[i]))) > 30000)	//判断手进入区域的阈值
//            {
//                filterContours.push_back(contours[i]);
//            }
//        }
//        // 画轮廓
//        if(filterContours.size()>0)
//        {
//            
//            count++;
//            lastImgHasHand=true;
//            drawContours(dst, filterContours, -1, Scalar(255,0,255), 3/*, 8, hierarchy*/);
//            
//            for (size_t j=0; j<filterContours.size(); j++)
//            {
//                convexHull(Mat(filterContours[j]), hull, true);
//                int hullcount = (int)hull.size();
//                for (int i=0; i<hullcount-1; i++)
//                {
//                    line(dst, hull[i+1], hull[i], Scalar(255,255,255), 2, CV_AA);//白色
//                    printf("num%d:x=%d\ty=%d\t\n",i,hull[i].x,hull[i].y);
//                    if(hull[i].x>maxX)
//                        maxX=hull[i].x;
//                    if(hull[i].x<minX)
//                        minX=hull[i].x;
//                    if(hull[i].y>maxY)
//                        maxY=hull[i].y;
//                    if(hull[i].y<minY)
//                        minY=hull[i].y;
//                    printf("miniX=%d\tminiY=%d\tmaxX=%d\tmaxY=%d\t\n",minX,minY,maxX,maxY);
//                    
//                }
//                
//                line(dst, hull[hullcount-1], hull[0], Scalar(0,255,0), 2, CV_AA);//绿色，最后一条
//                
//                if(count==1)//第一个轮廓的中心位置存在全局变量中，到最后一个再跟它比。
//                {
//                    previousX=(minX+maxX)/2;
//                    printf("previousX=%d\n",previousX);
//                    previousY=(minY+maxY)/2;
//                    printf("previousY=%d\n",previousY);
//                }
//                else
//                {
//                    presentX=(minX+maxY)/2;
//                    presentY=(minY+maxY)/2;
//                }
//            }
//        }
//        else
//        {	
//            if(lastImgHasHand==true)
//            {
//                if((previousX-presentX)<0)//中文的大括号和英文的大括号用肉眼看不出来，坑啊
//                {
//                    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<left\n");//镜像，没有flip过来，所以这里注意点。
////                    keybd_event(VK_LEFT,(BYTE)0, 0 ,0);
////                    keybd_event(VK_LEFT, (BYTE)0, KEYEVENTF_KEYUP,0);
//                }
//                if((previousX-presentX)>0)
//                {
//                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>right\n");
////                    keybd_event(VK_RIGHT,(BYTE)0, 0 ,0);
////                    keybd_event(VK_RIGHT, (BYTE)0, KEYEVENTF_KEYUP,0);
//                }
//                if((previousY-presentY)<0)
//                {
//                    printf("downVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n");
//                }
//                if((previousY-presentY)>0)
//                {
//                    printf("upAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
//                }
//                
//                count=0;
//                lastImgHasHand=false;
//            }
//        }
//        
//        imshow(WIN_RESULT, dst);
//        dst.release();
//        
//        
//        printf("previousX=%d\tpresentX=%d\tpreviousY=%d\tpresentY=%d\n",previousX,presentX,previousY,presentY);
//        printf("count=%d\n",count);
//        // End
//        c = cvWaitKey(1);
//        if (c == 27) 
//            break;
//    }
//}
