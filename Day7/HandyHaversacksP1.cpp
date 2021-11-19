#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
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

std::pair<std::string, int> extractPair(const std::string& word) {
    std::vector<std::string> words = splitString(word);
    int num = std::stoi(words[0]);
    std::string bagType = words[1] + " " + words[2];
    return std::pair<std::string, int>(bagType, num);
}

std::set<std::pair<std::string, int>> extractContainedBags(const std::string& word) {
    std::set<std::pair<std::string, int>> output;
    std::vector<std::string> bags = splitString(word, ", ");
    for (std::string str : bags) {
        output.insert(extractPair(str));
    }
    return output;
}

std::string extractKey(const std::string& word) {
    std::vector<std::string> keyWordSplit = splitString(word);
    return keyWordSplit[0] + " " + keyWordSplit[1]; // Key is the first two words before "contain"
}

int main() {
    // Map containing sets of string and int
    std::unordered_map<std::string, std::set<std::pair<std::string, int>>> rules;
    std::string input;
    while (std::getline(std::cin, input)) {
        std::string key;
        std::vector<std::string> containSplit = splitString(input, " contain ");
        key = extractKey(containSplit[0]);
        // Each contained bag has a number, thus pair
        std::set<std::pair<std::string, int>> bagSet = extractContainedBags(containSplit[1]);

        std::cout << key << ": ";
        for (auto i = bagSet.begin(); i != bagSet.end(); ++i) {
            std::cout << i->second << " " << i->first << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}