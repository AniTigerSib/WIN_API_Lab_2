#ifndef WIN_API_LAB_2_ARRAY_FUNCTIONS_H
#define WIN_API_LAB_2_ARRAY_FUNCTIONS_H

#include <vector> // for vectors
#include <random> // for random number generation

void FillArray(int* arr, int size);

int* ArrCpy(const int* src, int* dst, int size);

void BuildHeap(int arr[], int n);
void Heapify(int arr[], int n, int i);
void HeapSort(int arr[], int n);

void Swap(int& a, int& b);
int Partition(int arr[], int low, int high, int pivot);
void QuickSort(int* arr, int low, int high);

#endif //WIN_API_LAB_2_ARRAY_FUNCTIONS_H