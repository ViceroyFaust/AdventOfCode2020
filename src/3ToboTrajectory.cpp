#include <iostream>
#include <vector>
#include <string>

int main () {
    std::string map; // The "Map" given by the problem
    std::string input;
    std::getline(std::cin, input);
    int rows = 1;
    int cols = input.length();
    map += input;
    while (std::getline(std::cin, input)) {
        map += input;
        ++rows;
    }

}