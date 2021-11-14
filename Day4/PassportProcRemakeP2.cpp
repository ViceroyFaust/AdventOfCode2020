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
bool isIntBetween(int min, int max, int year) {
    return year >= min && year <= max;
}

bool checkField(const std::string& key, const std::string& value) {
    try {
        if (key == "byr") {
            if (!isIntBetween(1920, 2002, std::stoi(value)))
                return false;
        } else if (key == "iyr") {
            if (!isIntBetween(2010, 2020, std::stoi(value)))
                return false;
        } else if (key == "eyr") {
            if (!isIntBetween(2020, 2030, std::stoi(value)))
                return false;
        } else if (key == "hgt") {
        } else if (key == "hcl") {
        } else if (key == "ecl") {
        } else if (key == "pid") {
        }
    } catch (std::invalid_argument& e) {
        return false;
    }
    return true;
}

bool checkPassport(const std::string& passport) {
    std::vector<std::string> fields = splitString(passport);
    if (fields.size() < 7)
        return false;

    auto i = std::find_if(fields.begin(), fields.end(), [](const std::string& str) -> bool {
        if (str.find("cid") == std::string::npos) return false;
        return true;
    });
    if (i != fields.end())
        fields.erase(i);
    if (fields.size() != 7)
        return false;
    for (std::string str : fields) {
        std::vector<std::string> splitField = splitString(str, ":");
        if (!checkField(splitField[0], splitField[1]))
            return false;
    }
    return true;
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