#include "../../include/strategy/BaseLiorSolutionStrategy.h"
#include "../../5A-OpenCV-Poker/src/Main.h"

SolutionAResult BaseLiorSolutionStrategy::computeSolution(cv::Mat image) const
{
	return solA::compute(image);
}
