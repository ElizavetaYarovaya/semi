#ifndef ODNOFAZNAYA_SORTIROVKA_SLIYANIEM_H
#define ODNOFAZNAYA_SORTIROVKA_SLIYANIEM_H

#include <fstream>
#include <vector>
#include <string>
#include "dvuhfaznaya_sortirovka_sliyaniem.h" // Используем функции файлов

template <typename T>
void onePhaseMergeSortFile(const std::string& filename) {
    std::string f[4] = { "temp_1.bin", "temp_2.bin", "temp_3.bin", "temp_4.bin" };
    std::vector<T> initialData = readVectorFromFile<T>(filename);
    if (initialData.size() <= 1) return;
    writeVectorToFile(f[0], initialData);
    std::ifstream src(f[0], std::ios::binary);
    std::ofstream out0(f[2], std::ios::binary);
    std::ofstream out1(f[3], std::ios::binary);
    T val;
    bool toFirst = true;
    while (src.read(reinterpret_cast<char*>(&val), sizeof(T))) {
        if (toFirst) out0.write(reinterpret_cast<const char*>(&val), sizeof(T));
        else out1.write(reinterpret_cast<const char*>(&val), sizeof(T));
        toFirst = !toFirst;
    }
    src.close(); out0.close(); out1.close();
    int in1 = 2, in2 = 3, out1_idx = 0, out2_idx = 1;
    size_t series_len = 1;
    size_t total = initialData.size();
    while (series_len < total) {
        std::ifstream i1(f[in1], std::ios::binary);
        std::ifstream i2(f[in2], std::ios::binary);
        std::ofstream o1(f[out1_idx], std::ios::binary);
        std::ofstream o2(f[out2_idx], std::ios::binary);
        T v1, v2;
        bool h1 = static_cast<bool>(i1.read(reinterpret_cast<char*>(&v1), sizeof(T)));
        bool h2 = static_cast<bool>(i2.read(reinterpret_cast<char*>(&v2), sizeof(T)));
        bool writeToFirstOut = true;
        while (h1 || h2) {
            size_t c1 = 0, c2 = 0;
            auto& currentOut = writeToFirstOut ? o1 : o2;
            while (c1 < series_len && h1 && c2 < series_len && h2) {
                if (v1 <= v2) { currentOut.write(reinterpret_cast<const char*>(&v1), sizeof(T)); h1 = static_cast<bool>(i1.read(reinterpret_cast<char*>(&v1), sizeof(T))); c1++; }
                else { currentOut.write(reinterpret_cast<const char*>(&v2), sizeof(T)); h2 = static_cast<bool>(i2.read(reinterpret_cast<char*>(&v2), sizeof(T))); c2++; }
            }
            while (c1 < series_len && h1) { currentOut.write(reinterpret_cast<const char*>(&v1), sizeof(T)); h1 = static_cast<bool>(i1.read(reinterpret_cast<char*>(&v1), sizeof(T))); c1++; }
            while (c2 < series_len && h2) { currentOut.write(reinterpret_cast<const char*>(&v2), sizeof(T)); h2 = static_cast<bool>(i2.read(reinterpret_cast<char*>(&v2), sizeof(T))); c2++; }
            writeToFirstOut = !writeToFirstOut;
        }
        i1.close(); i2.close(); o1.close(); o2.close();
        std::swap(in1, out1_idx);
        std::swap(in2, out2_idx);
        series_len *= 2;
    }
    std::vector<T> result = readVectorFromFile<T>(f[in1]);
    writeVectorToFile(filename, result);
}

template <typename T>
void onePhaseMergeSort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;
    std::string filename = "temp_one_phase.bin";
    writeVectorToFile(filename, arr);
    onePhaseMergeSortFile<T>(filename);
    arr = readVectorFromFile<T>(filename);
}

#endif // ODNOFAZNAYA_SORTIROVKA_SLIYANIEM_H