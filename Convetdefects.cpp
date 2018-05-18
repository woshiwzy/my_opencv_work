////http://docs.opencv.org/doc/tutorials/imgproc/shapedescriptors/hull/hull.html
////http://www.codeproject.com/Articles/782602/Beginners-guide-to-understand-Fingertips-counting
//
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//using namespace cv;
//using namespace std;
//
//Mat src; Mat src_gray;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//
///// Function header
//void thresh_callback(int, void* );
//
///** @function main */
//int main( int argc, char** argv )
//{
//    
//    
//    VideoCapture videocapture(0);
//    
//    while(1){
//        
//        
//        /// Load source image and convert it to gray
//         videocapture>>src;
//        
//        flip(src, src, 1);
//        
//        /// Convert image to gray and blur it
//        cvtColor( src, src_gray, CV_BGR2GRAY );
//        blur( src_gray, src_gray, Size(3,3) );
//        
//        /// Create Window
//        char* source_window = "Source";
//        namedWindow( source_window, CV_WINDOW_AUTOSIZE );
//        imshow( source_window, src );
//        
//        createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
//        thresh_callback( 0, 0 );
//        
//        
//       int k= waitKey(30);
//       
//        if(k==27){
//            break;
//        }
//        
//    }
//    
//    
//
//    
//    return(0);
//}
//
///** @function thresh_callback */
//void thresh_callback(int, void* )
//{
//    Mat src_copy = src.clone();
//    Mat threshold_output;
//    vector<vector<Point> > contours;
//    vector<Vec4i> hierarchy;
//    
//    /// Detect edges using Threshold
//    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
//    
//    /// Find contours
//    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
//    
//    /// Find the convex hull object for each contour
//    vector<vector<Point> >hull( contours.size() );
//    // Int type hull
//    vector<vector<int>> hullsI( contours.size() );
//    // Convexity defects
//    vector<vector<Vec4i>> defects( contours.size() );
//    
//    for( size_t i = 0; i < contours.size(); i++ )
//    {
//        convexHull( Mat(contours[i]), hull[i], false );
//        // find int type hull
//        convexHull( Mat(contours[i]), hullsI[i], false );
//        // get convexity defects
//        convexityDefects(Mat(contours[i]),hullsI[i], defects[i]);
//        
//    }
//    
//    /// Draw contours + hull results
//    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
//    for( size_t i = 0; i< contours.size(); i++ )
//    {
//        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//        drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
//        drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
//        
//        // draw defects
//        size_t count = contours[i].size();
//        std::cout<<"Count : "<<count<<std::endl;
//        if( count < 300 )
//            continue;
//        
//        vector<Vec4i>::iterator d =defects[i].begin();
//        
//        while( d!=defects[i].end() ) {
//            Vec4i& v=(*d);
//            //if(IndexOfBiggestContour == i)
//            {
//                
//                int startidx=v[0];
//                Point ptStart( contours[i][startidx] ); // point of the contour where the defect begins
//                int endidx=v[1];
//                Point ptEnd( contours[i][endidx] ); // point of the contour where the defect ends
//                int faridx=v[2];
//                Point ptFar( contours[i][faridx] );// the farthest from the convex hull point within the defect
//                int depth = v[3] / 256; // distance between the farthest point and the convex hull
//                
//                if(depth > 20 && depth < 80)
//                {
//                    line( drawing, ptStart, ptFar, CV_RGB(0,255,0), 2 );
//                    line( drawing, ptEnd, ptFar, CV_RGB(0,255,0), 2 );
//                    circle( drawing, ptStart,   4, Scalar(255,0,100), 2 );
//                    circle( drawing, ptEnd,   4, Scalar(255,0,100), 2 );
//                    circle( drawing, ptFar,   4, Scalar(100,0,255), 2 );
//                }
//                
//                /*printf("start(%d,%d) end(%d,%d), far(%d,%d)\n",
//                 ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, ptFar.x, ptFar.y);*/
//            }
//            d++;
//        }
//        
//        
//    }
//    
//    /// Show in a window
//    namedWindow( "Hull demo", CV_WINDOW_AUTOSIZE );
//    imshow( "Hull demo", drawing );
//    //imwrite("convexity_defects.jpg", drawing);
//}
