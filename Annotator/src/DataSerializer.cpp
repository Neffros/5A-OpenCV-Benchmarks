#include "DataSerializer.h"
#include <fstream>

#include <iostream>

void DataSerializer::writeData(const std::string& fileName, TableMatches data) {
    auto json = data.toJson();
    std::ofstream file;
    file.open(fileName);
    file << json << std::endl;
    file.close();
}

TableMatches DataSerializer::readData(const std::string &fileName) {
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    auto js = nlohmann::json::parse(file);
    file.close();
    return TableMatches::fromJson(js);
}
