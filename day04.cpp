// imports
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>


auto main() -> int {
    // load in day04_input.txt lines into a vector of char vectors
    std::vector<std::vector<char>> lines;
    std::ifstream inputFile("data/day04_input.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> line_chars;
        for (char ch : line) {
            line_chars.push_back(ch);
        }
        lines.push_back(line_chars);
    }
    inputFile.close();

    // looking for xmas in any direction iteratively
    // loop through each line and if a character is 'x', send every direction
    int num_xmas_found = 0;
    for (int i = 0; i < lines.size(); i++) {
        auto line = lines[i];
        for (int j = 0; j < line.size(); j++) {
            auto ch = line[j];
            if (ch == 'X') {
                // send every direction
                // up
                if (i > 2) {
                    if (
                        lines[i - 1][j] == 'M' &&
                        lines[i - 2][j] == 'A' &&
                        lines[i - 3][j] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
                // down
                if (i < (lines.size() - 3)) {
                    if (
                        lines[i + 1][j] == 'M' &&
                        lines[i + 2][j] == 'A' &&
                        lines[i + 3][j] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
                // left
                if (j > 2) {
                    if (
                        line[j - 1] == 'M' &&
                        line[j - 2] == 'A' &&
                        line[j - 3] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
                // right
                if (j < (line.size() - 3)) {
                    if (
                        line[j + 1] == 'M' &&
                        line[j + 2] == 'A' &&
                        line[j + 3] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
                // up-left
                if (i > 2 && j > 2) {
                    if (
                        lines[i - 1][j - 1] == 'M' &&
                        lines[i - 2][j - 2] == 'A' &&
                        lines[i - 3][j - 3] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
                // up-right
                if (i > 2 && j < (line.size() - 3)) {
                    if (
                        lines[i - 1][j + 1] == 'M' &&
                        lines[i - 2][j + 2] == 'A' &&
                        lines[i - 3][j + 3] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
                // down-left
                if (i < (lines.size() - 3) && j > 2) {
                    if (
                        lines[i + 1][j - 1] == 'M' &&
                        lines[i + 2][j - 2] == 'A' &&
                        lines[i + 3][j - 3] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
                // down-right
                if (i < (lines.size() - 3) && j < (line.size() - 3)) {
                    if (
                        lines[i + 1][j + 1] == 'M' &&
                        lines[i + 2][j + 2] == 'A' &&
                        lines[i + 3][j + 3] == 'S'
                    ) {
                        num_xmas_found++;
                    }
                }
            }
        }
    }
    std::cout << num_xmas_found << '\n';
    return 0;
}