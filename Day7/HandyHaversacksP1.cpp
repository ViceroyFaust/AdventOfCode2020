#include <iostream>
#include <queue>
#include <set>
#include <string>
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

std::pair<bool, Bag*> bagExists(const std::set<Bag*>& list, const std::string& key) {
    for (Bag* b : list) {
        if (b->name == key)
            return std::pair<bool, Bag*>(true, b);
    }
    return std::pair<bool, Bag*>(false, NULL);
}

std::pair<int, Bag*> extractPair(const std::string& word, const std::set<Bag*>& bagList) {
    if (word == "no other bags.") {
        return std::pair<int, Bag*>(0, NULL);
    }
    std::vector<std::string> words = splitString(word);
    int num = std::stoi(words[0]);
    std::string bagType = words[1] + " " + words[2];
    Bag* bag;
    auto check = bagExists(bagList, bagType);
    if (check.first) {
        bag = check.second;
    } else {
        bag = new Bag;
        bag->name = bagType;
    }
    return std::pair<int, Bag*>(num, bag);
}

std::vector<std::pair<int, Bag*>> extractContainedBags(const std::string& word, const std::set<Bag*>& bagList) {
    std::vector<std::pair<int, Bag*>> output;
    std::vector<std::string> bags = splitString(word, ", ");
    for (std::string str : bags) {
        output.push_back(extractPair(str, bagList));
    }
    return output;
}

std::string extractKey(const std::string& word) {
    std::vector<std::string> keyWordSplit = splitString(word);
    return keyWordSplit[0] + " " + keyWordSplit[1];  // Key is the first two words before "contain"
}

int main() {
    std::set<Bag*> bagsList;
    std::string input;
    while (std::getline(std::cin, input)) {
        auto splitContain = splitString(input, " contain ");
        std::string key = extractKey(splitContain[0]);
        Bag* bag;
        auto exists = bagExists(bagsList, key);
        if (exists.first) {
            bag = exists.second;
        } else {
            bag = new Bag;
            bagsList.insert(bag);
            bag->name = key;
        }
        auto insideBags = extractContainedBags(splitContain[1], bagsList);
        bag->bags = insideBags;
        for (std::pair<int, Bag*> p : bag->bags) {
            if (p.second)
                bagsList.insert(p.second);
        }
    }
    return 0;
}