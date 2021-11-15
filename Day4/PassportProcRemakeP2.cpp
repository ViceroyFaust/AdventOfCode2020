#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string& str, std::string delim = " ") {
    typedef std::string::size_type index;
    std::vector<std::string> output;
    index start = 0U;
    index end = str.find(delim);
    while (end != std::string::npos) {
        output.push_back(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    output.push_back(str.substr(start));
    return output;
}
// Inclusive
bool isIntBetween(int min, int max, int num) {
    return num >= min && num <= max;
}

bool checkYr(char key, const std::string& value) {
    if (value.size() != 4)
        return false;
    int year = std::stoi(value);
    if (key == 'b') {
        return isIntBetween(1920, 2002, year);
    } else if (key == 'i') {
        return isIntBetween(2010, 2020, year);
    } else if (key == 'e') {
        return isIntBetween(2020, 2030, year);
    } else {
        return false;
    }
}

bool checkHeight(const std::string& str) {
    if (str.length() < 4)
        return false;
    std::string measure = str.substr(str.size() - 2);
    int height = std::stoi(str.substr(0, str.size() - 2));
    if (measure == "cm") {
        return isIntBetween(150, 193, height);
    } else if (measure == "in") {
        return isIntBetween(59, 76, height);
    } else {
        return false;
    }
}

bool checkHex(const std::string& str) {
    if (str.length() != 7 || str[0] != '#')
        return false;
    for (unsigned int i = 1; i < 7; ++i) {
        char c = str[i];
        if (!isIntBetween('0', '9', c) && !isIntBetween('a', 'f', c))
            return false;
    }
    return true;
}

bool checkColor(const std::string& str) {
    return str == "amb" || str == "blu" || str == "brn" ||
           str == "gry" || str == "grn" || str == "hzl" || str == "oth";
}

bool checkId(const std::string& str) {
    if (str.length() != 9)
        return false;
    for (char c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool checkField(const std::string& key, const std::string& value) {
    if (key.substr(key.size() - 2) == "yr") {
        return checkYr(key[0], value);
    } else if (key == "hgt") {
        return checkHeight(value);
    } else if (key == "hcl") {
        return checkHex(value);
    } else if (key == "ecl") {
        return checkColor(value);
    } else if (key == "pid") {
        return checkId(value);
    }
    return false;
}

bool checkPassport(const std::string& passport) {
    std::vector<std::string> fields = splitString(passport);
    int correctFields = 0;
    for (std::string str : fields) {
        std::vector<std::string> splitField = splitString(str, ":");
        correctFields += checkField(splitField[0], splitField[1]);
    }
    return correctFields == 7;
}

int main() {
    std::string input;
    std::string passport;
    int validCount = 0;
    while (std::getline(std::cin, input)) {
        if (input == "") {
            // do substr to remove hanging space
            if (checkPassport(passport.substr(0, passport.size() - 1)))
                ++validCount;
            passport = "";
        } else {
            passport += input + ' ';
        }
    }
    if (checkPassport(passport.substr(0, passport.size() - 1)))
        ++validCount;
    std::cout << validCount << std::endl;
    return 0;
}