#pragma once

#include "../ASolutionStrategy.hpp"
#include "../../5A-OpenCV-Poker/src/SolutionAResult.h"

struct ALiorSolutionStrategy : public ASolutionStrategy<SolutionAResult>
{
    virtual SolutionAResult computeSolution(const cv::Mat& image) const = 0;

    CompareData compare(const TableMatches& expected, const SolutionAResult& output, const cv::Mat& image) const override;
};
