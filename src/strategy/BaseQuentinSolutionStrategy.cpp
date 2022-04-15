#include "../../include/strategy/BaseQuentinSolutionStrategy.h"
#include "../../OpenCV_Poker/src/Main.cpp"

SolutionBResult BaseQuentinSolutionStrategy::computeSolution(cv::Mat image) const
{
	return compute(image);
}
