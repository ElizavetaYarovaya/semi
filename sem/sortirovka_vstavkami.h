#ifndef SORTIROVKA_VSTAVKAMI_H
#define SORTIROVKA_VSTAVKAMI_H

#include <vector>

template <typename T>
void insertionSort(std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; --j; }
        arr[j + 1] = key;
    }
}

#endif // SORTIROVKA_VSTAVKAMI_H