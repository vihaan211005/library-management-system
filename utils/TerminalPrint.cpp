#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void printTable(const std::vector<std::vector<std::string>> &data) {
    if (data.empty())
        return;

    std::vector<size_t> colWidths(data[0].size(), 0);

        for (const auto &row: data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    colWidths[i] = std::max(colWidths[i], row[i].length());
                }
        }

        for (const auto &row: data) {
            std::cout << "| ";
                for (size_t i = 0; i < row.size(); ++i) {
                    std::cout << std::left << std::setw(colWidths[i]) << row[i] << " | ";
                }
            std::cout << "\n";
        }
}

int printOptions(const std::vector<std::string> &options) {
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << i + 1 << ". " << options[i] << "\n";
        }
    int answer;
    std::cout << "Enter option number: ";
        while (!(std::cin >> answer) || answer < 1 || answer > static_cast<int>(options.size())) {
            std::cout << "Invalid option. Please enter a number between 1 and " << options.size() << ": ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return answer;
}