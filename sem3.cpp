#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdint>

int Partition(int* a, int n) {
    if (n <= 1) {
        return 0;
    }

    const int& pivot = a[n - 1];
    int i = 0;
    int j = n - 2;
    while (i <= j)
    {
        for (; a[i] < pivot; ++i) {}
        for (; a[j] >= pivot; --j) {}
        if (i < j) {
            std::swap(a[i++], a[j--]);
        }
    }
    std::swap(a[i], a[n - 1]);
    return i;
}

int QuickSelect(int *a, int n, int k) {
    assert(k >= 0);
    assert(k < n);

    int pivotPos = Partition(a, n);
    if (pivotPos == k) {
        return a[k];
    }
    if (k < pivotPos) {
        return QuickSelect(a, pivotPos, k);
    }

    return QuickSelect(a + pivotPos + 1, n - pivotPos - 1, k - pivotPos - 1);
}

template<typename T, typename TGetKey>
void CountingSort2(T* a, int n, TGetKey getKey) {
    int max = getKey(a[0]);
    for (int i = 1; i < n; ++i) {
        if (getKey(a[i]) > max) {
            max = getKey(a[i]);
        }
    }
    int* c = new int[max + 1];
    memset(c, 0, (max + 1) * sizeof(int));

    for (int i = 0; i < n; ++i) {
        ++c[getKey(a[i])];
    } 
    
    for (int i = 1; i <= max; ++i) {
        c[i] += c[i - 1]; // концы групп
    } 

    T* b = new T[n];
    for (int i = n - 1; i >= 0; --i) {
        b[--c[getKey(a[i])]] = a[i]; // проход с конца
    }

    delete[] c;
    for (int i = 0; i < n; ++i) {
        a[i] = b[i];
    }
    delete[] b;
} 

struct Point {
    int X = 0;
    int Y = 0;
};

int main() {
   // Point arr[5] = { {2, 3}, {7, 1}, {8, 8}, {3, 100}, {222, 5}};
   // CountingSort2(arr, 5, [](const Point& p){ return p.X; });
    
    // for (int i = 0; i < 5; ++i) {
    //    std::cout << "{" << arr[i].X << ";" << arr[i].Y << "} ";
    // }
    
    int arr[5] = {333, 555, 444, 213, 13};
    CountingSort2(arr, 5, [](const int& p){ return p % 10;});
    CountingSort2(arr, 5, [](const int& p){ return p / 10 % 10;});
    CountingSort2(arr, 5, [](const int& p){ return p / 100 % 10;});

    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    
    std::cout << std::endl;

    return 0;
}