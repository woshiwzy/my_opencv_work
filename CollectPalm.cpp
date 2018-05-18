//#include "headers.hpp"
//#include "Tool.hpp"
//
//Mat input_image;
//Mat output_mask;
//Mat output_image;
//Mat mask;
//
//bool isPress=false;
//Point lastPoint(-1,-1);
//
//
//
//
//void on_MouseHandle(int event,int x,int y,int flags,void* param);
//
//
//vector<Rect> plams;
//
//int main()
//{
//    VideoCapture cam(0);
//    
//    if(!cam.isOpened())
//        return 0;
//    
//    
//    
//    
//    RNG rng(12345);
//    
//    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//    
//    while(true)
//    {
//        
//        
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
//        
//        Mat struElmen = getStructuringElement(MORPH_RECT,Size(3, 3), Point(-1, -1));
//        morphologyEx(output_mask, output_mask, cv::MORPH_CLOSE, struElmen);
//        // 定义轮廓参数
//        vector< vector<Point> > contours;
//        vector< vector<Point> > resContours;
//        vector< Vec4i > hierarchy;
//        
//        
//        Mat contoursMat=  Mat(output_mask.size(), output_mask.type());
//        
//        // 连通域查找
//        findContours(output_mask, contours, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//        
//        plams.clear();
//        
//        for (size_t i = 0; i < contours.size(); i++)
//        {
//            
//              Rect rect=boundingRect(contours.at(i));
//              if ((rect.width>100&& rect.height>100) &&(rect.width<rect.height*1.15)){
//                Tool::drawRectangle(contoursMat, rect);
//
//                plams.push_back(rect);
//            }
//            
//        }
//        
//        
//        
//        imshow("p", output_mask);
//        imshow("p-con", contoursMat);
//        
//        setMouseCallback("p-con", on_MouseHandle,&contoursMat);
//        
//        
//        if(27 == waitKey(30))
//            return 0;
//    }
//    return 0;
//}
//
//
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
//                    
//                    Point point(x,y);
//                    
//                    for(Rect r:plams){
//                    
//                        if(r.contains(point)){
//                        
//                            imshow("x", output_mask(r));
//                            
//                        }
//                        
//                    }
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
//
//            break;
//
//        case EVENT_LBUTTONUP:
//            isPress=false;
//            break;
//    }
//
//}
