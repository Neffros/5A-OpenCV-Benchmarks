#pragma once

#include "../ISolutionStrategy.h"
#include "../../5A-OpenCV-Poker/src/SolutionAResult.h"

struct ALiorSolutionStrategy : public ISolutionStrategy<SolutionAResult>
{
    CompareData compare(TableMatches expected, SolutionAResult output) const override;
};
