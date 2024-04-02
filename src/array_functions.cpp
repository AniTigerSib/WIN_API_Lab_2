#include "array_functions.h"

using namespace std;

void FillArray(int* arr, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 100000);

    for (int* i = arr; i - arr < size; i++) {
        *i = dist(gen);
    }
}

int* ArrCpy(const int* src, int* dst, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
    return dst;
}

void BuildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        Heapify(arr, n, i);
    }
}

void Heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        Swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

void HeapSort(int arr[], int n) {
    BuildHeap(arr, n);

    for (int i = n - 1; i >= 0; --i) {
        Swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}


void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int Partition(int arr[], int low, int high, int pivot) {
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            Swap(arr[i], arr[j]);
        }
    }
    Swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void QuickSort(int* arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];

        int partitionIndex = Partition(arr, low, high, pivot);

        QuickSort(arr, low, partitionIndex - 1);
        QuickSort(arr, partitionIndex + 1, high);
    }
}