#pragma once

#include "../ASolutionStrategy.hpp"
#include "../../OpenCV_Poker/src/SolutionBResult.h"

struct AQuentinSolutionStrategy : public ASolutionStrategy<SolutionBResult>
{
    virtual SolutionBResult computeSolution(cv::Mat image) const = 0;

    CompareData compare(TableMatches expected, SolutionBResult output) const override;
};