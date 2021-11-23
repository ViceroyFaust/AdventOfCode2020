#include <iostream>
#include <string>
#include <unordered_set>
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
    getInput(inputList);

    std::unordered_set<size_t> iHistory;
    bool isLoop = false;
    int accumulator = 0;
    auto lastIndex = iHistory.begin(); // To detect the broken index
    for (size_t i = 0; i < inputList.size(); ++i) {
        auto status = iHistory.insert(i);
        isLoop = !status.second;
        if (isLoop) {
            // if there is a loop, change the index causing the loop
            // to jmp from nop OR nop from jmp
            i = *lastIndex;
            Command& cmd = inputList[i];
            if (cmd.oper == "jmp")
                cmd.oper = "nop";
            else
                cmd.oper = "jmp";
            isLoop = false;
        } else {
            lastIndex = status.first;
        }
        Command cmd = inputList[i];
        if (cmd.oper == "acc") {
            accumulator += cmd.arg;
        } else if (cmd.oper == "jmp") {
            i += cmd.arg - 1;  // Because of ++i
        }
    }
    std::cout << isLoop << ": " << accumulator << std::endl;
    return 0;
}