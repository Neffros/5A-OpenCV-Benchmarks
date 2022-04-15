#pragma once

#include "ALiorSolutionStrategy.h"

struct BaseLiorSolutionStrategy : public ALiorSolutionStrategy
{
	SolutionAResult computeSolution(cv::Mat image) const override;
};
