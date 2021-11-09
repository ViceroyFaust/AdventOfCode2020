#include <iostream>
#include <string>
#include <vector>

enum State {
    state_index1,
    state_index2,
    state_letter,
    state_passcode
};

bool isValid(int index1, int index2, char letter, const std::string& pass) {
    bool index1char = letter == pass[index1];
    bool index2char = letter == pass[index2];
    return index1char xor index2char;
}

int main() {
    int correctCount = 0;
    std::string input;
    // Read until EOF loop
    while (getline(std::cin, input)) {
        int index1 = 0;
        int index2 = 0;
        char letter = '\0';
        std::string passcode = "";
        State state = state_index1;
        std::string iList = "";
        // Parsing loop
        for (char c : input) {
            switch (state) {
                case state_index1:
                    if (c != '-') {
                        iList += c;
                    } else {
                        index1 = stoi(iList);
                        iList = "";
                        state = state_index2;
                    }
                    break;
                case state_index2:
                    if (c != ' ') {
                        iList += c;
                    } else {
                        index2 = stoi(iList);
                        iList = "";
                        state = state_letter;
                    }
                    break;
                case state_letter:
                    if (c != ':') {
                        letter = c;
                    } else {
                        state = state_passcode;
                    }
                    break;
                case state_passcode:
                    if (c != ' ') {
                        passcode += c;
                    }
            }
        }
        if (isValid(index1, index2, letter, passcode))
            ++correctCount;
    }
    std::cout << correctCount << std::endl;
    return 0;
}