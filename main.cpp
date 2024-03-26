#include <iostream>
#include <vector>
#include <random>

using namespace std;

void fill_array(vector<int>& arr) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1000);

    for (int & i : arr) {
        i = dist(gen);
    }
}

void merge_sort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    int mid = (int) arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    merge_sort(left);
    merge_sort(right);

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left.size()) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right.size()) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void quick_sort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    int pivot = arr[arr.size() / 2];
    vector<int> left;
    vector<int> right;

    for (int i : arr) {
        if (i < pivot) {
            left.push_back(i);
        } else if (i > pivot) {
            right.push_back(i);
        }
    }

    quick_sort(left);
    quick_sort(right);

    arr.clear();
    arr.insert(arr.end(), left.begin(), left.end());
    arr.insert(arr.end(), right.begin(), right.end());
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
