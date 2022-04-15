#pragma once

#include "../ISolutionStrategy.h"
#include "../../OpenCV_Poker/src/SolutionBResult.h"

struct AQuentinSolutionStrategy : public ISolutionStrategy<SolutionBResult>
{
    CompareData compare(TableMatches expected, SolutionBResult output) const override;
};
