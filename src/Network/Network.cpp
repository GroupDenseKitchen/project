#include "Network.hpp"

namespace network{
    Network::Network(){
        //TODO stub
    }	
    Network::~Network(){
        //TODO stub
    }
    void Network::start(void){
        //TODO stub
    }
    bool Network::hasNewFrame(){
        //TODO stub
        return false;
    }
    Frame Network::dequeFrame(){
        //TODO stub!!!
        Frame f = Frame();
        f.addRawImage(cv::Mat());
        return f;
    }
}
