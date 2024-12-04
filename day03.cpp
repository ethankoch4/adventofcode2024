#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

auto split(std::string string, const std::string& delim) -> std::vector<std::string> {
    std::vector<std::string> split_string;
    int pos = 0;
    std::string token;
    while ((pos = string.find(delim)) != std::string::npos) {
        token = string.substr(0, pos);
        split_string.push_back(token);
        string.erase(0, pos + delim.length());
    }
    split_string.push_back(string);
    return split_string;
}

/**
 * Get two substrings with numbers that are split by a comma and end with closed parentheses
 */
auto find_two_numbers(std::string string) -> std::vector<std::string> {
    std::vector<std::string> nums;
    std::string num1 = "";
    std::string num2 = "";
    int last_i;
    for (int i = 0; i < string.size(); i++) {
        if (isdigit(string[i])) {
            num1 += string[i];
        } else if (string[i] == ',') {
            last_i = i;
            break;
        }
    }
    for (int i = (last_i + 1); i <= string.size(); i++) {
        if (isdigit(string[i])) {
            num2 += string[i];
        } else if (string[i] == ')') {
            break;
        } else {
            num2 = "";
            break;
        }
    }
    if (num1.length() > 3 || num2.length() > 3) {
        num1 = "";
        num2 = "";
    }
    nums.push_back(num1);
    nums.push_back(num2);
    return nums;
}

auto find_number(const std::string& string) -> int {
    std::string num = "";
    for (char i : string) {
        if (isdigit(i)) {
            num += i;
        }
    }
    return std::stoi(num);
}

/**
 * Get all the correctly formatted 'mul(num1,num2)' instructions
 * 
 */
auto main() -> int {
    std::vector<int> col1;
    std::vector<int> col2;

    std::ifstream inputFile("data/day03_input.txt");
    // join lines with space
    std::string line = "";
    std::string curr_line;
    while (std::getline(inputFile, curr_line)) {
        line += curr_line;
    }
    inputFile.close();
    // PART !
    // substrings split by mul
    std::vector<std::string> split_string = split(line, "mul(");

    // loop through substrings and look for end parens; change inplace
    int total_mul_result = 0;
    for (int i = 0; i <= split_string.size(); i++) {
        std::string curr_string = split_string[i];
        std::vector<std::string> two_nums = find_two_numbers(curr_string);
        const std::string& num1 = two_nums[0];
        const std::string& num2 = two_nums[1];
        if (num1 == "" || num2 == "") {
            split_string[i] = "";
            continue;
        }
        int num1_int = find_number(num1);
        int num2_int = find_number(num2);
        total_mul_result += (num1_int * num2_int);
    }

    // print total mul result
    std::cout << total_mul_result << '\n';
    std::cout.flush();

    // PART 2
    bool enabled = true;
    int total_mul_result_part2 = 0;
    for (int i = 0; i <= line.size(); i++) {
        if (enabled && line.substr(i, 4) == "mul(") {
            // get first number
            std::string first_num = "";
            int real_first_num = 0;
            int idx;
            int j;
            for (j = 0; j <= 3; j++) {
                idx = i + 4 + j;
                if (isdigit(line[idx])) {
                    first_num += line[idx];
                } else if (line[idx] == ',' && first_num != "") {
                    real_first_num = std::stoi(first_num);
                    break;
                }
            }
            if (real_first_num == 0) {
                continue;
            }
            std::string second_num = "";
            int real_second_num = 0;
            // skip the comma
            for (int k = (j + 1); k <= (j + 5); k++) {
                idx = i + 4 + k;
                if (isdigit(line[idx])) {
                    second_num += line[idx];
                } else if (line[idx] == ')' && second_num != "") {
                    real_second_num = std::stoi(second_num);
                    break;
                }
            }
            if (real_second_num == 0) {
                continue;
            }
            total_mul_result_part2 += (real_first_num * real_second_num);
        }
        else if (line.substr(i, 4) == "do()") {
            enabled = true;
        }
        else if (line.substr(i, 7) == "don't()") {
            enabled = false;
        }
    }

    // print total mul result
    std::cout << total_mul_result_part2 << '\n';
    std::cout.flush();
    return 0;
}