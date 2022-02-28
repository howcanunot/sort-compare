#include "metrics.h"

using namespace std::chrono;

std::vector<int> Metrics::generateOriginalArrayFirst() {
    std::vector<int> vec(MAX_SIZE);

    for (auto& value : vec) {
        value = rand() % 6;
    }

    return std::move(vec);
}

std::vector<int> Metrics::generateOriginalArraySecond() {
    std::vector<int> vec(MAX_SIZE);

    for (auto& value : vec) {
        value = rand() % 4001;
    }

    return std::move(vec);
}

std::vector<int> Metrics::generateOriginalArrayThird() {
    std::vector<int> vec(MAX_SIZE);

    for (auto& value : vec) {
        value = rand() % 6;
    }

    return std::move(vec);
}

std::vector<int> Metrics::generateOriginalArrayFourth() {
    std::vector<int> vec(MAX_SIZE);

    for (auto& value : vec) {
        value = 1 + rand() % 4100;
    }

    std::sort(vec.begin(), vec.end());
    std::reverse(vec.begin(), vec.end());

    return std::move(vec);
}

void Metrics::sortMetrics(std::vector<std::vector<int64_t>>& table, int left,
                          int right, int step, int index_sort, int index_generator)
    {
    int index = index_sort * 4 + index_generator;
    for (int elements = left; elements <= right; elements += step) {
        std::vector<int> vec(array.begin(), (array.begin() + elements));

        auto start = high_resolution_clock::now();
        (*current_sorting_function)(&vec, 0, vec.size() - 1);
        auto end = high_resolution_clock::now();

        auto sort_time = duration_cast<microseconds>(end - start).count();

        table[index].push_back(sort_time);
    }
    std::cout << current_sorting_name << "finished\n" ;
}

void Metrics::start() {
    for (int i = 0; i < SORTINGS_COUNT; i++) {
        current_sorting_function = sortings_array[i];
        getCurrentSort(i);

        for (int j = 0; j < GENERATORS_COUNT; j++) {
            array = (this->*(generate_functions_array[j]))();
            sortMetrics(result_table_small, 50, 300, 10, i, j);
            sortMetrics(result_table_large, 100, 4100, 100, i, j);
        }
    }

    writeResult(csv_file_small, result_table_small, 50, 10);
    writeResult(csv_file_large, result_table_large, 100, 100);
}

void Metrics::writeHeader(std::ofstream& file) {
    file << "Array size;";

    std::string separator;
    for (int i = 0; i < SORTINGS_COUNT; i++) {
        getCurrentSort(i);
        for (int j = 0; j < GENERATORS_COUNT; j++) {
            file << separator;
            getCurrentGenerator(j);
            separator = ";";
            file << current_sorting_name << " " <<
                           current_array_type;
        }
    }

    file << "\n";
}

void Metrics::writeResult(std::ofstream& file, std::vector<std::vector<int64_t>>& table, int start, int step) {
    std::string separator;

    for (int i = 0; i < table[0].size(); i++) {
        file << start + i * step << ";";
        for (int j = 0; j < table.size(); j++) {
            file << separator;
            separator = ";";
            file << table[j][i];
        }

        file << "\n";
        separator = "";
    }
}
