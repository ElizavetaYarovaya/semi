#ifndef PUZYRKOVAYA_SORTIROVKA_H
#define PUZYRKOVAYA_SORTIROVKA_H

#include <vector>
#include <utility>

template <typename T>
void bubbleSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

#endif // PUZYRKOVAYA_SORTIROVKA_H