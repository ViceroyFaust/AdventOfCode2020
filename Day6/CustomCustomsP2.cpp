#include <iostream>
#include <unordered_map>

int countCommonChoices(const std::string& group, int members) {
    std::unordered_map<char, int> map;
    int sum = 0;
    for (char c : group) {
        ++map[c];
    }
    for (auto i = map.begin(); i != map.end(); ++i) {
        if (i->second == members)
            ++sum;
    }
    return sum;
}

int main() {
    int sum = 0;
    int lines = 0;
    std::string input;
    std::string group;
    while (std::getline(std::cin, input)) {
        if (input == "") {
            sum += countCommonChoices(group, lines);
            lines = 0;
            group = "";
        } else {
            group += input;
            ++lines;
        }
    }
    sum += countCommonChoices(group, lines);
    std::cout << sum << std::endl;
    return 0;
}