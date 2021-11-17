#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> seats;
    std::string input;
    std::getline(std::cin, input);
    do {
        // All input is always 10 characters long
        // First 7 characters are for rows; 3 are for cols
        // 128 rows & 8 cols
        int frontRow = 0, backRow = 127;
        int leftCol = 0, rightCol = 7;
        for (unsigned int i = 0; i < 10; ++i) {
            if (input[i] == 'F') {
                backRow -= (backRow - frontRow) / 2;
            } else if (input[i] == 'B') {
                frontRow += (1 + backRow - frontRow) / 2;
            } else if (input[i] == 'L') {
                rightCol -= (rightCol - leftCol) / 2;
            } else { // 'R'
                leftCol += (1 + rightCol - leftCol) / 2;
            }
        }
        int seatIndex = frontRow * 8 + leftCol;
        seats.push_back(seatIndex);
    } while (std::getline(std::cin, input));
    sort(seats.begin(), seats.end());
    for (unsigned int i = 1; i < seats.size(); ++i) {
        if (seats[i - 1] != seats[i] - 1) {
            std::cout << seats[i] - 1 << std::endl;
            break;
        }
    }
    return 0;
}