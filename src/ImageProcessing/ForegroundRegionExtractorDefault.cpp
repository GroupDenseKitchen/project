#include "ForegroundRegionExtractorDefault.hpp"

namespace image_processing
{
    ForegroundRegionExtractorDefault::ForegroundRegionExtractorDefault() {

    }

    ForegroundRegionExtractorDefault::~ForegroundRegionExtractorDefault() {

    }

    bool ForegroundRegionExtractorDefault::initialize(configuration::ConfigurationManager &settings)
    {
        isInitialized = true;

        CONFIG(settings, minimalArea, "minimalArea", 2500);

        return isInitialized;
    }

    void ForegroundRegionExtractorDefault::process(FrameList &frames) {

        for(CameraObject & camera : frames.getCurrent().getCameras())
        {
            if(!camera.hasImage("foregroundMask"))
            {
                LOG("ImageProcessing Error", "Image \"foregroundMask\" not set in current frame!");
                return;
            }

<<<<<<< HEAD
            cv::namedWindow("boundingboxes");           // Debug
            cv::Mat raw = camera.getImage("rawImage");  // Debug
=======
        //cv::namedWindow("boundingboxes");           // Debug
        cv::Mat raw = camera.getImage("rawImage");  // Debug
>>>>>>> origin/master

            foregroundMask = camera.getImage("foregroundMask");
            contours.clear();
            // TODO: is clone() necessary!?
            cv::findContours(foregroundMask.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
            for(unsigned int c = 0; c < contours.size(); c++)
            {
                cv::Rect rectangle = cv::boundingRect(contours[c]);
                if(rectangle.height * rectangle.width >= minimalArea)
                {
                    camera.objects.push_back(Object(rectangle));
                    cv::rectangle(raw, camera.objects.back().boundingBox, cv::Scalar(0,0,255), 2);               // Debug
                }
            }
            cv::imshow("boundingboxes", raw);     // Debug
        }
<<<<<<< HEAD
=======
        //cv::imshow("boundingboxes", raw);     // Debug


>>>>>>> origin/master
    }
}
