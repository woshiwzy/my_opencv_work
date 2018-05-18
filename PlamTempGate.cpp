//
//#include "headers.hpp"
//
//#include "Tool.hpp"
//
//#define window "palm"
//
//Point lastPoint(-1,-1);
//bool isPress=false;
//
//Mat srcImage;
//Mat tempMat;
//
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//
//
//  Rect rect;
//
//void on_MouseHandle(int event,int x,int y,int flags,void* param);
//float minMatch=0.7f;
//bool spacePressed=false;
//
//int main()
//{
//    
//    vector<Mat> temps;
//    
//    
//    cout<<temps.size()<<" templates:"<<endl;
//    
//    Rect centerRIORect;
//    
//    
//    VideoCapture videoCapture(0);
//    
//    
//    while(true){
//        
//        
//        char key=waitKey(300);
//        
//        
//        if(27==key){
//            break;
//        
//        }
//        
//        
////        if(32==key){
////            spacePressed=!spacePressed;
////        }
//       
////        if(spacePressed){
////            continue;
////        }
//        
//        
//        videoCapture>>srcImage;
//        
//        
//        if (srcImage.empty())
//            return -1;
//        
//        
//        
//        // 构建椭圆模型
//        Mat skinMat = Mat::zeros(cv::Size(256, 256), CV_8UC1);
//        
//        ellipse(skinMat, Point(113, 155.6), Size(23.4, 15.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);
//        // 结构元素定义
//        
//        Mat YcrcbMat;
//        tempMat = Mat::zeros(srcImage.size(), CV_8UC1);
//        // 颜色空间转换YCrCb
//        cvtColor(srcImage, YcrcbMat, CV_BGR2YCrCb);
//        // 椭圆皮肤模型检测
//        for (int i = 0; i < srcImage.rows; i++)
//        {
//            uchar* p = (uchar*)tempMat.ptr<uchar>(i);
//            Vec3b* ycrcb = (Vec3b*)YcrcbMat.ptr<Vec3b>(i);
//            for (int j = 0; j < srcImage.cols; j++)
//            {
//                // 颜色判断
//                if (skinMat.at<uchar>(ycrcb[j][1], ycrcb[j][2]) > 0)
//                    p[j] = 255;
//            }
//        }
//        // 形态学闭操作
//        Mat struElmen = getStructuringElement(MORPH_RECT,Size(3, 3), Point(-1, -1));
//        morphologyEx(tempMat, tempMat, cv::MORPH_CLOSE, struElmen);
//    
//        
//        Tool::drawRectangle(tempMat, rect);
//      
//        
//        imshow(window, tempMat);
//        
//        
//        if(32==key){
//            
//            char buffer[128];
//            sprintf(buffer, "/Users/wangzy/study/temp_l/%ld.png", Tool::getTimeLabel());
//            
//            imwrite(string(buffer), tempMat(rect));
//            cout<<"save:"<<string(buffer)<<endl;
//            
//        }
//        
//        setMouseCallback(window, on_MouseHandle,&tempMat);
//        
//        
//     
//    }
//    
//    
//    return 0;
//}
//
//void on_MouseHandle(int event,int x,int y,int flags,void* param){
//    
//    
//   
//    
//    switch (event) {
//            
//        case EVENT_MOUSEMOVE:
//            
//            if(lastPoint.x==-1){
//                lastPoint.x=x;
//                lastPoint.y=y;
//            }else{
//                
//                if(isPress){
//                    
//                    Point nowPoint(x,y);
//                    
//                    
////                    line(tempMat, lastPoint, nowPoint, Scalar(255, 0, 0), 5);
//                    
//                    rect.width=nowPoint.x-lastPoint.x;
//                    rect.height=nowPoint.y-lastPoint.y;
//                   
////                    Tool::drawRectangle(tempMat, rect);
//                    
//                    
//                    
//                    
////                    imshow(window, tempMat);
//                    
//                  
//                }
//                
//            }
//            
//            break;
//            
//        case EVENT_LBUTTONDOWN:
//            isPress=true;
//            
//            rect.x=x;
//            rect.y=y;
//            
//            lastPoint.x=x;
//            lastPoint.y=y;
//            
//            
//            
//            break;
//            
//        case EVENT_LBUTTONUP:
//            isPress=false;
//            break;
//    }
//    
//}
//
