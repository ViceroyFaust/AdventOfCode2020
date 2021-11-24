#include <deque>
#include <iostream>
#include <string>
#include <vector>

void getInput(std::vector<int>& inputs) {
    std::string inputStr;
    while (std::getline(std::cin, inputStr))
        inputs.push_back(std::stoi(inputStr));
}

std::deque<int> genPreamble(const std::vector<int>& inputs, int len) {
    std::deque<int> preamble;
    for (int i = 0; i < len; ++i) {
        preamble.push_back(inputs[i]);
    }
    return preamble;
}

int main() {
    std::vector<int> inputList;
    getInput(inputList);
    std::deque<int> preamble = genPreamble(inputList, 5);
    return 0;
}
