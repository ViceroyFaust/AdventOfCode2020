#include <iostream>
#include <vector>
#include <string>

// In this program I am using the row-major formula in order to
// simulate a 2D array using 1D.
// row * num_cols + col = index
int main () {
    std::vector<char> map; // The "Map" given by the problem
    // START Input Block and calculating rows & cols
    std::string input;
    std::getline(std::cin, input);
    int rows = 0;
    int cols = input.length();
    do {
        for (char c : input)
            map.push_back(c);
        ++rows;
    } while (std::getline(std::cin, input));
    // END Input Block
    int colAngle = 3;
    int rowAngle = 1;
    int treeCount = 0;
    int row = 0;
    int col = 0;
    while (row <= rows) {
        row += rowAngle;
        col += colAngle;
        if (col >= cols)
            col -= cols;
        if (map[row * cols + col] == '#')
            ++treeCount;
    }
    std::cout << treeCount << std::endl;
}