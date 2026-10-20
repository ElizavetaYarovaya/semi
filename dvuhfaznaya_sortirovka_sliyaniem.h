#ifndef DVUHFAZNAYA_SORTIROVKA_SLIYANIEM_H
#define DVUHFAZNAYA_SORTIROVKA_SLIYANIEM_H

#include <fstream>
#include <vector>
#include <string>

template <typename T>
void writeVectorToFile(const std::string& filename, const std::vector<T>& data) {
    std::ofstream out(filename, std::ios::binary);
    for (const auto& item : data) out.write(reinterpret_cast<const char*>(&item), sizeof(T));
}

template <typename T>
std::vector<T> readVectorFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    std::vector<T> data;
    T item;
    while (in.read(reinterpret_cast<char*>(&item), sizeof(T))) data.push_back(item);
    return data;
}

template <typename T>
void twoPhaseMergeSortFile(const std::string& filename) {
    std::string fileA = filename;
    std::string fileB = "temp_b.bin";
    std::string fileC = "temp_c.bin";
    std::ifstream in(fileA, std::ios::binary | std::ios::ate);
    if (!in.is_open()) return;
    size_t total_elements = in.tellg() / sizeof(T);
    in.close();
    if (total_elements <= 1) return;
    size_t series_len = 1;
    while (series_len < total_elements) {
        std::ifstream src(fileA, std::ios::binary);
        std::ofstream outB(fileB, std::ios::binary);
        std::ofstream outC(fileC, std::ios::binary);
        T val;
        size_t count = 0;
        bool writeToB = true;
        while (src.read(reinterpret_cast<char*>(&val), sizeof(T))) {
            if (writeToB) outB.write(reinterpret_cast<const char*>(&val), sizeof(T));
            else outC.write(reinterpret_cast<const char*>(&val), sizeof(T));
            count++;
            if (count % series_len == 0) writeToB = !writeToB;
        }
        src.close(); outB.close(); outC.close();

        std::ifstream inB(fileB, std::ios::binary);
        std::ifstream inC(fileC, std::ios::binary);
        std::ofstream dst(fileA, std::ios::binary);
        T valB, valC;
        bool hasB = static_cast<bool>(inB.read(reinterpret_cast<char*>(&valB), sizeof(T)));
        bool hasC = static_cast<bool>(inC.read(reinterpret_cast<char*>(&valC), sizeof(T)));
        while (hasB || hasC) {
            size_t iB = 0, iC = 0;
            while (iB < series_len && hasB && iC < series_len && hasC) {
                if (valB <= valC) {
                    dst.write(reinterpret_cast<const char*>(&valB), sizeof(T));
                    hasB = static_cast<bool>(inB.read(reinterpret_cast<char*>(&valB), sizeof(T)));
                    iB++;
                }
                else {
                    dst.write(reinterpret_cast<const char*>(&valC), sizeof(T));
                    hasC = static_cast<bool>(inC.read(reinterpret_cast<char*>(&valC), sizeof(T)));
                    iC++;
                }
            }
            while (iB < series_len && hasB) { dst.write(reinterpret_cast<const char*>(&valB), sizeof(T)); hasB = static_cast<bool>(inB.read(reinterpret_cast<char*>(&valB), sizeof(T))); iB++; }
            while (iC < series_len && hasC) { dst.write(reinterpret_cast<const char*>(&valC), sizeof(T)); hasC = static_cast<bool>(inC.read(reinterpret_cast<char*>(&valC), sizeof(T))); iC++; }
        }
        inB.close(); inC.close(); dst.close();
        series_len *= 2;
    }
}

template <typename T>
void twoPhaseMergeSort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;
    std::string filename = "temp_two_phase.bin";
    writeVectorToFile(filename, arr);
    twoPhaseMergeSortFile<T>(filename);
    arr = readVectorFromFile<T>(filename);
}

#endif // DVUHFAZNAYA_SORTIROVKA_SLIYANIEM_H