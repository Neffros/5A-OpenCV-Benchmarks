#pragma once

#include "CompareData.h"
#include "../Annotator/src/TableMatches.h"

template <typename Result>
struct ISolutionStrategy
{
    virtual Result execute(cv::Mat image) const = 0;
    virtual CompareData compare(TableMatches expected, Result output) const = 0;
};
