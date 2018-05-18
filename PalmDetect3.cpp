//
//#include "headers.hpp"
//#include "PalmTemplate.hpp"
//#include "MyCircle.hpp"
//#include "Tool.hpp"
//
//#define window "window"
//#define window_t "result"
//
//
//
//
//Mat srcImage;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//
//
//void loadTemplate(string path,vector<PalmTemplate>& templs);
//float matchMat(Mat& templ,Mat& area);
//MatchResult matchBestTemplate(Mat& areaMat,vector<PalmTemplate> templates);
//
//vector<vector<MyCircle>> computeCirclesRect(vector<Point> points,vector<MyCircle>& rects,Rect srcmat);
//set<set<int>> computeNeighbor(vector<vector<MyCircle>>& allPoints);
//
//
//float matchMat(Mat& templ,Mat& area){
//    
//    float match=0;
//    if(templ.cols==area.cols){
//        int s_count=0;
//        for(int i=0,isize=templ.rows;i<isize;i++){
//            for(int j=0,jsize=templ.cols;j<jsize;j++){
//                
//                uchar tv=templ.at<uchar>(i,j);
//                uchar ttv=area.at<uchar>(i,j);
//                
//                if(tv==ttv){
//                    s_count++;
//                }}
//        }
//        match=s_count*1.0/(templ.rows*templ.cols);
//    }
//    return  match;
//}
//
//
//void loadTemplate(string path,vector<PalmTemplate>& vectos){
//    
//    vector<string>  files=Tool::listFiles(path);
//    for(string f:files){
//        string dst=path+f;
//        Mat mat=imread(dst,CV_8UC1);
//        PalmTemplate p(dst);
//        vectos.push_back(p);
//    }
//}
//
//
//
//MatchResult matchBestTemplate(Mat& areaMat,vector<PalmTemplate> templates){
//    
//    
//    MatchResult bestmatch(0.0f,templates.at(0));
//    
//    for(int i=0,isize=(int)templates.size();i<isize;i++){
//        
//        PalmTemplate ptempl=templates.at(i);
//        
//        Size  tsize=ptempl.mat.size();
//        
//        Mat resetMat;
//        
//        resize(areaMat, resetMat, tsize);
//        
//        float t_match= matchMat(resetMat, ptempl.mat);
//        if(t_match>bestmatch.matchPercent){
//            
//            bestmatch.matchPercent=t_match;
//            bestmatch.palmTemplate=ptempl;
//        }
//        
//    }
//    
//    
//    return bestmatch;
//}
//
////============================================================================
//vector<vector<MyCircle>> computeCirclesRect(vector<Point> points,vector<MyCircle>& srcPointCircle,Rect areaLocationRect){
//    
//    float rw=15.0f;
//    
//    for(int i=0,isize=(int)points.size();i<isize;i++){
//        
//        Point p=points.at(i);
//        
//        //离底部太近的点不要
//        if(p.y>(areaLocationRect.y+areaLocationRect.height*0.6)){
//            continue;
//        }
//        
//        
//        MyCircle circle(rw,p);
//        srcPointCircle.push_back(circle);
//        
//        
//    }
//    
//    vector<vector<MyCircle>> classCircle(srcPointCircle.size());
//    
//    
//    for(int i=0,isize=(int)srcPointCircle.size();i<isize;i++){
//        
//        MyCircle rootCircle=srcPointCircle.at(i);
//        
//        classCircle.at(i).push_back(rootCircle);
//        
//        for(int j=0,jsize=isize;j<jsize;j++){
//            
//            if(i!=j){
//                
//                MyCircle s2Circle=srcPointCircle.at(j);
//                
//                if(rootCircle.containsPoint(s2Circle.p)){
//                    
//                    classCircle.at(i).push_back(s2Circle);
//                }
//                
//            }
//            
//            
//        }
//        
//        
//    }
//    
//    
//    
//    
//    return classCircle;
//    
//    
//}
//
//
//bool cmparePoints(vector<MyCircle> p1s,vector<MyCircle> p2s){
//    
//    bool eq=false;
//    
//    if(p1s.size()!=p2s.size()){
//        eq=false;
//    }else{
//        
//        int eqcount=0;
//        
//        for(int i=0,isize=(int)p1s.size();i<isize;i++){
//            
//            
//            MyCircle p1=p1s.at(i);
//            
//            for(int j=0,jsize=(int)p2s.size();j<jsize;j++){
//                
//                MyCircle p2=p2s.at(j);
//                if(p1.p.x==p2.p.x && p1.p.y==p2.p.y){
//                    eqcount++;
//                    break;
//                }
//                
//            }
//            
//        }
//        
//        if(eqcount==p1s.size()){
//            
//            eq=true;
//        }
//        
//    }
//    
//    return eq;
//}
//
//set<set<int>>  computeNeighbor(vector<vector<MyCircle>>& allPoints){
//    
//    
//    
//    
//    set<set<int>> cSet;
//    
//    for(int i=0,isize=(int)allPoints.size();i<isize;i++){
//        
//        vector<MyCircle> xpoints=allPoints.at(i);
//        
//        for(int j=0,jsize=(int)allPoints.size();j<jsize;j++){
//            
//            if(i!=j){
//                vector<MyCircle> xpoints2=allPoints.at(j);
//                bool isEq=  cmparePoints(xpoints2,xpoints);
//                
//                if(isEq){
//                    
//                    bool findLocate=false;
//                    
//                    for(set<int> ss:cSet){
//                        
//                        if( ss.find(i)==ss.end() && ss.find(j)==ss.end()){
//                            findLocate=false;
//                            
//                        }else if(ss.find(j)!=ss.end() || ss.find(i)!=ss.end()){
//                            ss.insert(i);
//                            ss.insert(j);
//                            findLocate=true;
//                            break;
//                        }
//                        
//                    }
//                    
//                    if(findLocate==false){
//                        set<int> oldset;
//                        oldset.insert(i);
//                        oldset.insert(j);
//                        cSet.insert(oldset);
//                    }
//                    
//                }
//                
//            }
//        }
//    }
//    
//    //找到所以后，计算中点
//    
//    //    for(set<int> s:cSet){
//    //
//    //        float sx,sy;
//    //
//    //        for(int i:s){
//    //
//    //            allPoints.at(i);
//    //
//    //        }
//    //
//    //    }
//    //
//    
//    
//    
//    return cSet;
//}
//
//
////使用模版匹配法监测shouzhang=====================================================
//
//float minMatch=0.7f;
//int main()
//{
//    
//    vector<PalmTemplate> temps;
//    
//    loadTemplate("/Users/wangzy/study/c20/", temps);
//    
//    cout<<temps.size()<<" templates:模版加载完毕..."<<endl;
//    
//    Rect centerRIORect;
//    
//    
//    VideoCapture videoCapture(0);
//    
//    
//    
//    while(true){
//        
//        
//        
//        videoCapture>>srcImage;
//        
//        
//        if (srcImage.empty())
//            return -1;
//        
//        
//        // 构建椭圆模型
//        Mat skinMat = Mat::zeros(cv::Size(256, 256), CV_8UC1);
//        
//        ellipse(skinMat, Point(113, 155.6), Size(23.4, 15.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);
//        // 结构元素定义
//        
//        Mat YcrcbMat;
//        Mat tempMat = Mat::zeros(srcImage.size(), CV_8UC1);
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
//        
//        
//        imshow(window, srcImage);
//        imshow(window_t, tempMat);
//        
//        
//        char key=waitKey(300);
//        
//        if(27==key){
//            break;
//        }
//    }
//    
//    
//    return 0;
//}
//
//
//
//
//
//
