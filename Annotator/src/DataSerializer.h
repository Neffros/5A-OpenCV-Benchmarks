// Created by Quentin Pamart on 14/04/2022.

#pragma once

#include "../../json/single_include/nlohmann/json.hpp"
#include "TableMatches.h"

class DataSerializer {
public:
    template <typename T>
    static void writeData(const std::string& fileName, T data);
    static TableMatches readData(const std::string& fileName);
};


