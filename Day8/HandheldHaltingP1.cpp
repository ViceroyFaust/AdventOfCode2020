#include <iostream>
#include <string>
#include <vector>

struct Command {
    std::string oper;
    int arg;
    Command(std::string str, int i) : oper(str), arg(i){};
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

void getInput(std::vector<Command>& vec) {
    std::string strIn;
    while (std::getline(std::cin, strIn)) {
        auto commandParts = splitString(strIn);
        std::string oper = commandParts[0];
        int arg = std::stoi(commandParts[1]);
        vec.push_back(Command(oper, arg));
    }
}

int main() {
    std::vector<Command> inputList;
    
    return 0;
}