//手掌监测，手指定位


#include "headers.hpp"
#include "PalmTemplate.hpp"
#include "MyCircle.hpp"
#include "Tool.hpp"

#define window "window"
#define window_t "result"




Mat srcImage;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


void loadTemplate(string path,vector<PalmTemplate>& templs);
float matchMat(Mat& templ,Mat& area);
MatchResult matchBestTemplate(Mat& areaMat,vector<PalmTemplate> templates);

vector<vector<MyCircle>> computeCirclesRect(vector<Point> points,vector<MyCircle>& rects,Rect srcmat);
set<set<int>> computeNeighbor(vector<vector<MyCircle>>& allPoints);


float matchMat(Mat& templ,Mat& area){
    
    float match=0;
    if(templ.cols==area.cols){
        int s_count=0;
        for(int i=0,isize=templ.rows;i<isize;i++){
            for(int j=0,jsize=templ.cols;j<jsize;j++){
                
                uchar tv=templ.at<uchar>(i,j);
                uchar ttv=area.at<uchar>(i,j);
                
                if(tv==ttv){
                    s_count++;
                }}
        }
        match=s_count*1.0/(templ.rows*templ.cols);
    }
    return  match;
}


void loadTemplate(string path,vector<PalmTemplate>& vectos){
    
    vector<string>  files=Tool::listFiles(path);
    for(string f:files){
        string dst=path+f;
        Mat mat=imread(dst,CV_8UC1);
        PalmTemplate p(dst);
        vectos.push_back(p);
    }
}



MatchResult matchBestTemplate(Mat& areaMat,vector<PalmTemplate> templates){
    
    
    MatchResult bestmatch(0.0f,templates.at(0));
    
    for(int i=0,isize=(int)templates.size();i<isize;i++){
        
        PalmTemplate ptempl=templates.at(i);
        
        Size  tsize=ptempl.mat.size();
        
        Mat resetMat;
        
        resize(areaMat, resetMat, tsize);
        
        float t_match= matchMat(resetMat, ptempl.mat);
        if(t_match>bestmatch.matchPercent){
            
            bestmatch.matchPercent=t_match;
            bestmatch.palmTemplate=ptempl;
        }
        
    }
    
    
    return bestmatch;
}

//============================================================================
vector<vector<MyCircle>> computeCirclesRect(vector<Point> points,vector<MyCircle>& srcPointCircle,Rect areaLocationRect){
   
    float rw=15.0f;
    
    for(int i=0,isize=(int)points.size();i<isize;i++){
    
        Point p=points.at(i);
        
        //离底部太近的点不要
        if(p.y>(areaLocationRect.y+areaLocationRect.height*0.6)){
            continue;
        }
        
        
        MyCircle circle(rw,p);
        srcPointCircle.push_back(circle);
        
        
    }
    
    vector<vector<MyCircle>> classCircle(srcPointCircle.size());
    
    
    for(int i=0,isize=(int)srcPointCircle.size();i<isize;i++){
        
        MyCircle rootCircle=srcPointCircle.at(i);
        
        classCircle.at(i).push_back(rootCircle);
        
        for(int j=0,jsize=isize;j<jsize;j++){
            
            if(i!=j){
                
                MyCircle s2Circle=srcPointCircle.at(j);
                
                if(rootCircle.containsPoint(s2Circle.p)){
                    
                    classCircle.at(i).push_back(s2Circle);
                }
                
            }
            
            
        }
        
        
    }
    
 
    

    return classCircle;
    

}


bool cmparePoints(vector<MyCircle> p1s,vector<MyCircle> p2s){
    
    bool eq=false;
    
    if(p1s.size()!=p2s.size()){
        eq=false;
    }else{
        
        int eqcount=0;
        
        for(int i=0,isize=(int)p1s.size();i<isize;i++){
           
            
            MyCircle p1=p1s.at(i);
          
            for(int j=0,jsize=(int)p2s.size();j<jsize;j++){
                
                MyCircle p2=p2s.at(j);
                if(p1.p.x==p2.p.x && p1.p.y==p2.p.y){
                    eqcount++;
                    break;
                }
                
            }
            
        }
        
        if(eqcount==p1s.size()){
        
            eq=true;
        }
        
    }
    
    return eq;
}


/**
 计算凸包附近的点邻居点
 如果发现两个点的邻居相同（每一个点的邻居包括自己），那么删除其中一个点，因为这两个点
 聚集在一起的
 **/
