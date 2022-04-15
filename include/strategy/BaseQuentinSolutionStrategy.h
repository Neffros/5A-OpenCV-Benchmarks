#pragma once

#include "AQuentinSolutionStrategy.h"

struct BaseQuentinSolutionStrategy : public AQuentinSolutionStrategy
{
	SolutionBResult execute(cv::Mat image) const override;
};
