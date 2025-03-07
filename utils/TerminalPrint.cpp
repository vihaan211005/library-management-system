#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

void printTable(const std::vector<std::vector<std::string>>& data) {
    if (data.empty()) return;
    
    std::vector<size_t> colWidths(data[0].size(), 0);
    
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            colWidths[i] = std::max(colWidths[i], row[i].length());
        }
    }
    
    for (const auto& row : data) {
        std::cout << "| ";
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << std::left << std::setw(colWidths[i]) << row[i] << " | ";
        }
        std::cout << "\n";
    }
}