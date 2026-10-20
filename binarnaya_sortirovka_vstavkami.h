#ifndef BINARNAYA_SORTIROVKA_VSTAVKAMI_H
#define BINARNAYA_SORTIROVKA_VSTAVKAMI_H

#include <vector>

template <typename T>
void binaryInsertionSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        int left = 0;
        int right = static_cast<int>(i) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (key < arr[mid]) right = mid - 1;
            else left = mid + 1;
        }
        for (int j = static_cast<int>(i) - 1; j >= left; --j) arr[j + 1] = arr[j];
        arr[left] = key;
    }
}

#endif // BINARNAYA_SORTIROVKA_VSTAVKAMI_H