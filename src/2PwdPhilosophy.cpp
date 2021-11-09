#include <iostream>
#include <string>
#include <vector>

enum State {
    state_min,
    state_max,
    state_letter,
    state_passcode
};

int main() {
    int min = 0;
    int max = 0;
    char letter = '\0';
    std::string passcode = "";
    State state = state_min;
    std::string input = "";
    std::string iList = "";

    getline(std::cin, input);
    // Parsing loop
    for (char c : input) {
        switch (state) {
            case state_min:
                if (c != '-') {
                    iList += c;
                } else {
                    min = stoi(iList);
                    iList = "";
                    state = state_max;
                }
                break;
            case state_max:
                if (c != ' ') {
                    iList += c;
                } else {
                    max = stoi(iList);
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
    
    return 0;
}