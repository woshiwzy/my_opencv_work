


class MyCircle{
    
public:
    
    float r;
    Point p;
    
    MyCircle(float r,Point p);
     MyCircle();
    bool containsPoint(Point p);
    
};


MyCircle::MyCircle(float r,Point p){
    
    this->r=r;
    this->p=p;
}

MyCircle::MyCircle(){
    
    this->r=0;
    this->p=Point(0,0);
}



bool MyCircle::containsPoint(Point pt){
    
    float xx=(pt.x-p.x)*(pt.x-p.x)+(pt.y-p.y)*(pt.y-p.y);
    float d=sqrt(xx);
    if(d<=r){
        return true;
    }else{
        return false;
    }
};