set<set<int>>  computeNeighbor(vector<vector<MyCircle>>& allPoints){
    
    


    set<set<int>> cSet;
    
    for(int i=0,isize=(int)allPoints.size();i<isize;i++){
        
        vector<MyCircle> xpoints=allPoints.at(i);
        
        for(int j=0,jsize=(int)allPoints.size();j<jsize;j++){
            
            if(i!=j){
              vector<MyCircle> xpoints2=allPoints.at(j);
              bool isEq=  cmparePoints(xpoints2,xpoints);
                
              if(isEq){
                    
                    bool findLocate=false;
                    
                    for(set<int> ss:cSet){
                    
                        if( ss.find(i)==ss.end() && ss.find(j)==ss.end()){
                            findLocate=false;
                        
                        }else if(ss.find(j)!=ss.end() || ss.find(i)!=ss.end()){
                             ss.insert(i);
                             ss.insert(j);
                             findLocate=true;
                            break;
                        }
                        
                    }
                    
                    if(findLocate==false){
                        set<int> oldset;
                        oldset.insert(i);
                        oldset.insert(j);
                        cSet.insert(oldset);
                    }

                }
                
            }
        }
    }
  
    //找到所以后，计算中点
    
//    for(set<int> s:cSet){
//        
//        float sx,sy;
//        
//        for(int i:s){
//            
//            allPoints.at(i);
//            
//        }
//        
//    }
//    
    


    return cSet;
}


//使用模版匹配法监测shouzhang=====================================================
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
//        // 定义轮廓参数
//        vector< vector<Point> > contours;
//        vector< vector<Point> > resContours;
//        vector< Vec4i > hierarchy;
//        
//        
//        // 连通域查找
//        findContours(tempMat, contours, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//        
//        
//        vector<vector<Point>> hull(contours.size());
//        Mat drawing = Mat::zeros( tempMat.size(), CV_8UC3 );
//        Mat resultMat=Mat(srcImage.size(), CV_8UC1);
//        
//        bool needHull=true;
//        
//        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//        // 筛选伪轮廓
//        for (size_t i = 0; i < contours.size(); i++)
//        {
//            
//            Rect rect=boundingRect(contours.at(i));
//            
//            if((rect.height*1.0/rect.width)>2){
//                rect.height=rect.width*1.5;
//            }
//            
//            
//            if ((rect.width>100|| rect.height>100) &&(rect.width<rect.height*1.15)){
//                
//                resContours.push_back(contours[i]);
//                
//                Mat areaMat=resultMat(rect);
//                
//                
//                MatchResult matchResult =matchBestTemplate(areaMat, temps);
//                
////                cout<<"best match:"<<matchResult.matchPercent<<endl;
//                char buffer[32];
//                
//                
//                if(matchResult.matchPercent>minMatch){
//                    
//                    if(matchResult.palmTemplate.isLeft){
//                        sprintf(buffer, " left hand:%4.2f", matchResult.matchPercent);
//                    }else{
//                        sprintf(buffer, " right hand:%4.2f", matchResult.matchPercent);
//                    }
//                    
//                    
//                    if(needHull){
//                        
//                        convexHull( Mat(contours[i]), hull[i], false );
//
//                        drawContours( drawing, hull, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );//绘制轮廓
//                        
//                        vector<Point> allPoints;
//                        
//                        for(vector<Point> ppp:hull){
//                            for(Point p:ppp){
//                                allPoints.push_back(p);
////                                 Tool::drawCircle(resultMat, p, 10);
////                                Tool::drawText(p, "x", resultMat);
//                            }
//                        }
//
//                        
//                        vector<MyCircle> srcCircle;//以某点为中心的圆
//                        
//                        
//                        //寻找每一点的邻居
//                        vector<vector<MyCircle>>  nearsPoints=computeCirclesRect(allPoints,srcCircle,rect);
//                        
//                        cout<<"寻找邻居点:"<<nearsPoints.size()<<endl;
//                        
//                        //排除邻居相同的点
//                        set<set<int>> resultN=computeNeighbor(nearsPoints);
//                        
//                        if(resultN.size()==5){
//                            //                        int totalp=0;
//                            for(set<int> s:resultN){
//                                
//                                //                            totalp+=s.size();
//                                
//                                int x=*s.rbegin();
//                                Tool::drawCircle(srcImage, nearsPoints.at(x).at(0).p, 10,color,5);
//
//                            }
//                            
//                            Tool::drawRectangle(resultMat, rect,Scalar(0xff,0xaa,0xbb),5);
//                        }
//                        
//
//                        
////                        if(totalp==nearsPoints.size()){
//                        
////                            cout<<"=====***==="<<endl;
////                        }
//                        
//                        cout<<"----------------"<<endl;
//                        
//                        
//                        cout<<"resntN:"<<resultN.size()<<endl;
//
//                        
//                        
//                        cout<<"-----------------"<<endl;
//                       
//                        
//                    }
//                    
//                    Tool::drawText(Point(rect.x,rect.y), string(buffer), resultMat);
//                    Tool::drawRectangle(resultMat, rect);
//                    Tool::drawRectangle(srcImage, rect);
//
//                }
//                
//
//                
//            }
//            
//        }
//        
//        if(needHull){
//            imshow("hull", drawing);
//        }
//        
//        
//        imshow(window, srcImage);
//        imshow(window_t, resultMat);
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






