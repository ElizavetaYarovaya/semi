#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// --- 1. Базовые сортировки ---
#include "sortirovka_vstavkami.h"
#include "sortirovka_obmenom.h"
#include "sortirovka_vyborom.h"
#include "puzyrkovaya_sortirovka.h"
#include "optimizirovannaya_puzyrkovaya.h"

// --- 2. Бинарная вставка и Шейкер ---
#include "binarnaya_sortirovka_vstavkami.h"
#include "sheykernaya_sortirovka.h"

// --- 3. Быстрая и Шелла ---
#include "bystraya_sortirovka.h"
#include "sortirovka_shella.h"

// --- 4. Слияния ---
#include "dvuhfaznaya_sortirovka_sliyaniem.h"
#include "odnofaznaya_sortirovka_sliyaniem.h"
#include "estestvennaya_sortirovka_sliyaniem.h"

TEST_CASE("Insertion Sort Tests", "[insertion]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 5, 3, 1, 4, 2 };
        insertionSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Пустой массив") {
        std::vector<int> arr = {};
        insertionSort(arr);
        REQUIRE(arr.empty());
    }
    SECTION("Один элемент") {
        std::vector<int> arr = { 42 };
        insertionSort(arr);
        REQUIRE(arr == std::vector<int>{42});
    }
    SECTION("Уже отсортирован") {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        insertionSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Отрицательные числа") {
        std::vector<int> arr = { -3, -1, -2, 0, 5 };
        insertionSort(arr);
        REQUIRE(arr == std::vector<int>{-3, -2, -1, 0, 5});
    }
}

TEST_CASE("Exchange Sort Tests", "[exchange]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 5, 3, 1, 4, 2 };
        exchangeSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Пустой массив") {
        std::vector<int> arr = {};
        exchangeSort(arr);
        REQUIRE(arr.empty());
    }
    SECTION("Дубликаты") {
        std::vector<int> arr = { 3, 1, 3, 2, 1 };
        exchangeSort(arr);
        REQUIRE(arr == std::vector<int>{1, 1, 2, 3, 3});
    }
}

TEST_CASE("Selection Sort Tests", "[selection]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 5, 3, 1, 4, 2 };
        selectionSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Пустой массив") {
        std::vector<int> arr = {};
        selectionSort(arr);
        REQUIRE(arr.empty());
    }
    SECTION("Обратный порядок") {
        std::vector<int> arr = { 5, 4, 3, 2, 1 };
        selectionSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
}

TEST_CASE("Bubble Sort Tests", "[bubble]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 5, 3, 1, 4, 2 };
        bubbleSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Пустой массив") {
        std::vector<int> arr = {};
        bubbleSort(arr);
        REQUIRE(arr.empty());
    }
    SECTION("Один элемент") {
        std::vector<int> arr = { 1 };
        bubbleSort(arr);
        REQUIRE(arr == std::vector<int>{1});
    }
}

TEST_CASE("Optimized Bubble Sort Tests", "[opt_bubble]") {
    SECTION("Обратный порядок") {
        std::vector<int> arr = { 5, 4, 3, 2, 1 };
        optimizedBubbleSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Уже отсортирован (должен быстро выйти)") {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        optimizedBubbleSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Тип double") {
        std::vector<double> arr = { 3.14, 1.41, 2.71 };
        optimizedBubbleSort(arr);
        REQUIRE(arr == std::vector<double>{1.41, 2.71, 3.14});
    }
}

TEST_CASE("Binary Insertion Sort Tests", "[binary_insertion]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 7, 2, 5, 1, 9, 3 };
        binaryInsertionSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 5, 7, 9});
    }
    SECTION("Пустой массив") {
        std::vector<int> arr = {};
        binaryInsertionSort(arr);
        REQUIRE(arr.empty());
    }
    SECTION("Дубликаты") {
        std::vector<int> arr = { 5, 5, 2, 2, 1 };
        binaryInsertionSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 2, 5, 5});
    }
}

TEST_CASE("Shaker Sort Tests", "[shaker]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 4, 3, 2, 1, 5, 0 };
        shakerSort(arr);
        REQUIRE(arr == std::vector<int>{0, 1, 2, 3, 4, 5});
    }
    SECTION("Уже отсортирован") {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        shakerSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Дубликаты") {
        std::vector<int> arr = { 2, 1, 2, 1, 0 };
        shakerSort(arr);
        REQUIRE(arr == std::vector<int>{0, 1, 1, 2, 2});
    }
}


TEST_CASE("Shell Sort Tests", "[shell]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 12, 34, 54, 2, 3 };
        shellSort(arr);
        REQUIRE(arr == std::vector<int>{2, 3, 12, 34, 54});
    }
    SECTION("Один элемент") {
        std::vector<int> arr = { 1 };
        shellSort(arr);
        REQUIRE(arr == std::vector<int>{1});
    }
    SECTION("Отрицательные") {
        std::vector<int> arr = { -5, 2, -10, 0 };
        shellSort(arr);
        REQUIRE(arr == std::vector<int>{-10, -5, 0, 2});
    }
}

TEST_CASE("Quick Sort Tests", "[quick]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 10, 7, 8, 9, 1, 5 };
        quickSort(arr);
        REQUIRE(arr == std::vector<int>{1, 5, 7, 8, 9, 10});
    }
    SECTION("Пустой массив") {
        std::vector<int> arr = {};
        quickSort(arr);
        REQUIRE(arr.empty());
    }
    SECTION("Уже отсортирован") {
        std::vector<int> arr = { 1, 2, 3, 4 };
        quickSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4});
    }
}

TEST_CASE("Two-Phase Merge Sort Tests", "[two_phase]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 9, 3, 7, 5, 6, 1, 4, 2, 8 };
        twoPhaseMergeSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    }
    SECTION("Пустой массив") {
        std::vector<int> arr = {};
        twoPhaseMergeSort(arr);
        REQUIRE(arr.empty());
    }
    SECTION("Тип double") {
        std::vector<double> arr = { 10.5, 4.2, 2.1, 0.0 };
        twoPhaseMergeSort(arr);
        REQUIRE(arr == std::vector<double>{0.0, 2.1, 4.2, 10.5});
    }
}

TEST_CASE("One-Phase Merge Sort Tests", "[one_phase]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 12, 11, 13, 5, 6, 7 };
        onePhaseMergeSort(arr);
        REQUIRE(arr == std::vector<int>{5, 6, 7, 11, 12, 13});
    }
    SECTION("Один элемент") {
        std::vector<int> arr = { 42 };
        onePhaseMergeSort(arr);
        REQUIRE(arr == std::vector<int>{42});
    }
}

TEST_CASE("Natural Merge Sort Tests", "[natural]") {
    SECTION("Обычный массив") {
        std::vector<int> arr = { 1, 2, 10, 3, 4, 5, 2, 8 };
        naturalMergeSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 2, 3, 4, 5, 8, 10});
    }
    SECTION("Уже отсортирован") {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        naturalMergeSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
    SECTION("Обратный порядок") {
        std::vector<int> arr = { 5, 4, 3, 2, 1 };
        naturalMergeSort(arr);
        REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
    }
}