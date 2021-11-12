#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum state {
    state_key,
    state_value,
    state_next
};

bool isValid(const std::unordered_map<std::string, std::string> fields, std::vector<std::string>& req) {
    if (fields.size() < 7)
        return false;
    for (std::string str : req) {
        auto found = fields.find(str);
        if (found == fields.end()) {
            return false;
        }
    }
    return true;
}

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
            if (isValid(fieldsMap, reqFields))
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
                        if (i >= input.size() || input[i] == ' ') {
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
    // Due to endline, the while loop never reaches the last validation
    if (isValid(fieldsMap, reqFields)) {
        ++validCount;
    }
    std::cout << validCount << std::endl;
    return 0;
}