#ifndef FLOWESTIMATOR_HPP
#define FLOWESTIMATOR_HPP

#include "../Utilities/utilities.hpp"
#include "../Utilities/FrameList.hpp"
#include "../Utilities/Algorithm.hpp"

/*!
 * \brief   TODO
 * \details TODO
 */
namespace statistics
{
/*!
 * \brief   Stuct which is used for a vector with pair values, people entered in a specific frame number.
 * \details TODO
 */
struct flowVectorPair {
    flowVectorPair(int _flow,unsigned int _frameCount);
    int flow;
    unsigned int frameCount;
};

/*!
 * \brief   Stuct which is used for a vector with pair values.
 * \details TODO
 */
struct CameraFlow {
    std::vector<flowVectorPair> inFlow;
    std::vector<flowVectorPair> outFlow;
};

/*!
 * \brief   Process step which calculates the flow in  and out through the door.
 * \details TODO
 */
class FlowEstimator : public Algorithm
{ 
public:
    /*!
     * \brief   Constructor.
     */
    FlowEstimator();

    /*!
     * \brief   Destructor.
     */
    ~FlowEstimator();

    /*!
     * \brief        Performs the process step.
     * \details      TODO
     * \param frames TODO
     */
    void process(FrameList &frames);

    /*!
     * \brief      Initialize the algorithm.
     * \details    Returns false if initialization fails,
     *             e.g. if a required variable is not set.
     * \param conf TODO
     */
     bool initialize(configuration::ConfigurationManager &conf);

private:
     std::vector<CameraFlow> cameraFlowVector;//vector to separate flow for different cameras.
     bool isSetup;
};
}
#endif







