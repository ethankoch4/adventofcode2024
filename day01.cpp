#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

/**
 * Get the sum of the absolute differences between two columns of numbers.
 * 
 */
int main() {
    std::vector<int> col1;
    std::vector<int> col2;

    std::ifstream inputFile("data/day01_input.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int a, b;
        iss >> a >> b;
        col1.push_back(a);
        col2.push_back(b);
    }
    inputFile.close();

    // sort each vector
    std::sort(col1.begin(), col1.end());
    std::sort(col2.begin(), col2.end());

    // loop through the vectors and sum absolute differences
    int sum = 0;
    for (int i = 0; i <= col1.size(); i++) {
        sum += std::abs(col1[i] - col2[i]);
    }

    // print the sum of the differences
    std::cout << sum << '\n';
    std::cout.flush();
    return 0;
}