#pragma once

#include "../ASolutionStrategy.hpp"
#include "../../5A-OpenCV-Poker/src/SolutionAResult.h"

struct ALiorSolutionStrategy : public ASolutionStrategy<SolutionAResult>
{
    virtual SolutionAResult computeSolution(cv::Mat image) const = 0;

    CompareData compare(TableMatches expected, SolutionAResult output) const override;
};
