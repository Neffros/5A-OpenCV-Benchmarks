#pragma once

#include "AQuentinSolutionStrategy.h"

struct BaseQuentinSolutionStrategy : public AQuentinSolutionStrategy
{
	SolutionBResult computeSolution(cv::Mat image) const override;
	std::string getName() const override;
};
