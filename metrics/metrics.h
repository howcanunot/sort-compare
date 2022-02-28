#include "sortings/sortings.h"
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#define MAX_SIZE 4100
#define SORTINGS_COUNT 12
#define GENERATORS_COUNT 4


class Metrics {
    typedef std::vector<int> (Metrics::*generate_functions) ();
    typedef void (*sorting)(std::vector<int>*, int, int);

public:
    Metrics() {
        result_table_small.resize(SORTINGS_COUNT * GENERATORS_COUNT);
        result_table_large.resize(SORTINGS_COUNT * GENERATORS_COUNT);

        csv_file_small = std::ofstream("C:\\Users\\Dova\\source\\repos\\SortrCompare\\sorting_metrics_small.csv");
        csv_file_large = std::ofstream("C:\\Users\\Dova\\source\\repos\\SortrCompare\\sorting_metrics_large.csv");

        writeHeader(csv_file_small);
        writeHeader(csv_file_large);
    }

    ~Metrics() {
        csv_file_small.close();
        csv_file_large.close();
    }

    void start();

private:
    void sortMetrics(std::vector<std::vector<int64_t>>&, int, int, int, int, int);

    std::vector<int> generateOriginalArrayFirst();

    std::vector<int> generateOriginalArraySecond();

    std::vector<int> generateOriginalArrayThird();

    std::vector<int> generateOriginalArrayFourth();

    void writeResult(std::ofstream&, std::vector<std::vector<int64_t>>&, int, int);

    void writeHeader(std::ofstream&);

    void getCurrentSort(int index) {
        switch (index) {
            case 0:
                current_sorting_name = "Bubble sort";
                break;
            case 1:
                current_sorting_name = "Bubble sort with 1 condition";
                break;
            case 2:
                current_sorting_name = "Bubble sort with 2 condition";
                break;
            case 3:
                current_sorting_name = "Insertion sort";
                break;
            case 4:
                current_sorting_name = "Selection sort";
                break;
            case 5:
                current_sorting_name = "Binary insertion sort";
                break;
            case 6:
                current_sorting_name = "Count sort";
                break;
            case 7:
                current_sorting_name = "Radix sort";
                break;
            case 8:
                current_sorting_name = "Heap sort";
                break;
            case 9:
                current_sorting_name = "Merge Sort";
                break;
            case 10:
                current_sorting_name = "Quick Sort Hoare";
                break;
            case 11:
                current_sorting_name = "Quick Sort Lomuto";
                break;
            default:
                throw std::exception("Unknown sorting");
                break;
        }
    }

    void getCurrentGenerator(int index) {
        switch (index) {
            case 0:
                current_array_type = "Random 0-5";
                break;
            case 1:
                current_array_type = "Random 0-4100";
                break;
            case 2:
                current_array_type = "Almost sort";
                break;
            case 3:
                current_array_type = "Reverse sort";
                break;
            default:
                throw std::exception("Unknown generator");
                break;
        }
    }


private:
    const generate_functions generate_functions_array[4] = {
            &Metrics::generateOriginalArrayFirst,
            &Metrics::generateOriginalArraySecond,
            &Metrics::generateOriginalArrayThird,
            &Metrics::generateOriginalArrayFourth
    };

    const sorting sortings_array[12] = {
            &Sortings::bubbleSort,
            &Sortings::bubbleSortWithOneCondition,
            &Sortings::bubbleSortWithTwoCondition,
            &Sortings::insertionSort,
            &Sortings::selectionSort,
            &Sortings::binaryInsertionSort,
            &Sortings::countSort,
            &Sortings::radixSort,
            &Sortings::heapSort,
            &Sortings::mergeSort,
            &Sortings::quickSortHoare,
            &Sortings::quickSortLomuto
    };

    sorting current_sorting_function;
    std::vector<int> array;

    std::ofstream csv_file_small;
    std::ofstream csv_file_large;

    std::string current_sorting_name;
    std::string current_array_type;

    std::vector<std::vector<int64_t>> result_table_small;
    std::vector<std::vector<int64_t>> result_table_large;
};
