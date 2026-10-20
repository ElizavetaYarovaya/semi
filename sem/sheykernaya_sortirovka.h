#ifndef SHEYKERNAYA_SORTIROVKA_H
#define SHEYKERNAYA_SORTIROVKA_H

#include <vector>
#include <utility>

template <typename T>
void shakerSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;
    bool swapped = true;
    while (left < right&& swapped) {
        swapped = false;
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) { std::swap(arr[i], arr[i + 1]); swapped = true; }
        }
        --right;
        if (!swapped) break;
        for (int i = right; i > left; --i) {
            if (arr[i - 1] > arr[i]) { std::swap(arr[i - 1], arr[i]); swapped = true; }
        }
        ++left;
    }
}

#endif // SHEYKERNAYA_SORTIROVKA_H