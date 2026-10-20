#ifndef ESTESTVENNAYA_SORTIROVKA_SLIYANIEM_H
#define ESTESTVENNAYA_SORTIROVKA_SLIYANIEM_H

#include <fstream>
#include <vector>
#include <string>
#include "dvuhfaznaya_sortirovka_sliyaniem.h"

template <typename T>
void naturalMergeSortFile(const std::string& filename) {
    std::string fileA = filename;
    std::string fileB = "temp_nat_b.bin";
    std::string fileC = "temp_nat_c.bin";
    bool sorted = false;
    while (!sorted) {
        std::ifstream src(fileA, std::ios::binary);
        std::ofstream outB(fileB, std::ios::binary);
        std::ofstream outC(fileC, std::ios::binary);
        T curr, prev;
        if (!src.read(reinterpret_cast<char*>(&curr), sizeof(T))) return;
        bool writeToB = true;
        outB.write(reinterpret_cast<const char*>(&curr), sizeof(T));
        prev = curr;
        size_t series_count = 1;
        while (src.read(reinterpret_cast<char*>(&curr), sizeof(T))) {
            if (curr < prev) { writeToB = !writeToB; series_count++; }
            if (writeToB) outB.write(reinterpret_cast<const char*>(&curr), sizeof(T));
            else outC.write(reinterpret_cast<const char*>(&curr), sizeof(T));
            prev = curr;
        }
        src.close(); outB.close(); outC.close();
        if (series_count <= 1) { sorted = true; break; }
        std::ifstream inB(fileB, std::ios::binary);
        std::ifstream inC(fileC, std::ios::binary);
        std::ofstream dst(fileA, std::ios::binary);
        T valB, valC;
        bool hasB = static_cast<bool>(inB.read(reinterpret_cast<char*>(&valB), sizeof(T)));
        bool hasC = static_cast<bool>(inC.read(reinterpret_cast<char*>(&valC), sizeof(T)));
        while (hasB || hasC) {
            bool endB = !hasB, endC = !hasC;
            T lastB = valB, lastC = valC;
            while (!endB && !endC) {
                if (valB <= valC) {
                    dst.write(reinterpret_cast<const char*>(&valB), sizeof(T));
                    lastB = valB;
                    hasB = static_cast<bool>(inB.read(reinterpret_cast<char*>(&valB), sizeof(T)));
                    if (!hasB || valB < lastB) endB = true;
                }
                else {
                    dst.write(reinterpret_cast<const char*>(&valC), sizeof(T));
                    lastC = valC;
                    hasC = static_cast<bool>(inC.read(reinterpret_cast<char*>(&valC), sizeof(T)));
                    if (!hasC || valC < lastC) endC = true;
                }
            }
            while (!endB) { dst.write(reinterpret_cast<const char*>(&valB), sizeof(T)); lastB = valB; hasB = static_cast<bool>(inB.read(reinterpret_cast<char*>(&valB), sizeof(T))); if (!hasB || valB < lastB) endB = true; }
            while (!endC) { dst.write(reinterpret_cast<const char*>(&valC), sizeof(T)); lastC = valC; hasC = static_cast<bool>(inC.read(reinterpret_cast<char*>(&valC), sizeof(T))); if (!hasC || valC < lastC) endC = true; }
        }
        inB.close(); inC.close(); dst.close();
    }
}

template <typename T>
void naturalMergeSort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;
    std::string filename = "temp_natural.bin";
    writeVectorToFile(filename, arr);
    naturalMergeSortFile<T>(filename);
    arr = readVectorFromFile<T>(filename);
}

#endif // ESTESTVENNAYA_SORTIROVKA_SLIYANIEM_H