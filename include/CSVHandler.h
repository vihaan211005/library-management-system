#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void                                  writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data);
std::vector<std::vector<std::string>> readCSV(const std::string &filename);