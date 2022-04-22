#pragma once

#include "../ASolutionStrategy.hpp"
#include "../../OpenCV_Poker/src/SolutionBResult.h"

struct AQuentinSolutionStrategy : public ASolutionStrategy<SolutionBResult>
{
    virtual SolutionBResult computeSolution(const cv::Mat& image) const = 0;

    CompareData compare(const TableMatches& expected, const SolutionBResult& output, const cv::Mat& image) const override;
};