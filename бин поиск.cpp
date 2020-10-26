#include <iostream>
#include <vector>

bool Binary_Search(std::vector<int> &vector, int search_value) {
    int search_index;
    int left = 0;
    int right = vector.size();
    while (left < right) {
        search_index = (left + right) / 2;
        if (search_value == vector[search_index]) {
            return true;
        } else if (search_value > vector[search_index]) {
            left = search_index + 1;
        } else {
            right = search_index;
        }
    }
    return false;
}

int Lower_Bound(std::vector<int> &vector, int search_value) {
    int search_index;
    int left = 0;
    int right = vector.size();
    while (left < right) {
        search_index = (left + right) / 2;
        if (search_value <= vector[search_index]) {
            right = search_index;
        } else {
            left = search_index + 1;
        }
    }
    return left;
}
int Upper_Bound(std::vector<int> &vector, int search_value) {
    int search_index;
    int left = 0;
    int right = vector.size();
    while (left < right) {
        search_index = (left + right) / 2;
        if (search_value >= vector[search_index]) {
            left = search_index + 1;
        } else {
            right = search_index;
        }
    }
    return right;
}

int main() {
    int size;
    std::cin >> size;
    std::vector<int> vector(size);
    for (auto &item : vector) {
        std::cin >> item;
    }
    int k;
    std::cin >> k;
    int search_value;
    for (int i = 0; i < k; i++) {
        std::cin >> search_value;
        if (Binary_Search(vector, search_value)) {
            std::cout << 1 << " ";
        } else std::cout << 0 << " ";
        std::cout << Lower_Bound(vector,search_value) << " ";
        std::cout << Upper_Bound(vector,search_value) << std::endl;
    }

    return 0;
}