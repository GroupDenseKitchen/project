#include "KinectHandlerOpenNi.hpp"

namespace kinect
{

KinectHandler::KinectHandler()
{
    depthWritePath = "depthStream.avi";
    colorWritePath = "colorStream.avi";
    networkWritePath = "networkStream.avi";
}

KinectHandler::~KinectHandler()
{
    std::cout << "Shutting down OpenNI" << std::endl;
    openni::OpenNI::shutdown();
}

bool KinectHandler::initialize()
{
    // ------------- Setup OpenNI ----------------------
    // Initiallize OpenNI
    openni::OpenNI::initialize();
    std::string openNIError = openni::OpenNI::getExtendedError();
    if(openNIError.empty()){
        std::cout << "Successfully initialized OpenNI" << std::endl;
    } else {
        std::cout << openNIError << std::endl;
    }

    // Look for devices
    openni::Array<openni::DeviceInfo> devices; // = new openni::Array<openni::DeviceInfo>;
    openni::OpenNI::enumerateDevices(&devices);
    nDevices = devices.getSize();

    std::cout << "Available devices: " << nDevices << std::endl;

    depthStreams = new openni::VideoStream*[nDevices];
    colorStreams = new openni::VideoStream*[nDevices];

    // If any interesting device exists
    if(nDevices > 0){
        for(int i = 0; i < nDevices; i++){

            //const char* deviceURI = openni::ANY_DEVICE;
            const char* deviceURI = devices[i].getUri();

            openni::VideoStream *depth = new openni::VideoStream;
            openni::VideoStream *color = new openni::VideoStream;

            // Try to open device
            rc = device.open(deviceURI);
            if (rc != openni::STATUS_OK)
            {
                printf("Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
                openni::OpenNI::shutdown();
                return false;
            }

            rc = depth->create(device, openni::SENSOR_DEPTH);
            if (rc == openni::STATUS_OK)
            {
                rc = depth->start();
                if (rc != openni::STATUS_OK)
                {
                    printf("Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
                    depth->destroy();
                    return false;
                }
            }
            else
            {
                printf("Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
                return false;
            }

            rc = color->create(device, openni::SENSOR_COLOR);
            if (rc == openni::STATUS_OK)
            {
                rc = color->start();
                if (rc != openni::STATUS_OK)
                {
                    printf("Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
                    color->destroy();
                    return false;
                }
            }
            else
            {
                printf("Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
                return false;
            }

            if (!depth->isValid() || !color->isValid())
            {
                printf("SimpleViewer: No valid streams. Exiting\n");
                openni::OpenNI::shutdown();
                return false;
            }

            depthStreams[i] = depth;
            colorStreams[i] = color;
        }
    } else {
        printf("Atleast 1 Kinect sensor is required for the system to start.\n");
        return false;
    }

    return true;
}

KinectFrame* KinectHandler::readFrame(int deviceId)
{
    KinectFrame* kinectFrame = new KinectFrame;
    cv::Mat cvColorImage;
    cv::Mat cvDepthImage;

    // --------- Read from VideoStream -------------

    // ------------ Depth -------------
    depthStreams[deviceId]->readFrame(&depthFrame);
    cvDepthImage = cv::Mat(depthFrame.getHeight(), depthFrame.getWidth(),
            CV_16U, (char*)depthFrame.getData());

    // The max value from the kinect sensor is somewhare around 5000
    // based on empirical experiments
    cvDepthImage.convertTo(cvDepthImage, CV_16U, 255*255/5000);
    cvDepthImage.convertTo(cvDepthImage, CV_8U, 1.0/255);
    cv::cvtColor(cvDepthImage, cvDepthImage, CV_GRAY2BGR);

    // ------------ Record Color -------------
    colorStreams[deviceId]->readFrame(&colorFrame);
    cvColorImage = cv::Mat(colorFrame.getHeight(), colorFrame.getWidth(),
            CV_8UC3, (char*)colorFrame.getData());

    cv::cvtColor(cvColorImage, cvColorImage, CV_RGB2BGR);

    kinectFrame->depthImage = cvDepthImage.clone();
    kinectFrame->bgrImage = cvColorImage.clone();

    return kinectFrame;
}

int KinectHandler::getnDevices()
{
	//TODO stub
	return nDevices;
}

} // namespace kinect
