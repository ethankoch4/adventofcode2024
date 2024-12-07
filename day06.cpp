#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <set>


using namespace std;


auto main() -> int {
    // load in day06.txt
    vector<vector<char>> lines;
    ifstream inputFile("data/day06.txt");
    string line;
    // record starting position of agent (^)
    // record positions of guards (#)
    // record positions with (i, j) of the grid
    tuple<int, int> agent_idx = make_tuple(-1, -1);
    // 1 = right, 2 = down, 3 = left, 4 = up
    int agent_direction = 0;
    vector<tuple<int, int>> guards;
    while (getline(inputFile, line)) {
        vector<char> line_chars;
        for (int j = 0; j < line.size(); j++) {
            char ch = line[j];
            if (ch == '^') {
                agent_direction = 4;
                agent_idx = make_tuple(lines.size(), j);
            }
            else if (ch == '>') {
                agent_direction = 1;
                agent_idx = make_tuple(lines.size(), j);
            }
            else if (ch == 'v') {
                agent_direction = 2;
                agent_idx = make_tuple(lines.size(), j);
            }
            else if (ch == '<') {
                agent_direction = 3;
                agent_idx = make_tuple(lines.size(), j);
            }
            else if (ch == '#') {
                guards.emplace_back(lines.size(), j);
            }
            line_chars.push_back(ch);
        }
        lines.push_back(line_chars);
    }
    inputFile.close();
    tuple<int, int> original_agent_idx(agent_idx);
    int original_agent_direction = agent_direction;

    // PART 1
    // take a step "forward" until you hit a wall or a guard
    // when you hit something, turn right
    // repeat until you hit the bottom
    // print the number of guards you hit
    // keep track of unique positions the agent has visited
    set<tuple<int, int>> visited_positions;
    visited_positions.insert(agent_idx);
    while (true) {
        int i = get<0>(agent_idx);
        int j = get<1>(agent_idx);
        if (agent_direction == 1) {
            // right
            if (j == (lines[i].size() - 1) || lines[i][j + 1] == '#') {
                agent_direction = 2;
            }
            else {
                agent_idx = make_tuple(i, j + 1);
            }
        }
        else if (agent_direction == 2) {
            // down
            if (i == (lines.size() - 1) || lines[i + 1][j] == '#') {
                agent_direction = 3;
                continue;
            }
            else {
                agent_idx = make_tuple(i + 1, j);
            }
        }
        else if (agent_direction == 3) {
            // left
            if (j == 0 || lines[i][j - 1] == '#') {
                agent_direction = 4;
                continue;
            }
            else {
                agent_idx = make_tuple(i, j - 1);
            }
        }
        else if (agent_direction == 4) {
            // up
            if (i == 0 || lines[i - 1][j] == '#' ) {
                agent_direction = 1;
                continue;
            }
            else {
                agent_idx = make_tuple(i - 1, j);
            }
        }
        visited_positions.insert(agent_idx);
        // if we hit the bottom, break
        if (get<0>(agent_idx) == (lines.size() - 1)) {
            break;
        }
    }
    cout << visited_positions.size() << '\n';

    // PART 2
    int num_infinite_loops = 0;
    // deep copy original agent position and direction
    for (int i = 0; i < lines.size(); i++) {
        vector<char> curr_line = lines[i];
        for (int j = 0; j < curr_line.size(); j++) {
            agent_idx = original_agent_idx;
            agent_direction = original_agent_direction;
            if (curr_line[j] == '#') {
                continue;
            }
            else if (curr_line[j] == '^') {
                continue;
            }
            // add an obstacle at (i, j)
            lines[i][j] = '#';
            // run the simulation
            set<tuple<int, int, int>> visited_positions;

            while (true) {
                // run iteration and see if you get an infinite loop or not
                int k = get<0>(agent_idx);
                int l = get<1>(agent_idx);
                // check if we've visited this position & direction before
                // visited positions
                if (visited_positions.find(make_tuple(k, l, agent_direction)) != visited_positions.end()) {
                    num_infinite_loops++;
                    break;
                }
                visited_positions.insert(make_tuple(k, l, agent_direction));
                if (agent_direction == 1) {
                    // right
                    if (l == (lines[k].size() - 1) || lines[k][l + 1] == '#') {
                        agent_direction = 2;
                    }
                    else {
                        agent_idx = make_tuple(k, l + 1);
                    }
                }
                else if (agent_direction == 2) {
                    // down
                    if (k == (lines.size() - 1) || lines[k + 1][l] == '#') {
                        agent_direction = 3;
                    }
                    else {
                        agent_idx = make_tuple(k + 1, l);
                    }
                }
                else if (agent_direction == 3) {
                    // left
                    if (l == 0 || lines[k][l - 1] == '#') {
                        agent_direction = 4;
                    }
                    else {
                        agent_idx = make_tuple(k, l - 1);
                    }
                }
                else if (agent_direction == 4) {
                    // up
                    if (k == 0 || lines[k - 1][l] == '#' ) {
                        agent_direction = 1;
                    }
                    else {
                        agent_idx = make_tuple(k - 1, l);
                    }
                }
                // if we hit the bottom, left screen, right screen, or top, break
                if (get<0>(agent_idx) == (lines.size() - 1) || get<1>(agent_idx) == 0 || get<1>(agent_idx) == (lines[get<0>(agent_idx)].size() - 1) || get<0>(agent_idx) == 0) {
                    break;
                }
            }
            // remove the obstacle
            lines[i][j] = '.';
        }
    }
    cout << num_infinite_loops << '\n';
    
    return 0;
}