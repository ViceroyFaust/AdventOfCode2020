#include <string>
#include <iostream>
#include <unordered_map>

enum state {
    state_key,
    state_value,
    state_next
};

int main() {
    std::unordered_map<std::string, std::string> fieldsMap;
    std::string input;
    std::string key;
    std::string value;
    state stage = state_key;
    int validCount = 0;
    while (std::getline(std::cin, input)) { 
        if (input == "") {

        }
        for (unsigned int i = 0; i < input.size(); ++i) {
            switch(stage) {
                case state_key:
                    if (input[i] == ':')
                        stage = state_value;
                    else
                        key += input[i];
                break;
                case state_value:
                    if (input[i] == ' ' || i == input.size() - 1)
                        stage = state_next;
                    else
                        value += input[i];
                break;
                case state_next:
                    fieldsMap.insert(std::pair(key, value));
                    key = "";
                    value = "";
                    stage = state_key;
                break;
            }
        }
    }
    return 0;
}