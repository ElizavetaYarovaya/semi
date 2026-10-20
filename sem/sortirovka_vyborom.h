#ifndef SORTIROVKA_VYBOROM_H
#define SORTIROVKA_VYBOROM_H

#include <vector>
#include <utility>

template <typename T>
void selectionSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) std::swap(arr[i], arr[minIdx]);
    }
}

#endif // SORTIROVKA_VYBOROM_H