#include "../../include/strategy/BaseLiorSolutionStrategy.h"
#include "../../5A-OpenCV-Poker/src/Main.h"

SolutionAResult BaseLiorSolutionStrategy::computeSolution(const cv::Mat& image) const
{
	return solA::compute(image);
}

std::string BaseLiorSolutionStrategy::getName() const
{
	return "Base Lior Solution Strategy";
}
