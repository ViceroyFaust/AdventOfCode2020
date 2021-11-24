#include <deque>
#include <iostream>
#include <string>
#include <vector>

// Populates a vector with the contents of the input
void getInput(std::vector<unsigned long>& inputs) {
    std::string inputStr;
    while (std::getline(std::cin, inputStr))
        inputs.push_back(std::stoul(inputStr));
}

// Generates a variable length preamble queue from the input
std::deque<unsigned long> genPreamble(const std::vector<unsigned long>& inputs, int len) {
    std::deque<unsigned long> preamble;
    for (int i = 0; i < len; ++i) {
        preamble.push_back(inputs[i]);
    }
    return preamble;
}

bool isError(const std::deque<unsigned long>& preamble, unsigned long num) {
    for (size_t i = 0; i < preamble.size(); ++i) {
        for (size_t j = i + 1; j < preamble.size(); ++j) {
            if (preamble[i] + preamble[j] == num) {
                return false;
            }
        }
    }
    return true;
}

unsigned long findError(const std::vector<unsigned long>& inputs, int preambleLen) {
    std::deque<unsigned long> preamble = genPreamble(inputs, preambleLen);
    for (size_t i = preambleLen; i < inputs.size(); ++i) {
        unsigned long toCheck = inputs[i];
        if (isError(preamble, toCheck))
            return toCheck;
        preamble.pop_front();
        preamble.push_back(toCheck);
    }
    return 0;
}

unsigned long findWeakness(const std::vector<unsigned long>& inputs, unsigned long errorNum) {
    while (true) {
        unsigned long int min = 0 - 1, max = 0;
        unsigned long sum = 0;
        for (size_t i = 0; i < inputs.size(); ++i) {
            unsigned long curNum = inputs[i];
            sum += curNum;
            if (curNum < min) {
                min = curNum;
            } else if (curNum > max) {
                max = curNum;
            }
            if (sum == errorNum)
                return min + max;
            if (sum > errorNum)
                return 0;
        }
    }
    return 0;
}

int main() {
    std::vector<unsigned long> inputList;
    getInput(inputList);

    unsigned long errorNum = findError(inputList, 25);
    return 0;
}
