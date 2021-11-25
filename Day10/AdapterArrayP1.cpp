#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

void getInput(std::vector<int>& inputs) {
    std::string inputStr;
    while (std::getline(std::cin, inputStr)) {
        int number = std::stoi(inputStr);
        inputs.push_back(number);
    }
    std::sort(inputs.begin(), inputs.end());
}

int differenceProduct(const std::vector<int>& inputs) {
    // There is always a 1 difference between the outlet
    // & 3 difference between the device
    int oneDiff = 1, threeDiff = 1;    
    for (size_t i = 1; i < inputs.size(); ++i) {
        int prevNum = inputs[i - 1];
        int curNum = inputs[i];
        if (curNum - prevNum == 1)
            ++oneDiff;
        else if (curNum - prevNum == 3)
            ++threeDiff;
    }
    std::cout << "1's: " << oneDiff << " 3's: " << threeDiff << std::endl;
    return oneDiff * threeDiff;
}

int main() {
    std::vector<int> inputList;
    getInput(inputList);

    std::cout << differenceProduct(inputList) << std::endl;
    return 0;
}