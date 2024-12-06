#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include <set>


auto isOrderingValid(const std::vector<int>& line, const std::unordered_map<int, std::set<int>>& befores, const std::unordered_map<int, std::set<int>>& afters) -> bool {
    int idx = -1;
    std::vector<int> visited = {};
    std::set<int> visited_map = {};
    std::vector<int> remaining = {};
    bool valid;
    for (int j : line) {
        idx++;
        // remaining is all numbers in num_line after (not including) j
        remaining = {};
        for (int k = idx + 1; k < line.size(); k++) {
            remaining.push_back(line[k]);
        }
        // if overlap between visited set and afters set for j, it's not valid
        valid = true;
        std::vector<int> intersection;
        if (afters.find(j) != afters.end()) {
            std::set_intersection(visited.begin(), visited.end(), afters.at(j).begin(), afters.at(j).end(), std::back_inserter(intersection));
        }
        if (!intersection.empty()) {
            valid = false;
            break;
        }
        // check remaining and befores violation
        std::vector<int> intersection2;
        if (befores.find(j) != befores.end()) {
            std::set_intersection(remaining.begin(), remaining.end(), befores.at(j).begin(), befores.at(j).end(), std::back_inserter(intersection2));
        }
        if (!intersection2.empty()) {
            valid = false;
            break;
        }
        visited.push_back(j);
    }
    return valid;
}

auto main() -> int {
    std::vector<int> lefts;
    std::vector<int> rights;
    std::vector<std::vector<int>> nums;
    std::ifstream inputFile("data/day05.txt");
    // section1: line looks like: int1|int2
    std::string line;
    // section2: line looks like: num1,num2,num3,...,numi
    bool section2 = false;
    std::unordered_map<int, std::set<int>> befores;
    std::unordered_map<int, std::set<int>> afters;
    while (std::getline(inputFile, line)) {
        // if line is empty, indicate section2 start
        if (line == "") {
            section2 = true;
            continue;
        }
        // get section1 values
        if (section2) {
            std::istringstream iss(line);
            std::string num;
            std::vector<int> curr_nums;
            while (std::getline(iss, num, ',')) {
                curr_nums.push_back(std::stoi(num));
            }
            nums.push_back(curr_nums);
        }
        else {
            std::istringstream iss(line);
            std::string left;
            std::string right;
            std::getline(iss, left, '|');
            std::getline(iss, right, '|');
            int left_int = std::stoi(left);
            int right_int = std::stoi(right);
            befores[right_int].insert(left_int);
            afters[left_int].insert(right_int);
            lefts.push_back(std::stoi(left));
            rights.push_back(std::stoi(right));
        }
    }
    inputFile.close();
    
    int total_middle_sum = 0;
    std::vector<std::vector<int>> invalid_lines;
    for (auto & num_line : nums) {
        bool valid = isOrderingValid(num_line, befores, afters);
        if (valid) {
            // it's valid, get middle number in the line
            total_middle_sum += num_line.at(num_line.size() / 2);
        }
        else {
            invalid_lines.push_back(num_line);
        }
    }
    std::cout << total_middle_sum << '\n';

    // PART 2
    int total_middle_invalid_sum = 0;
    for (auto & num_line : invalid_lines) {
        std::vector<int> sorted_line;
        bool found = false;
        for (int num : num_line) {
            if (sorted_line.empty()) {
                sorted_line.push_back(num);
                continue;
            }
            std::vector<int> curr_line;
            int sorted_line_size = sorted_line.size();
            for (int i = 0; i <= sorted_line.size(); i++) {
                curr_line = sorted_line;
                curr_line.insert(curr_line.begin() + sorted_line_size - i, num);
                bool valid = isOrderingValid(curr_line, befores, afters);
                if (valid) {
                    sorted_line = curr_line;
                    found = true;
                    break;
                }
            }
        }
        total_middle_invalid_sum += sorted_line.at(sorted_line.size() / 2);
    }
    std::cout << total_middle_invalid_sum << '\n';
    return 0;
}