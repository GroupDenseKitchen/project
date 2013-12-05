#ifndef BACKGROUNDMODELMOG_HPP
#define BACKGROUNDMODELMOG_HPP

#include "../Utilities/utilities.hpp"
#include "../Utilities/FrameList.hpp"
#include "../Utilities/Algorithm.hpp"

namespace image_processing
{
/*!
 *  \brief   Process step which creates binary image using OpenCV function BackgroundModelMoG2.
 */
class BackgroundModelMoG : public Algorithm
{
public:
    /*!
       \brief   Constructor.
    */
    BackgroundModelMoG();

    /*!
       \brief   Destructor.
    */
    ~BackgroundModelMoG();

    /*!
       \brief   Performs the background modulation.
    */
    void process(FrameList &frames) override;

    /*!
       \brief   Initialize the algorithm.
       \details Returns false if initialization fails,
                e.g. if a required variable is not set
    */
    bool initialize(configuration::ConfigurationManager &conf) override;

private:
    int cameraAmount;
    int nmixtures;
    int dilations;
    int erotions;
    int history;
    double backgroundRatio;
    double varThresholdGen;
    double varThreshold;
    double fVarInit;
    double fVarMin;
    double fVarMax;
    double fCT;
    double fTau;
    double learningRate;
    double downSamplingFactor;
    bool isShadowDetection;
    std::vector<cv::BackgroundSubtractorMOG2*> backgroundModels;

    void initializeBackgroundModels(int cameraAmount);
};
}

#endif
