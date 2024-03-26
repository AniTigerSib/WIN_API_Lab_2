#include <iostream>
#include "array_functions.h" // contains array functions
#include <Windows.h>

using namespace std;

DWORD WINAPI ThreadFuncMerge(LPVOID lpParam) {
    auto* arr = (vector<int>*)lpParam;
    MergeSort(*arr);
    return 0;
}

DWORD WINAPI ThreadFuncQuick(LPVOID lpParam) {
    auto* arr = (vector<int>*)lpParam;
    QuickSort(*arr);
    return 0;
}

int main() {
    vector<int> arr;
    FillArray(arr); // fill array with random numbers
    vector<int> arrForMerge;
    vector<int> arrForQuick;
    // copy source array to vectors for merge sorting and quick sorting
    copy(arr.begin(), arr.end(), arrForMerge.begin());
    copy(arr.begin(), arr.end(), arrForQuick.begin());

    // Создание потоков
    HANDLE hThreadMerge = CreateThread(NULL, 0, ThreadFuncMerge, &arrForMerge, 0, NULL);
    HANDLE hThreadQuick = CreateThread(NULL, 0, ThreadFuncQuick, &arrForQuick, 0, NULL);

    // Дожидаемся завершения
    WaitForSingleObject(hThreadMerge, INFINITE);
    WaitForSingleObject(hThreadQuick, INFINITE);

    // Получение временных характеристик
    DWORD time_main = GetTickCount();
    LPFILETIME mergeCreate, mergeExit, quickCreate, quickExit;
    LPFILETIME mergeKernel, mergeUser, quickKernel, quickUser;
    GetThreadTimes(hThreadMerge, mergeCreate, mergeExit, mergeKernel, mergeUser);
    GetThreadTimes(hThreadQuick, quickCreate, quickExit, quickKernel, quickUser);


    return 0;
}
