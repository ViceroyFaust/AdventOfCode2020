#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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

bool checkPassport(const std::string& passport) {
    std::vector<std::string> fields = splitString(passport);
    if (fields.size() != 7)
        return false;

    auto i = std::find_if(fields.begin(), fields.end(), [](const std::string& str)->bool {
        if(str.find("cid") == std::string::npos) return false;
        return true;
    });
    if (i != fields.end())
        fields.erase(i);
    return fields.size() == 7;
}

int main() {
    
    return 0;
}