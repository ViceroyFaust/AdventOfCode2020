#include <iostream>
#include <set>

int countChoices(const std::string& group) {
    std::set<char> choices;
    for (char c : group) {
        choices.insert(c);
    }
    return choices.size();
}

int main() {
    int sum = 0;
    std::string input;
    std::string group;
    while (std::getline(std::cin, input)) {
        if (input == "") {
            sum += countChoices(group);
            group = "";
        } else 
            group += input;
    }
    sum += countChoices(group);
    std::cout << sum << std::endl;
    return 0;
}