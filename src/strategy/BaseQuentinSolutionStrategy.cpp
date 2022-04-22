#include "../../include/strategy/BaseQuentinSolutionStrategy.h"
#include "../../OpenCV_Poker/src/Main.h"

SolutionBResult BaseQuentinSolutionStrategy::computeSolution(const cv::Mat& image) const
{
	return solB::compute(image);
}

std::string BaseQuentinSolutionStrategy::getName() const
{
	return "Base Quentin Solution Strategy";
}
