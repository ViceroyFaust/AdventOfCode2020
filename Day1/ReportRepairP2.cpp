#include <vector>
#include <iostream>

int main () {
    std::vector<int> list;
    int temp;
    while (std::cin >> temp)
        list.push_back(temp);
    for (int i = 0; i < list.size(); ++i) {
        for (int j = i + 1; j < list.size(); ++j) {
            for (int k = j + 1; k < list.size(); ++k) {
                if (list[i] + list[j] + list[k] == 2020) {
                    std::cout << (list[i] * list[j] * list[k]) << std::endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}