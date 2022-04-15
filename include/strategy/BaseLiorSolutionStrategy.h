#pragma once

#include "ALiorSolutionStrategy.h"

struct BaseLiorSolutionStrategy : public ALiorSolutionStrategy
{
	SolutionAResult execute(cv::Mat image) const override;
};
