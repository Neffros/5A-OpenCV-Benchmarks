#pragma once

#include "ISolutionStrategy.h"

template <typename Result>
struct ASolutionStrategy : public ISolutionStrategy
{
    virtual CompareData compare(TableMatches expected, Result output) const = 0;
    virtual Result computeSolution(cv::Mat image) const = 0;

    CompareData execute(cv::Mat image, TableMatches expected) const override
    {
        return this->compare(expected, this->computeSolution(image));
    }
};
