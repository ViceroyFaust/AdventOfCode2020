#include <iostream>
#include <string>
#include <unordered_map>

enum state {
    state_key,
    state_value,
    state_next
};

enum field {
    byr,
    iyr,
    eyr,
    hgt,
    hcl,
    ecl,
    pid
};

bool isValid(const std::unordered_map<std::string, std::string> fields) {
    std::unordered_map<std::string, field> req = {
        std::pair("byr", byr), std::pair("iyr", iyr), std::pair("eyr", eyr),
        std::pair("hgt", hgt), std::pair("hcl", hcl), std::pair("ecl", ecl),
        std::pair("pid", pid)};
    if (fields.size() < 7)
        return false;
    for (auto i = req.begin(); i != req.end(); ++i) {
        auto found = fields.find(i->first);
        if (found == fields.end()) {
            return false;
        } else {
            switch (i->second) {
                case byr: {
                    int min = 1920, max = 2002;
                    int year = std::stoi(fields.at(i->first));
                    if (year < min && year > max)
                        return false;
                    break;
                }
                case iyr: {
                    int min = 2010, max = 2020;
                    int year = std::stoi(fields.at(i->first));
                    if (year < min && year > max)
                        return false;
                    break;
                }
                case eyr: {
                    int min = 2020, max = 2030;
                    int year = std::stoi(fields.at(i->first));
                    if (year < min && year > max)
                        return false;
                    break;
                }
                case hgt: {
                    std::string height = fields.at(i->first);
                    int minCm = 150, maxCm = 193;
                    int minIn = 59, maxIn = 76;
                    int heightNum = std::stoi(height.substr(0, height.size() - 2));
                    if ("cm" == height.substr(height.size() - 2) && (heightNum < minCm && heightNum > maxCm))
                        return false;
                    if ("in" == height.substr(height.size() - 2) && (heightNum < minIn && heightNum > maxIn))
                        return false;
                    break;
                }
                case hcl: {
                    std::string hex = fields.at(i->first);
                    if (hex.size() != 7)
                        return false;
                    if (hex[0] != '#')
                        return false;
                    for (unsigned int i = 1; i < 7; ++i) {
                        if ((isdigit(hex[i]) == 0) || (isalpha(hex[i]) == 0))
                            return false;
                    }
                    break;
                }
                case ecl: {
                    std::string clr = fields.at(i->first);
                    if (clr != "amb" && clr != "blu" && clr != "brn" && clr != "gry" &&
                        clr != "grn" && clr != "hzl" && clr != "oth")
                        return false;
                    break;
                }
                case pid: {
                    std::string number = fields.at(i->first);
                    if (number.length() != 9)
                        return false;
                    for (unsigned int i = 0; i < 9; ++i) {
                        if (isdigit(number[i]) == 0)
                            return false;
                    }
                    break;
                }
            }
        }
    }
    return true;
}

int main() {
    std::unordered_map<std::string, std::string> fieldsMap;
    std::string input;
    std::string key;
    std::string value;
    state stage = state_key;
    int validCount = 0;
    while (std::getline(std::cin, input)) {
        if (input == "") {
            if (isValid(fieldsMap))
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
    if (isValid(fieldsMap)) {
        ++validCount;
    }
    std::cout << validCount << std::endl;
    return 0;
}