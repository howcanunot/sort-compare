#include "sortings.h"

void Sortings::bubbleSort(std::vector<int>* vec, int left, int right) {
    for (int iter = 0; iter < vec->size() - 1; ++iter) {
        for (int j = 0; j < vec->size() - iter - 1; ++j) {
            if ((*vec)[j] > (*vec)[j + 1]) {
                std::swap((*vec)[j], (*vec)[j + 1]);
            }
        }
    }
}

void Sortings::bubbleSortWithOneCondition(std::vector<int>* vec, int left, int right) {
    int iterator = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int j = 0; j < vec->size() - iterator - 1; ++j) {
            if ((*vec)[j] > (*vec)[j + 1]) {
                std::swap((*vec)[j], (*vec)[j + 1]);
                flag = true;
            }
        }
        ++iterator;
    }
}

void Sortings::bubbleSortWithTwoCondition(std::vector<int>* vec, int left, int right) {
    bool was_swap;
    int last_swap = vec->size() - 1;
    for (int iter = 0; iter < vec->size() - 1; ++iter) {
        was_swap = false;
        int last_swap_iter = 0;
        for (int j = 0; j < last_swap; ++j) {
            if ((*vec)[j] > (*vec)[j + 1]) {
                std::swap((*vec)[j], (*vec)[j + 1]);
                was_swap = true;
                last_swap_iter = j;
            }
        }
        last_swap = last_swap_iter;
        if (!was_swap || last_swap == 0) {
            break;
        }
    }
}

void Sortings::selectionSort(std::vector<int>* vec, int left, int right) {
    for (int iter = 0; iter < vec->size() - 1; ++iter) {
        int min_index = iter;
        for (int j = iter + 1; j < vec->size(); ++j) {
            if ((*vec)[min_index] > (*vec)[j]) {
                min_index = j;
            }
        }

        if (min_index != iter) {
            std::swap((*vec)[iter], (*vec)[min_index]);
        }
    }
}

void Sortings::insertionSort(std::vector<int>* vec, int left, int right) {
    int swap_count = 0;
    bool is_on_place;
    for (int iter = 1; iter < vec->size(); ++iter) {
        is_on_place = true;
        int index = iter - 1;
        int key = (*vec)[iter];
        while (index >= 0 && (*vec)[index] > key) {
            (*vec)[index + 1] = (*vec)[index];
            index--;
            is_on_place = false;
        }
        if (is_on_place) {
            swap_count++;
        }
        (*vec)[index + 1] = key;
    }
}

void Sortings::binaryInsertionSort(std::vector<int>* vec, int left, int right) {
    for (int iter = 1; iter < vec->size(); ++iter) {
        int index = iter - 1;
        int key = (*vec)[iter];
        int pos = Sortings::rbs(*vec, -1, index + 1, key);
        for (int j = index; j > pos; --j) {
            std::swap((*vec)[j], (*vec)[j + 1]);
        }
    }
}

void Sortings::countSort(std::vector<int>* vec, int left, int right) {
    std::vector<int> count(4101, 0);

    for (auto value : *vec) {
        count[value]++;
    }

    // for (int i = 1; i < count.size(); ++i) {
    //     count[i] = vec->at(i - 1) + count[i];
    // }

    // for (int i = vec->size() - 1; i >= 0; --i) {
    //     count[vec->at(i)]--;
    //     (*vec)[count[vec->at(i)]] = (*vec)[i];
    // }
}

void Sortings::radixSort(std::vector<int>* vec, int left, int right) {
    std::vector<int> counter(256, 0);

    auto digit = [](int number, int index) {
        return (number & (255 << (8 * index))) >> (8 * index);
    };

    for (int index = 0; index < sizeof(uint32_t); ++index) {
        for (int j = 0; j < 256; ++j) {
            counter[j] = 0;
        }
        for (int j : *vec) {
            uint32_t digit_value = digit(j, index);
            counter[digit_value]++;
        }
        int count = 0;
        for (int j = 0; j < 256; ++j) {
            int temp = counter[j];
            counter[j] = count;
            count += temp;
        }
        std::vector<int> tmp(vec->size());
        for (int j : *vec) {
            uint32_t digit_value = digit(j, index);
            tmp[counter[digit_value]] = j;
            counter[digit_value]++;
        }
        (*vec) = tmp;
    }
}


void Sortings::heapSort(std::vector<int>* heap, int left, int right) {
    for (int i = heap->size() / 2 - 1; i >= 0; --i) {
        fix(heap, i, heap->size());
    }

    for (int i = heap->size() - 1; i >= 0; --i) {
        std::swap((*heap)[0], (*heap)[i]);
        fix(heap, 0, i);
    }
}

void Sortings::mergeSort(std::vector<int>* vec, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(vec, left, middle);
        mergeSort(vec, middle + 1, right);
        merge(vec, left, middle, middle + 1, right);
    }
}

void Sortings::quickSortHoare(std::vector<int>* vec, int left, int right) {
    if (left < right) {
        auto pivots = partitionHoare(vec, left, right);
        if (pivots.second > left) {
            quickSortHoare(vec, left, pivots.second);
        }
        if (pivots.first < right) {
            quickSortHoare(vec, pivots.first, right);
        }
    }
}

void Sortings::quickSortLomuto(std::vector<int>* vec, int left, int right) {
    if (left < right) {
        int pivot = partitionLomuto(vec, left, right);
        if (left < pivot - 1) {
            quickSortLomuto(vec, left, pivot - 1);
        }
        if (pivot + 1 < right) {
            quickSortLomuto(vec, pivot + 1, right);
        }
    }
}
