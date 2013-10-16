#include "BackgroundModelMoG.hpp"

namespace image_processing
{

BackgroundModelMoG::BackgroundModelMoG(){

}
BackgroundModelMoG::~BackgroundModelMoG(){

}

bool BackgroundModelMoG::initialize(configuration::ConfigurationManager &settings)
{
    isInitialized = true;

    // Initialize variables
    //
    //           |VARIABLE          |NAME                  |DEFAULT
    //---------------------------------------------------------------
    CONFIG(settings, nmixtures,         "nmixtures",            5);
    CONFIG(settings, backgroundRatio,   "backgroundRatio",      0.9);
    CONFIG(settings, varThresholdGen,   "varThresholdGen",      19);
    CONFIG(settings, fVarInit,          "fVarInit",             15);
    CONFIG(settings, fCT,               "fCT",                  0.05);
    CONFIG(settings, isShadowDetection, "isShadowDetection",    false);
    CONFIG(settings, erotions,          "erotions",             3);
    CONFIG(settings, dilations,         "dilations",            3);
    CONFIG(settings, history,           "history",              500);
    //fVarMin = ;
    //fVarMax = ;
    //fTau = ;

    bg.set("history",history);
    bg.set("varThreshold",varThresholdGen);
    //bg.setBool("shadowDetection",isShadowDetection);
    bg.set("nmixtures",nmixtures);
    bg.set("backgroundRatio",backgroundRatio);

    //TODO: more parameters should be set, see above and clean it up, function should get inparameters...

    return isInitialized;
}

 void BackgroundModelMoG::process(FrameList &frames)
 {
     //TODO: loop over all cameras...
     CameraObject &camera = frames.getCurrent().getCameras().back();

     if(!camera.hasImage("rawImage"))
     {
         LOG("ImageProcessing Error", "Image \"rawImage\" not set in current frame!");
         return;
     }

     cv::Mat rawImage = camera.getImage("rawImage");
     cv::Mat foregroundMask;    // From frames (current)

     bg(rawImage,foregroundMask,0.001);
     cv::erode(foregroundMask,foregroundMask,cv::Mat(),cv::Point(-1,-1), erotions);
     cv::dilate(foregroundMask,foregroundMask,cv::Mat(),cv::Point(-1,-1), dilations);
     cv::threshold(foregroundMask,foregroundMask,230,255,CV_THRESH_BINARY);
     cv::namedWindow("binary");
     cv::imshow("binary", foregroundMask);


     camera.addImage("foregroundMask", foregroundMask);
 }

}