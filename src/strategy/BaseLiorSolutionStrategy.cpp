#include "../../include/strategy/BaseLiorSolutionStrategy.h"
#include "../../5A-OpenCV-Poker/src/Main.cpp"

SolutionAResult BaseLiorSolutionStrategy::computeSolution(cv::Mat image) const
{
	return compute(image);
}

std::string BaseLiorSolutionStrategy::getName() const
{
	return "Base Lior Solution Strategy";
}
