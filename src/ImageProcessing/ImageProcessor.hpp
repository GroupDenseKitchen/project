#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "../Utilities/utilities.hpp"
#include "../Utilities/FrameList.hpp"
#include "../Utilities/Algorithm.hpp"

/*!
 *  \brief   Image processing contains functionality for the different
 *           states of image processing required for human detection and tracking.
 */
namespace image_processing
{
/*!
 *  \brief     The Image Processor is the interface to the image processing functionality.
 */
class ImageProcessor : public Algorithm
{
public:

    /*!
       \brief   Constructor.
    */
    ImageProcessor();

    /*!
       \brief   Destructor.
    */
    ~ImageProcessor();

    /*!
       \brief   Initialize all image processing algorithms.
       \details Returns false if any of the sub algorithms fail during their initialization.
    */
    bool initialize(configuration::ConfigurationManager & settings);

    void reset();

    /*!
       \brief   Perform all image processing algorithms in order.
    */
    void process(FrameList &frames);
};
}

#endif
