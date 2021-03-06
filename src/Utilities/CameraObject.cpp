#include "CameraObject.hpp"

CameraObject::CameraObject()
{
enteredTotal = 0;
exitedTotal = 0;
queIsVisible = false;
}

CameraObject::~CameraObject()
{

}

void CameraObject::addImage(std::string tag, cv::Mat image)
{
    processHistory.push_back(ProcessHistoryEntry(tag, "TODO: time...", image));
    images[tag] = image;
}

bool CameraObject::hasImage(std::string tag)
{
    return images.find(tag) != images.end();
}

cv::Mat CameraObject::getImage(std::string tag)
{
    if(!hasImage(tag))
        LOG("Frame CameraObject Error", "No image tagged \"" << tag << "\" exist!");
    return images[tag];
}


