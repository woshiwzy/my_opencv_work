
#include "headers.hpp"

class PalmTemplate{

public:
    
    Mat mat;
    bool isLeft;
    PalmTemplate(std::string path);
    
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
