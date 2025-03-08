#include "CSVHandler.h"

void writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data) {
    std::ofstream file(filename);
        if (file.is_open()) {
                for (const auto &row: data) {
                        for (size_t i = 0; i < row.size(); ++i) {
                            file << row[i];
                                if (i < row.size() - 1) {
                                    file << ",";
                            }
                        }
                    file << "\n";
                }
            file.close();
    }
}

std::vector<std::vector<std::string>> readCSV(const std::string &filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream                         file(filename);
        if (file.is_open()) {
            std::string line, cell;
                while (std::getline(file, line)) {
                    std::stringstream        lineStream(line);
                    std::vector<std::string> row;
                        while (std::getline(lineStream, cell, ',')) {
                            row.push_back(cell);
                        }
                    data.push_back(row);
                }
            file.close();
    }
    return data;
}