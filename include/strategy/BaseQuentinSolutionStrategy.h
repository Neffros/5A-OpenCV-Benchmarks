#pragma once

#include "AQuentinSolutionStrategy.h"

struct BaseQuentinSolutionStrategy : public AQuentinSolutionStrategy
{
	SolutionBResult computeSolution(const cv::Mat& image) const override;
	std::string getName() const override;
};
