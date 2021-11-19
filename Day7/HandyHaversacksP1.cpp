#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

struct Bag {
    std::string name;
    std::vector<std::pair<int, Bag*>> bags;
};

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
    return keyWordSplit[0] + " " + keyWordSplit[1];  // Key is the first two words before "contain"
}

bool hasBag(const std::unordered_map<std::string, std::set<std::pair<std::string, int>>>& containedBags) {
    
    return false;
}

int main() {
    // Map containing sets of string and int
    std::unordered_map<std::string, std::set<std::pair<std::string, int>>> rules;
    std::string input;
    // Collect all bag rules and store them in a map
    while (std::getline(std::cin, input)) {
        std::vector<std::string> containSplit = splitString(input, " contain ");
        std::string key = extractKey(containSplit[0]);
        std::set<std::pair<std::string, int>> bagSet = extractContainedBags(containSplit[1]);
    }
    int counter = 0;
    if (hasBag(rules))
        counter++;
    return 0;
}