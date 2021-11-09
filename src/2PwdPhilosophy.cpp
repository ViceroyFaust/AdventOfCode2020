#include <iostream>
#include <string>
#include <vector>

enum State {
    state_min,
    state_max,
    state_letter,
    state_passcode
};

bool isValid(int min, int max, char letter, const std::string& pass) {
    int count = 0;
    for (char c : pass)
        if (c == letter)
            count++;
    if (count >= min && count <= max)
        return true;
    return false;
}

int main() {
    int correctCount = 0;
    std::string input;
    // Read until EOF loop
    while (getline(std::cin, input)) {
        int min = 0;
        int max = 0;
        char letter = '\0';
        std::string passcode = "";
        State state = state_min;
        std::string iList = "";
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
        if (isValid(min, max, letter, passcode))
            ++correctCount;
    }
    std::cout << correctCount << std::endl;
    return 0;
}