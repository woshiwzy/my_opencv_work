//#include "headers.hpp"
//#include "Tool.hpp"
//
//Mat input_image;
//Mat output_mask;
//Mat output_image;
//Mat mask;
//
//
//
//
//
//int main()
//{
//    VideoCapture cam(0);
//    
//
////    cap.set(CV_CAP_PROP_POS_FRAMES, number_of_frames);
//    
//    if(!cam.isOpened())
//        return 0;
//    
//    
//   
//    
//    double fps;
//    char fpst[32];  // 用于存放帧率的字符串
//    double t = 0;
//
//    RNG rng(12345);
//    
//    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//    
//    while(true)
//    {
//        
//        t = (double)cv::getTickCount();//帧率开始
//        
//        cam >> input_image;
//        
//        flip(input_image, input_image, 1);
//        
//        if(input_image.empty())
//            return 0;
//        
//        
//
//        
//        output_mask = Mat::zeros(input_image.size(), CV_8UC1);
//     
//        Tool::getSkinOutput(input_image, output_mask);
//        
//        
//        vector< vector<Point> > contours;   // 轮廓
//        vector< vector<Point> > filterContours; // 筛选后的轮廓
//        vector< Vec4i > hierarchy;    // 轮廓的结构信息
//        contours.clear();
//        hierarchy.clear();
//        filterContours.clear();
//        
//        findContours(output_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//        
//        vector<vector<Point>> hull(contours.size());
//        // 去除伪轮廓
//        for (size_t i = 0; i < contours.size(); i++)
//        {
//            
//            Rect r=boundingRect(contours[i]);
//            
//            float whs=r.width*1.0f/r.height;
//            
//            long abs=fabs(contourArea(Mat(contours[i]))) ;
//            
//            int ow=output_mask.cols;
//            int oh=output_mask.rows;
//            
//            
//            if(
//               (r.width>100 && r.height>100)&&
////               (r.height<oh/2)&&
//               (whs>=0.5f && whs<=1.6f)&&
//               (abs> 1000)){
//                
//                
//                
//                
////                convexHull( Mat(contours[i]), hull[i], false );
//                
////                drawContours(output_mask, hull, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );//绘制轮廓
//                
//                
//                
//                filterContours.push_back(contours[i]);
//                
//                
//                Tool::drawRectangle(output_image, r);
//                Tool::drawRectangle(output_mask, r);
//                
//                
//                
//            }
//         
//        }
//        
//        output_mask.setTo(0);
//        
//        drawContours(output_mask, filterContours, -1, Scalar(255,0,0), CV_FILLED); //8, hierarchy);
//        
//        input_image.copyTo(output_image, output_mask);
//        
//        
//        //====================
//        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
//        fps = 1.0 / t;
//        sprintf(fpst, "fps:%.2f", fps);      // 帧率保留两位小数
//               //帧率结束
//        
//        Tool::drawText(Point(100,100), string(fpst), output_mask);
//        
//        
//        imshow("input image msk", output_mask);
////        imshow("input image", input_image);
//        imshow("output image", output_image);
//        
//        output_image.setTo(0);
//        if(27 == waitKey(30))
//            return 0;
//    }
//    return 0;
//}
