/* #include <iostream>

int leftBound(int* arr, int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        size_t mid = (left + right) / 2;

        if (arr[mid] >= target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int n;
    std::cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int k;
    std::cin >> k;

    int ans = leftBound(arr, n, k);
    std::cout << ans << "\n";
} 


#include <iostream>

struct Container {
    int a = 0;
    int b = 0;
    int c = 0; 
    int originalIndex = 0;
};

inline void myswap(int& x, int& y) { int t = x; x = y; y = t; }

bool isLessContainer(const Container& x, const Container& y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

void insertionSort(Container* arr, int n,
                   bool (*cmp)(const Container&, const Container&)) {
    for (int i = 1; i < n; ++i) {
        Container key = arr[i];
        int j = i - 1;
        while (j >= 0 && cmp(key, arr[j])) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int main() {

    int n;
    if (!(std::cin >> n)) return 0;

    Container* arr = new Container[n];

    for (int i = 0; i < n; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;

        if (x > y) myswap(x, y);
        if (y > z) myswap(y, z);
        if (x > y) myswap(x, y); 

        arr[i].a = x; arr[i].b = y; arr[i].c = z;
        arr[i].originalIndex = i; 
    }

    insertionSort(arr, n, isLessContainer);

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i].originalIndex << (i + 1 == n ? '\n' : ' ');
    }

    delete[] arr;
    return 0;
}
*/


#include <iostream>
#include <string>

using namespace std;

class Stack {
private:
    char* data;
    int capacity;
    int topIndex;
    
public:
    Stack(int size) {
        capacity = size;
        data = new char[capacity];
        topIndex = -1;
    }
    
    ~Stack() {
        delete[] data;
    }
    
    void push(char c) {
        data[++topIndex] = c;
    }
    
    char pop() {
        return data[topIndex--];
    }
    
    char top() {
        return data[topIndex];
    }
    
    bool empty() {
        return topIndex == -1;
    }
};

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    
    int n = s1.length();
    Stack st(n);
    
    int i = 0, j = 0;
    
    while (j < s2.length()) {
        if (!st.empty() && st.top() == s2[j]) {
            st.pop();
            j++;
        } else if (i < s1.length()) {
            st.push(s1[i]);
            i++;
        } else {
            cout << "NO" << endl;
            return 0;
        }
    }
    
    cout << "YES" << endl;
    return 0;
}