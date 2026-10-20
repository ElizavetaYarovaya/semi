#ifndef OPTIMIZIROVANNAYA_PUZYRKOVAYA_H
#define OPTIMIZIROVANNAYA_PUZYRKOVAYA_H

#include <vector>
#include <utility>

template <typename T>
void optimizedBubbleSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    bool swapped;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < arr.size() - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

#endif // OPTIMIZIROVANNAYA_PUZYRKOVAYA_H