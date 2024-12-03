#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

/**
 * Get the similarity score
 * 
 */
int main() {
    // load into two vectors
    std::vector<int> col1;
    std::vector<int> col2;

    std::ifstream inputFile("data/input.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue; // Skip lines that cannot be parsed
        }
        col1.push_back(a);
        col2.push_back(b);
    }
    inputFile.close();

    int similarity_score = 0;
    for (int i = 0; i <= col1.size(); i++) {
        int curr_val1 = col1[i];
        int num_appearances_in_col2 = std::count(col2.begin(), col2.end(), curr_val1);
        similarity_score += (curr_val1 * num_appearances_in_col2);
    }

    std::cout << similarity_score << std::endl;
    std::cout.flush();
    return 0;
}