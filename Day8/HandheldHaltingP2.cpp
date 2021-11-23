#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct Command {
    std::string oper;
    int arg;
    Command(std::string str, int i) : oper(str), arg(i){};
};

struct RunStatus {
    bool isInf;
    int acc;
    RunStatus(bool b, int i) : isInf(b), acc(i) {};
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

void getInput(std::vector<Command>& inputs, std::vector<size_t> jmpAndNopI) {
    std::string strIn;
    size_t i = 0;
    while (std::getline(std::cin, strIn)) {
        auto commandParts = splitString(strIn);
        std::string oper = commandParts[0];
        int arg = std::stoi(commandParts[1]);
        if (oper == "jmp" || oper == "nop")
            jmpAndNopI.push_back(i);
        inputs.push_back(Command(oper, arg));
        ++i;
    }
}

RunStatus runInputCode(const std::vector<Command>& inputs) {
    std::unordered_set<size_t> iHistory;
    bool isLoop = false;
    int accumulator = 0;
    for (size_t i = 0; i < inputs.size(); ++i) {
        isLoop = !iHistory.insert(i).second;
        if (isLoop)
            break;
        Command cmd = inputs[i];
        if (cmd.oper == "acc") {
            accumulator += cmd.arg;
        } else if (cmd.oper == "jmp") {
            i += cmd.arg - 1;  // Because of ++i
        }
    }
    return RunStatus(isLoop, accumulator);
}

int main() {
    std::vector<Command> inputList;
    std::vector<size_t> jmpAndNopIndexes;
    getInput(inputList, jmpAndNopIndexes);
    return 0;
}