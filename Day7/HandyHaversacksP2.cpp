#include <iostream>
#include <queue>
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
// Returns the information extracted from rules after contain
// If no bags are contained, an empty pair is returned
std::pair<std::string, int> extractPair(const std::string& word) {
    if (word == "no other bags.")
        return std::pair<std::string, int>();
    std::vector<std::string> words = splitString(word);
    int num = std::stoi(words[0]);
    std::string bagType = words[1] + " " + words[2];
    return std::pair<std::string, int>(bagType, num);
}

// Creates a set containing the rules of the given bag
std::set<std::pair<std::string, int>> extractContainedBags(const std::string& word) {
    std::set<std::pair<std::string, int>> output;
    std::vector<std::string> bags = splitString(word, ", ");
    for (std::string str : bags) {
        output.insert(extractPair(str));
    }
    return output;
}

// Extracts the "key" or colour designation of a given bag
std::string extractKey(const std::string& word) {
    std::vector<std::string> keyWordSplit = splitString(word);
    return keyWordSplit[0] + " " + keyWordSplit[1];  // Key is always the first two words before "contain"
}

unsigned long insideGoldCount(const std::unordered_map<std::string, std::set<std::pair<std::string, int>>>& rules) {
    unsigned long totCount = 0;
    std::queue<std::pair<std::string, int>> q;
    q.push(std::pair("shiny gold", 1));
    unsigned long prevSize = 1;
    while (q.size() > 0) {
        int bagsCount = 0;
        auto curSet = rules.at(q.front().first);
        for (auto bags = curSet.begin(); bags != curSet.end(); ++bags) {
            if (bags->first != "") {
                q.push(std::pair(bags->first, bags->second));
                bagsCount += bags->second;
            }
        }
        totCount += q.front().second * prevSize * bagsCount;
        prevSize *= q.front().second;
        q.pop();
    }
    return totCount;
}

int main() {
    // Map containing a set representing a bag containing rules on how to contain other bags
    std::unordered_map<std::string, std::set<std::pair<std::string, int>>> rules;
    std::string input;
    while (std::getline(std::cin, input)) {
        std::vector<std::string> containSplit = splitString(input, " contain ");
        std::string key = extractKey(containSplit[0]);
        std::set<std::pair<std::string, int>> bagSet = extractContainedBags(containSplit[1]);
        rules.insert(std::pair(key, bagSet));
    }
    std::cout << insideGoldCount(rules) << std::endl;
    return 0;
}