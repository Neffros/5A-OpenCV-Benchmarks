#include "../../include/strategy/BaseQuentinSolutionStrategy.h"
#include "../../OpenCV_Poker/src/Main.h"

SolutionBResult BaseQuentinSolutionStrategy::computeSolution(cv::Mat image) const
{
	return solB::compute(image);
}
