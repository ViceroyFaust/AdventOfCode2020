#include <deque>
#include <iostream>
#include <string>
#include <vector>

// Populates a vector with the contents of the input
void getInput(std::vector<int>& inputs) {
    std::string inputStr;
    while (std::getline(std::cin, inputStr))
        inputs.push_back(std::stoi(inputStr));
}

// Generates a variable length preamble queue from the input
std::deque<int> genPreamble(const std::vector<int>& inputs, int len) {
    std::deque<int> preamble;
    for (int i = 0; i < len; ++i) {
        preamble.push_back(inputs[i]);
    }
    return preamble;
}

bool isError(const std::deque<int>& preamble, int num) {
    for (size_t i = 0; i < preamble.size(); ++i) {
        for (size_t j = i + 1; j < preamble.size(); ++j) {
            if (preamble[i] + preamble[j] == num) {
                return false;
            }
        }
    }
    return true;
}

int findError(const std::vector<int>& inputs, int preambleLen) {
    std::deque<int> preamble = genPreamble(inputs, preambleLen);
    for (size_t i = preambleLen; i < inputs.size(); ++i) {
        int toCheck = inputs[i];
        if(isError(preamble, toCheck))
            return toCheck;
        preamble.pop_front();
        preamble.push_back(toCheck);
    }
    return 0;
}

int main() {
    std::vector<int> inputList;
    getInput(inputList);
    
    std::cout << findError(inputList, 5) << std::endl;
    return 0;
}
