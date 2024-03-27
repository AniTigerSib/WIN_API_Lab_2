#include <iostream>
#include <thread>
#include <Windows.h>
#include "array_functions.h" // contains array functions

#define ARRAY_SIZE 2000000

using namespace std;

struct ArrType {
    int* arr;
};

DWORD WINAPI ThreadFuncHeap(LPVOID lpParam) {
    int* arr = ((ArrType*)lpParam)->arr;
    HeapSort(arr, ARRAY_SIZE);
    ExitThread(0);
}

DWORD WINAPI ThreadFuncQuick(LPVOID lpParam) {
    int* arr = ((ArrType*)lpParam)->arr;
    QuickSort(arr, 0, ARRAY_SIZE - 1);
    ExitThread(0);
}

int main() {
    int* baseArr = (int*)calloc(ARRAY_SIZE, sizeof(int)); // create array with N elements
    FillArray(baseArr, ARRAY_SIZE); // fill array with random numbers

    int* arrForQSort = (int*)calloc(ARRAY_SIZE, sizeof(int));
    arrForQSort = ArrCpy(baseArr, arrForQSort, ARRAY_SIZE);
    int* arrForHeapSort = (int*)calloc(ARRAY_SIZE, sizeof(int));
    arrForHeapSort = ArrCpy(baseArr, arrForHeapSort, ARRAY_SIZE);

    ArrType qSortArr{}, hSortArr{};
    qSortArr.arr = arrForQSort;
    hSortArr.arr = arrForHeapSort;

    /* HeapSort(arrForHeapSort, ARRAY_SIZE);
     QuickSort(arrForQSort, 0, ARRAY_SIZE - 1);

     for (auto* i = arrForHeapSort; i - arrForHeapSort < ARRAY_SIZE; i++) {
         cout << *i << "\t";
     }*/

    // Создание потоков
    HANDLE hThreadHeap = CreateThread(NULL, 0, &ThreadFuncHeap, (LPVOID)(&qSortArr), CREATE_SUSPENDED, NULL);
    HANDLE hThreadQuick = CreateThread(NULL, 0, &ThreadFuncQuick, (LPVOID)(&hSortArr), CREATE_SUSPENDED, NULL);

    ResumeThread(hThreadQuick);
    ResumeThread(hThreadHeap);

    // Дожидаемся завершения
    WaitForSingleObject(hThreadQuick, INFINITE);
    WaitForSingleObject(hThreadHeap, INFINITE);


    // Получение временных характеристик
    FILETIME heapCreateFTime, heapExitFTime, quickCreateFTime, quickExitFTime;
    FILETIME heapKernelFTime, heapUserFTime, quickKernelFTime, quickUserFTime;
    GetThreadTimes(hThreadHeap, &heapCreateFTime, &heapExitFTime, &heapKernelFTime, &heapUserFTime);
    GetThreadTimes(hThreadQuick, &quickCreateFTime, &quickExitFTime, &quickKernelFTime, &quickUserFTime);

    // Преобразуем FILETIME в системное время
    SYSTEMTIME heapCreateSTime, heapExitSTime, quickCreateSTime, quickExitSTime;
    FileTimeToSystemTime(&heapCreateFTime, &heapCreateSTime);
    FileTimeToSystemTime(&heapExitFTime, &heapExitSTime);
    FileTimeToSystemTime(&quickCreateFTime, &quickCreateSTime);
    FileTimeToSystemTime(&quickExitFTime, &quickExitSTime);

    // Вывод временных характеристик потоков
    cout << "Function with Heap sorting creating time:" << endl;
    cout << heapCreateSTime.wYear << "-" << heapCreateSTime.wMonth << "-" << heapCreateSTime.wDay << " " << heapCreateSTime.wHour << ":" << heapCreateSTime.wMinute << ":" << heapCreateSTime.wSecond << "." << heapCreateSTime.wMilliseconds << endl;

    cout << "Function with Heap sorting closing time:" << endl;
    cout << heapExitSTime.wYear << "-" << heapExitSTime.wMonth << "-" << heapExitSTime.wDay << " " << heapExitSTime.wHour << ":" << heapExitSTime.wMinute << ":" << heapExitSTime.wSecond << "." << heapExitSTime.wMilliseconds << endl;

    cout << "Function with Heap sorting operating time in kernel mode:" << endl;
    cout << "  Seconds: " << heapKernelFTime.dwLowDateTime / 10000000 << endl;
    cout << "  Milliseconds: " << heapKernelFTime.dwLowDateTime % 10000000 / 1000 << endl;
    // cout << "  Milliseconds: " << heapKernelFTime.dwLowDateTime << endl;

    cout << "Function with Heap sorting operating time in user mode:" << endl;
    cout << "  Seconds: " << heapUserFTime.dwLowDateTime / 10000000 << endl;
    cout << "  Milliseconds: " << heapUserFTime.dwLowDateTime % 10000000 / 1000 << endl << endl;


    cout << "Function with quick sorting creating time:" << endl;
    cout << quickCreateSTime.wYear << "-" << quickCreateSTime.wMonth << "-" << quickCreateSTime.wDay << " " << quickCreateSTime.wHour << ":" << quickCreateSTime.wMinute << ":" << quickCreateSTime.wSecond << "." << quickCreateSTime.wMilliseconds << endl;

    cout << "Function with quick sorting closing time:" << endl;
    cout << quickExitSTime.wYear << "-" << quickExitSTime.wMonth << "-" << quickExitSTime.wDay << " " << quickExitSTime.wHour << ":" << quickExitSTime.wMinute << ":" << quickExitSTime.wSecond << "." << quickExitSTime.wMilliseconds << endl;

    cout << "Function with quick sorting operating time in kernel mode:" << endl;
    cout << "  Seconds: " << quickKernelFTime.dwLowDateTime / 10000000 << endl;
    cout << "  Milliseconds: " << quickKernelFTime.dwLowDateTime % 10000000 / 1000 << endl;

    cout << "Function with quick sorting operating time in user mode:" << endl;
    cout << "  Seconds: " << quickUserFTime.dwLowDateTime / 10000000 << endl;
    cout << "  Milliseconds: " << quickUserFTime.dwLowDateTime % 10000000 / 1000 << endl << endl;

    CloseHandle(hThreadHeap); // закрываем дескриптор потока
    CloseHandle(hThreadQuick); // закрываем дескриптор потока

    // for (auto* i = arrForHeapSort; i - arrForHeapSort < ARRAY_SIZE; i++) {
    //     cout << *i << "\t";
    // }

    free(baseArr);
    free(arrForQSort);
    free(arrForHeapSort);

    return 0;
}
