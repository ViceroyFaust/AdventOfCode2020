#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum state {
    state_key,
    state_value,
    state_next
};

int main() {
    std::vector<std::string> reqFields = {
        "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" /*, "cid"*/
    };
    std::unordered_map<std::string, std::string> fieldsMap;
    std::string input;
    std::string key;
    std::string value;
    state stage = state_key;
    int validCount = 0;
    while (std::getline(std::cin, input)) {
        if (input == "") {
            bool isValid = true;
            for (std::string str : reqFields) {
                auto found = fieldsMap.find(str);
                if (found == fieldsMap.end()) {
                    isValid = false;
                    break;
                }
            }
            if (isValid)
                ++validCount;
            fieldsMap.clear();
        } else {
            unsigned int i = 0;
            bool stop = false;
            while (!stop) {
                switch (stage) {
                    case state_key:
                        if (input[i] == ':') {
                            stage = state_value;
                        } else {
                            key += input[i];
                        }
                        ++i;
                        break;
                    case state_value:
                        if (i == input.size() - 1) {
                            value += input[i];
                            stage = state_next;
                        } else if (input[i] == ' ') {
                            stage = state_next;
                        } else {
                            value += input[i];
                        }
                        ++i;
                        break;
                    case state_next:
                        fieldsMap.insert(std::pair(key, value));
                        key = "";
                        value = "";
                        stage = state_key;
                        if (i >= input.size())
                            stop = true;
                        break;
                }
            }
        }
    }
    std::cout << validCount << std::endl;
    return 0;
}