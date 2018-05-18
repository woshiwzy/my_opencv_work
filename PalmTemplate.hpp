
#include "headers.hpp"

class PalmTemplate{
    
public:
    
    Mat mat;
    bool isLeft;
    PalmTemplate(std::string path);
    PalmTemplate();
    
};


PalmTemplate::PalmTemplate(std:: string path){
    
    std::string::size_type idx=path.find("L");
    
    if ( idx != std::string::npos )
    {
        isLeft=true;
    }else{
        isLeft=false;
    }
    
    mat=imread(path,CV_8UC1);
}

PalmTemplate::PalmTemplate(){
    
 
}



//==========

class MatchResult{
    
    
    
public:
    
    float matchPercent;
    PalmTemplate palmTemplate;
    
    MatchResult(float matchPercent,PalmTemplate palmTemplate);
    
};


MatchResult::MatchResult(float matchPercent,PalmTemplate palmTemplate){
    
    this->matchPercent=matchPercent;
    this->palmTemplate=palmTemplate;
}


//===========
