#ifndef SORTIROVKA_SHELLA_H
#define SORTIROVKA_SHELLA_H

#include <vector>

template <typename T>
void shellSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    size_t n = arr.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            T temp = arr[i];
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

#endif // SORTIROVKA_SHELLA_H