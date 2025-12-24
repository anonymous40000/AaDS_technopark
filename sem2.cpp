#include <iostream>

struct Point
{
    int X = 0;
    int Y = 0;
};

/* bool operator < (const Point& l, const Point &r) {
    return l.Y < r.Y;
} */

bool isLessByX (const Point& l, const Point &r) {
    return l.X < r.X;
}

bool isLessByY (const Point& l, const Point &r) {
    return l.Y < r.Y;
}

template<typename T>
bool isLessDefault(const T& l, const T& r) {
    return l < r;
}

struct isLessCmpByDx {
    isLessCmpByDx(int _x) : x(_x) {}
    bool operator()(const Point& l, const Point &r){
        return std::abs(l.X - x) < std::abs(r.X - x);
    }
private:
    int x;
};

template<typename T>
struct isLessCmpDefault{
    bool operator()(const T& l, const T& r){
        return l < r;
    }
};
/*
template<typename T, typename IsLess>>
class Heap {
public:
    Heap(IsLess isLess);
    Heap (T* arr, int size, IsLess less);

    void Add (const T& el);
    T Extract();
    const T& Peek();
private:

}; */


template<typename T, typename IsLessCmp = isLessCmpDefault<T>>
void MegaSort(T* arr, int l, int r, IsLessCmp isLess = IsLessCmp()) /*bool isLess(const T&, const T&) = isLessDefault*/
{
    for (int i = l; i < r; ++i) {
        for (int j = l; j < r; ++j) {
            if (isLess(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template<typename T>
void printArray(T* arr, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int intArr[5] = {3, 1, 0, 2, 7};
    MegaSort(intArr, 0, 4);
    
    printArray(intArr, 5);

    char charArr[5] = {'c', 'a', 'z', 'b', 'd'};
    MegaSort(charArr, 0, 4);

    printArray(charArr, 5);

    Point ptArr[5] = {{3, 1}, {0, 2}, {7, 5}, {2, 2}, {3, 9}};
    isLessCmpByDx isLess(0);
    int x = 5;
    MegaSort(ptArr, 0, 4, [x](const Point& l, const Point &r){return std::abs(l.X - x) < std::abs(r.X - x);});
    /* printArray(ptArr, 5);*/
    for (int i = 0; i < 5; ++i) {
        std::cout << "{" << ptArr[i].X << ", " << ptArr[i].Y << "} ";
    }
    std::cout << "\n";

    return 0;
}