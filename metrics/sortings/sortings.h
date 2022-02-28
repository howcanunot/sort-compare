#include <vector>

class Sortings {
public:
    static void bubbleSort(std::vector<int>*, int, int);

    static void bubbleSortWithOneCondition(std::vector<int>*, int, int);

    static void bubbleSortWithTwoCondition(std::vector<int>*, int, int);

    static void selectionSort(std::vector<int>*, int, int);

    static void insertionSort(std::vector<int>*, int, int);

    static void binaryInsertionSort(std::vector<int>*, int, int);

    static void countSort(std::vector<int>*, int, int);

    static void radixSort(std::vector<int>*, int, int);

    static void heapSort(std::vector<int>*, int, int);

    static void mergeSort(std::vector<int>*, int, int);

    static void quickSortHoare(std::vector<int>*, int, int);

    static void quickSortLomuto(std::vector<int>*, int, int);

private:
    static int rbs(const std::vector<int>& vec, int left, int right, int number) {
        while (left < right - 1) {
            int mid = left + (right - left) / 2;
            if (vec[mid] > number) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return left;
    }

    static void fix(std::vector<int>* heap, int root, int size) {
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        int max = root;

        if (left < size && heap->at(max) < heap->at(left)) {
            max = left;
        }

        if (right < size && heap->at(max) < heap->at(right)) {
            max = right;
        }

        if (max != root) {
            std::swap((*heap)[max], (*heap)[root]);
            fix(heap, max, size);
        }
    }

    static void merge(std::vector<int>* vec, int fleft, int fright, int sleft, int sright) {
        int finals = fleft;
        int findle = sright;
        int index = 0;
        std::vector<int> result(findle - finals + 1);

        while (fleft <= fright && sleft <= sright) {
            if (vec->at(fleft) < vec->at(sleft)) {
                result[index++] = vec->at(fleft);
                fleft++;
            } else {
                result[index++] = vec->at(sleft);
                sleft++;
            }
        }

        if (fleft <= fright) {
            for (int i = fleft; i <= fright; ++i) {
                result[index++] = vec->at(i);
            }
        } else {
            for (int i = sleft; i <= sright; ++i) {
                result[index++] = vec->at(i);
            }
        }

        index = 0;
        for (int i = finals; i <= findle; ++i) {
            (*vec)[i] = result[index++];
        }
    }

    static std::pair<int, int> partitionHoare(std::vector<int>* vec, int left, int right) {
        int pivot_index = left + (right - left) / 2;
        int pivot = vec->at(pivot_index);

        int itf = left, its = right;

        while (itf <= its) {
            while (vec->at(itf) < pivot) {
                itf++;
            }

            while (vec->at(its) > pivot) {
                its--;
            }

            if (itf <= its) {
                std::swap((*vec)[itf++], (*vec)[its--]);
            }
        }

        return {itf, its};
    }

    static int partitionLomuto(std::vector<int>* vec, int left, int right) {
        int pivot = vec->at(right);
        int index = left;
        for (int i = left; i < right; ++i) {
            if (vec->at(i) <= pivot) {
                std::swap((*vec)[index++], (*vec)[i]);
            }
        }
        std::swap((*vec)[right], (*vec)[index]);
        return index;
    }
};
