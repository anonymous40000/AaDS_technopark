/*  
1.4. Инвертирование бита
Ограничение времени	1 секунда
Ограничение памяти	64Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt
Инвертируйте значение бита в числе N по его номеру K.

Необходимо использование битовых операций.
Использование арифметических операций запрещено.

Формат ввода
Сначала вводится число N.
Оно лежит в диапазоне 0..
2
32
2 
32
 -1 и вводится в десятичном виде.
Далее вводится номер бита K.
Лежит в диапазоне 0..31 и вводится в десятичном виде.

Формат вывода
Выходное число выводится в десятичном виде.

#include <iostream>

using namespace std;

u_int32_t k_bit_inversion(u_int32_t N, int16_t K) {
    return (N ^ (1 << K)); // мы берем такое число, которое имеет единицу в к-ом бите, соответственно если в числе N на K-ом месте единица, то остается 0, иначе - 1, 
                           // то есть как раз инверсия происходит
}

int main () {
    u_int32_t N;
    int16_t K;
    std::cin >> N >> K;

    u_int32_t result = k_bit_inversion(N, K);
    std::cout << result << '\n';
}

// 25 = 16 + 8 + 1 -> 00000000 00000000 00000000 00011001 ^ (1 << K), это пример на котором я выводил формулу





2.3. Пересечение множеств
Ограничение времени	0.05 секунд
Ограничение памяти	4Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt
Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение. 
Требуемое время работы: O(m * log k), 
где k - позиция элементта B[m-1] в массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.


// сдаю предыдущее решение так как моя попытка оптимизировать не сработала, здесь асимптотика также удовлетворительна

#include <iostream>
#include <cassert>

using namespace std;

int binary_search(int arr[], int key, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// экспоненциальный поиск, начинаем с позиции start
int exponential_search(int arr[], int size, int key, int start) {
    if (start >= size)
        return -1;

    int bound = 1;
    int left = start;
    int right = start + bound;

    // расширяем границу экспоненциально, пока не выйдем за key
    while (right < size && arr[right] < key) {
        left = right;
        bound *= 2;
        right = start + bound;
    }

    if (right >= size)
        right = size - 1;

    return binary_search(arr, key, left, right);
}

int* intersection(int n, int m, int a[], int b[], int &result_size) {
    int* res = new int[min(n, m)];
    result_size = 0;

    int start = 0; 

    for (int i = 0; i < m; ++i) {
        int pos = exponential_search(a, n, b[i], start);
        if (pos != -1) {
            res[result_size++] = b[i];
            start = pos; // продолжаем с найденной позиции
        } else {
            // если не нашли, двигаем старт вперёд, чтобы не застрять
            while (start < n && a[start] < b[i])
                ++start;
        }
    }
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;

    // надо создавать по new
    int* a = new int[n];
    int* b = new int[m];
    
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    int result_size;
    int* result = intersection(n, m, a, b, result_size);

    for (int i = 0; i < result_size; ++i) {
        cout << result[i] << " ";
    }
    cout << "\n";

    // delete[] result; надо создавать там же где и удалять
    delete[] a;
    delete[] b;
    delete[] result;
    
    return 0;
}





3.2. Дек с динамическим буфером
Полное решение
Ограничение времени	1 секунда
Ограничение памяти	10Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt
Реализовать дек с динамическим зацикленным буфером.

Обрабатывать команды push * и pop *.

Формат ввода
В первой строке количество команд n.
n≤1000000.

Каждая команда задаётся как 2 целых числа ab.

a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Если дана команда pop *, то число b - ожидаемое значение. 
Если команда pop * вызвана для пустой структуры данных, 
то ожидается “-1”.


#include <iostream>
#include <cassert>

using namespace std;

class Deque {
private:
    void growBuffer() 
    {
        if (size == bufferSize) {
            increase_buffer(bufferSize * 2);
        }
    }

    void increase_buffer (size_t new_bufferSize) {
        int* newBuffer = new int[new_bufferSize];

        for (size_t i = 0; i < size; ++i) {
            newBuffer[i] = buffer[(head + i) % bufferSize];
        }

        delete[] buffer;
        buffer = newBuffer;
        bufferSize = new_bufferSize;
        head = 0;
        tail = size;
    }

    int* buffer;
    size_t bufferSize;
    size_t size;
    size_t head;
    size_t tail;
public:
    Deque() : bufferSize(1), size(0), head(0), tail(0) {
        buffer = new int[bufferSize];
    }

    ~Deque()
    {
        delete[] buffer;
    };

    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;

    void push_front(int data) 
    {
        growBuffer(); // если заполненный буфер, то увеличиваем его (реализация динамики)
        if (head == 0) { // если голова нулевая уходим в конец буфера, обеспечиваем закольцованность 
            head = bufferSize - 1;
        } else {
            --head;
        }
        buffer[head] = data;
        ++size;
    };

    int pop_front() {
        assert(size > 0); 
        int returned_data = buffer[head];
        head = (head + 1) % bufferSize; // модуль используем для закольцованности 
        --size;
        return returned_data;
    }

    void push_back(int data) {
        growBuffer();
        buffer[tail] = data;
        tail = (tail + 1) % bufferSize; // аналогично pop_front
        ++size;
    }
    int pop_back() {
        assert(size > 0);
        if (tail == 0) { // аналогично push_front
            tail = bufferSize - 1;
        } else {
            --tail;
        }
        int returned_data = buffer[tail];
        --size;
        return returned_data;
    };

    bool IsEmpty() const
    {
        return (size == 0);
    };
};

int main() {
    Deque deque;
    int n = 0;
    std::cin >> n;
    bool result = true;
    for (int i = 0; i < n; ++i) {
        int command = 0;
        int data = 0;
        std::cin >> command >> data;
        switch (command) {
        case 1:
            deque.push_front(data);
            break;
        case 2:
            if (deque.IsEmpty()) {
                result = result && data == -1;
            } else {
                result = result && deque.pop_front() == data;
            }
            break;
        case 3:
            deque.push_back(data);
            break;
        case 4:
            if (deque.IsEmpty()) {
                result = result && data == -1;
            } else {
                result = result && deque.pop_back() == data;
            }
            break;
        default:
            assert(false);
        }
    }

    std::cout << (result ? "YES" : "NO") << std::endl;
    return 0;
}





4.2. Топ K пользователей из лога
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости.
Количество заходов и идентификаторы пользователей не повторяются.

Требования:

Время работы O(N * logK)
Куча должна быть реализована в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
Формат ввода
Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).

Формат вывода
Идентификаторы пользователей в порядке возрастания посещаемости.


#include <iostream>
#include <stdexcept>

template<typename T, typename IsLess>
class Heap {
public:
    Heap(IsLess isLess)
        : isLess(isLess), buffer(nullptr), bufferSize(0), size(0) {}

    Heap(T* arr, size_t n, IsLess less)
        : isLess(less), buffer(nullptr), bufferSize(0), size(0)
    {
        heapify(arr, n);
    } // конструктор для кучи, делаем кучу из массива

    ~Heap() { delete[] buffer; }
    Heap(const Heap&) = delete;
    Heap& operator=(const Heap&) = delete;

    void Add(const T& el) {
        growBuffer();
        buffer[size] = el;
        ++size;
        siftUp(size - 1);
    }
    
    T Extract() {
        if (size == 0) {
            throw std::runtime_error("extract from empty heap"); // из пустой кучи извлекать нельзя, это невалидное поведение
        }
        T result = buffer[0]; 
        buffer[0] = buffer[size - 1];  
        --size;
        if (size > 0) siftDown(0);
        return result;
    } // извлекаем минимум (у нас в задаче min heap)

    const T& Peek() const {
        if (size == 0) {
            static T tmp{};
            return tmp;
        }
        return buffer[0];
    } // смотрим минимум (у нас в задаче min heap)

    size_t Size() const { return size; }

    bool Empty() const { return size == 0; }

private:
    IsLess isLess;
    T* buffer;
    size_t bufferSize;
    size_t size;

    void heapify(T* arr, size_t n) {
        if (arr == nullptr || n == 0) return;
        
        delete[] buffer;
        buffer = new T[n];
        bufferSize = size = n;
        for (size_t i = 0; i < n; ++i) buffer[i] = arr[i];
        
        for (long i = (long)(n / 2) - 1; i >= 0; --i)
            siftDown((size_t)i);
    } // массив в кучу 

    void growBuffer() {
        if (size == bufferSize) {
            size_t new_bufferSize = (bufferSize == 0) ? 1 : bufferSize * 2;
            increase_buffer(new_bufferSize);
        }
    } // увеличиваем буфер

    void increase_buffer(size_t new_bufferSize) {
        T* newBuffer = new T[new_bufferSize];
        for (size_t i = 0; i < size; ++i)
            newBuffer[i] = buffer[i];
        delete[] buffer;
        buffer = newBuffer;
        bufferSize = new_bufferSize;
    } // сам механизм увеличения буфера

    void siftUp(size_t index) {
        // итеративно
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (isLess(buffer[index], buffer[parent])) {
                std::swap(buffer[index], buffer[parent]);
                index = parent;
            } else {
                break;
            }
        }
    } // просеивание вверх

    void siftDown(size_t index) {
        // итеративно
        while (true) {
            size_t smallest = index;
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;

            if (left < size && isLess(buffer[left], buffer[smallest])) {
                smallest = left;
            }
            if (right < size && isLess(buffer[right], buffer[smallest])) {
                smallest = right;
            }

            if (smallest != index) {
                std::swap(buffer[index], buffer[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    } // просеивание вниз
};

struct User { // структура пользователя
    int id;
    int attendance;
};

struct IsLessByAttendance { // нужный компаратор для сравнения по посещаемости
    bool operator()(const User& l, const User& r) const {
        return l.attendance < r.attendance;
    }
};

int main() {
    int n, k;
    if (!(std::cin >> n >> k)) {
        return 0;
    }

    if (n <= 0 || k <= 0) {
        return 0;
    }

    if (k > n) k = n;

    User* arr = new User[n];
    bool valid_input = true;
    
    for (int i = 0; i < n; ++i) {
        int id, att;
        if (!(std::cin >> id >> att)) {
            valid_input = false;
            break;
        }
        arr[i] = User{id, att};
    }

    if (!valid_input) {
        delete[] arr;
        return 0;
    }

    IsLessByAttendance cmp;

    // строим кучу из первых k элементов при помощи конструктора
    Heap<User, IsLessByAttendance> heap(arr, static_cast<size_t>(k), cmp);
    
    for (int i = k; i < n; ++i) {
        if (arr[i].attendance > heap.Peek().attendance) {
            heap.Extract();
            heap.Add(arr[i]);
        }
    }
    
    delete[] arr;

    while (!heap.Empty()) {
        User u = heap.Extract();
        std::cout << u.id << " ";
    }
    
    return 0;
}





5.3. Закраска прямой
На числовой прямой окрасили 
N отрезков.
Известны координаты левого и правого концов каждого отрезка.
Найти длину окрашенной части числовой прямой.
Формат ввода
В первой строке записано количество отрезков.
В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.

Формат вывода
Выведите целое число — длину окрашенной части.

#include <iostream>

template<typename T, typename IsLess>
void MergeSort(T* arr, int n, IsLess isLess) {
    if (n <= 1) return;

    int mid = n / 2;

    MergeSort(arr, mid, isLess);
    MergeSort(arr + mid, n - mid, isLess);

    T* left = new T[n];
    if (!left) {
        return;
    }

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    Merge(left, mid, arr + mid, n - mid, isLess);

    for (int i = 0; i < n; i++) {
        arr[i] = left[i];
    }

    delete[] left;
}

template<typename T, typename IsLess>
void Merge(T* arr1, int m, T* arr2, int n, IsLess isLess) {
    if (!arr1 || !arr2 || m < 0 || n < 0) return;

    int p1 = m - 1;
    int p2 = n - 1;
    int p = m + n - 1;

    while (p1 >= 0 && p2 >= 0) {
        if (isLess(arr2[p2], arr1[p1])) {
            arr1[p] = arr1[p1];
            p1--;
        } 
        else {
            arr1[p] = arr2[p2];
            p2--;
        }
        p--;
    }

    while (p2 >= 0) {
        arr1[p] = arr2[p2];
        p2--;
        p--;
    }
}

struct Segment {
    int left_point;
    int right_point;
};

struct IsLessByEnd {
    bool operator()(const Segment& l, const Segment& r) const {
        return l.left_point < r.left_point;
    }
};

int main() {
    int n;
    std::cin >> n;
    
    if (n <= 0) {
        return 0;
    }

    Segment* arr = new Segment[n];
    if (!arr) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        int left_point, right_point;
        std::cin >> left_point >> right_point;
        
        if (left_point > right_point) {
            delete[] arr;
            return 0;
        }
        
        arr[i] = Segment{left_point, right_point};
    }

    MergeSort(arr, n, IsLessByEnd());

    int totalLength = 0;
    int currentLeft = arr[0].left_point;
    int currentRight = arr[0].right_point;

    for (int i = 1; i < n; ++i) {
        if (arr[i].left_point <= currentRight) {
            currentRight = std::max(currentRight, arr[i].right_point);
        }
        else {
            totalLength += currentRight - currentLeft;
            currentLeft = arr[i].left_point;
            currentRight = arr[i].right_point;
        }
    }

    totalLength += currentRight - currentLeft;

    std::cout << totalLength << "\n";

    delete[] arr;

    return 0;
}




6. Порядковая статистика и параметры множества (ВАРИАНТ 6.4)
ВАРИАНТ --> Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
Дано множество целых чисел из [0 ... 10^9] n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10% перцентиль
медиана
90% перцентиль

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

// выбор случайного опорного элемента
template<typename T>
int ChooseRandomPivot(T* a, int n) {
    return std::rand() % n;
}

// компаратор по умолчанию для сравнения элементов
template<typename T>
struct DefaultCompare {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

// разделение массива относительно опорного элемента
// проход двумя итераторами от конца к началу
template<typename T, typename Compare>
int Partition(T* a, int n, Compare comp) {
    if (n <= 1) {
        return 0;
    }
    
    // выбор случайного опорного элемента и перемещение в конец
    int randomIndex = ChooseRandomPivot(a, n);
    std::swap(a[randomIndex], a[n - 1]);
    
    const T& pivot = a[n - 1];
    int i = n - 1; // граница для элементов, больших опорного
    int j = n - 2; // текущий элемент для проверки
    
    // проход от конца к началу
    while (j >= 0) {
        if (comp(pivot, a[j])) { // если текущий элемент больше опорного
            i--;
            std::swap(a[i], a[j]);
        }
        j--;
    }
    
    // перемещение опорного элемента на правильную позицию
    std::swap(a[i], a[n - 1]);
    return i;
}

// инициализация генератора случайных чисел
void InitializeRandom() {
    std::srand(std::time(nullptr));
}

// алгоритм быстрого выбора для нахождения k-ой порядковой статистики
template<typename T, typename Compare = DefaultCompare<T>>
T QuickSelect(T *a, int n, int k, Compare comp = Compare{}) {
    assert(k >= 0);
    assert(k < n);

    int left = 0;
    int right = n - 1;
    
    // итеративный процесс без рекурсии
    while (left <= right) {
        // разделение текущего подмассива
        int pivotPos = Partition(a + left, right - left + 1, comp) + left;
        
        if (pivotPos == k) {
            return a[k]; // найден искомый элемент
        } else if (k < pivotPos) {
            right = pivotPos - 1; // ищем в левой части
        } else {
            left = pivotPos + 1; // ищем в правой части
        }
    }
    return a[k];
}

int main() {
    InitializeRandom();
    
    int n;
    std::cin >> n;
    int* arr = new int[n];
    
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    
    // вычисление перцентилей с помощью быстрого выбора
    int percentile_10 = QuickSelect(arr, n, n / 10);       // 10% перцентиль
    int median = QuickSelect(arr, n, n / 2);               // медиана (50%)
    int percentile_90 = QuickSelect(arr, n, n * 9 / 10);   // 90% перцентиль
    
    std::cout << percentile_10 << std::endl;
    std::cout << median << std::endl;
    std::cout << percentile_90 << std::endl;

    delete[] arr;

    return 0;
}



/*7.3. Binary MSD для long long
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 1000000. Отсортировать массив методом MSD по битам (бинарный QuickSort).
#include <iostream>

void BinaryQuickSort(long long* arr, size_t size, int bit = 63) {
    if (size <= 1 || bit < 0) return;
    
    size_t left = 0;
    for (size_t i = 0; i < size; ++i) {
        if (!((arr[i] >> bit) & 1)) {
            // перемещаем элементы с битом=0 в начало, сохраняя относительный порядок
            if (i != left) std::swap(arr[i], arr[left]);
            left++;  // left теперь указывает на первую позицию для элемента с битом=1
        }
    }
    
    if (left > 0 && left < size) {
        // разделились на две непустые части - сортируем обе по следующему биту
        BinaryQuickSort(arr, left, bit - 1);
        BinaryQuickSort(arr + left, size - left, bit - 1);
    } else {
        // все элементы имеют одинаковый бит на этой позиции - переходим к следующему биту
        BinaryQuickSort(arr, size, bit - 1);
    }
}

int main() {
    size_t n;
    std::cin >> n;

    long long *data = new long long[n];
    
    for (size_t i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    
    BinaryQuickSort(data, n);
    
    for (size_t i = 0; i < n; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
} */




/*
Задача 1. Хеш-таблица (6 баллов)
Обязательная задача
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
1_2. Для разрешения коллизий используйте двойное хеширование.

Требования: В таблице запрещено хранение указателей на описатель элемента.
Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество; 
    -  означает удаление  строки из множества;  
    ?  означает проверку принадлежности данной строки множеству. 
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.




#include <vector>
#include <iostream>
#include <cassert>
#include <string>

const size_t BIG_PRIME = 9223372036854775783ULL;
const size_t InitSize = 32;

template<typename T, typename H>
class HashTable {
public:
    HashTable(H _hasher);
    ~HashTable();

    bool AddKey(const T& key);
    bool DeleteKey(const T& key);
    bool HasKey(const T& key) const;
private:
    enum CellState { empty, filled, deleted };
    struct Cell {
        T key;
        size_t hash;
        CellState state;
    };

    H hasher;
    std::vector<Cell> table;
    size_t keysCount;

    void growTable();
    size_t secondaryHash(size_t primary_hash) const;
};

template<typename T, typename H>
size_t HashTable<T, H>::secondaryHash(size_t primary_hash) const {
    return 1 + (primary_hash % (table.size() - 1));
}

template<typename T, typename H>
HashTable<T, H>::HashTable(H _hasher) :
    hasher(_hasher),
    table(InitSize),
    keysCount(0)
{
    for (size_t i = 0; i < table.size(); ++i) {
        table[i].state = empty;
    }
}

template<typename T, typename H>
HashTable<T, H>::~HashTable() {}

template<typename T, typename H>
bool HashTable<T, H>::AddKey(const T& key)
{
    if (keysCount * 2 >= table.size()) {
        growTable();
    }

    size_t h1 = hasher(key);
    size_t h2 = secondaryHash(h1);
    size_t index = h1 % table.size();
    size_t first_deleted = table.size();

    for (size_t probe = 0; probe < table.size(); ++probe) {
        if (table[index].state == empty) {
            break;
        }
        if (table[index].state == deleted && first_deleted == table.size()) {
            first_deleted = index;
        }
        if (table[index].state == filled && table[index].hash == h1 && table[index].key == key) {
            return false;
        }
        index = (index + h2) % table.size();
    }

    size_t insert_pos = (first_deleted != table.size()) ? first_deleted : index;
    table[insert_pos].key = key;
    table[insert_pos].hash = h1;
    table[insert_pos].state = filled;
    ++keysCount;
    return true;
}

template<typename T, typename H>
bool HashTable<T, H>::DeleteKey(const T& key)
{
    size_t h1 = hasher(key);
    size_t h2 = secondaryHash(h1);
    size_t index = h1 % table.size();

    for (size_t probe = 0; probe < table.size(); ++probe) {
        if (table[index].state == empty) {
            return false;
        }
        if (table[index].state == filled && table[index].hash == h1 && table[index].key == key) {
            table[index].state = deleted;
            --keysCount;
            return true;
        }
        index = (index + h2) % table.size();
    }
    return false;
}

template<typename T, typename H>
bool HashTable<T, H>::HasKey(const T& key) const
{
    size_t h1 = hasher(key);
    size_t h2 = secondaryHash(h1);
    size_t index = h1 % table.size();

    for (size_t probe = 0; probe < table.size(); ++probe) {
        if (table[index].state == empty) {
            return false;
        }
        if (table[index].state == filled && table[index].hash == h1 && table[index].key == key) {
            return true;
        }
        index = (index + h2) % table.size();
    }
    return false;
}

template<typename T, typename H>
void HashTable<T, H>::growTable()
{
    std::vector<Cell> old_table = std::move(table);
    table = std::vector<Cell>(old_table.size() * 2);
    for (size_t i = 0; i < table.size(); ++i) {
        table[i].state = empty;
    }
    keysCount = 0;

    for (size_t i = 0; i < old_table.size(); ++i) {
        if (old_table[i].state == filled) {
            AddKey(old_table[i].key);
        }
    }
}

struct StringHasher {
    StringHasher(size_t _p) : p(_p) {}
    size_t operator()(const std::string& key) const {
        size_t hash = 0;
        for (char c : key) {
            hash = hash * p + static_cast<unsigned char>(c);
        }
        return hash;
    }
private:
    size_t p;
};

int main()
{
	StringHasher hasher(BIG_PRIME);
	HashTable<std::string, StringHasher> table(hasher);
	char op = 0;
	std::string word;
	while (std::cin >> op >> word) {
		switch (op) {
		case '+':
			std::cout << (table.AddKey(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (table.DeleteKey(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			std::cout << (table.HasKey(word) ? "OK" : "FAIL") << std::endl;
			break;
		}
	}

	return 0;
}
*/

/*2_3. Обход дерева в порядке post-order
Дано число N <= 10 ^ 4 и последовательность целых чисел из  [-2 ^ 31, 2 ^ 31]
длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; 
иначе в левое поддерево root. Выведите элементы в порядке post-order (снизу вверх).
Рекурсия запрещена. 

#include <iostream>
#include <stack>

template<typename T, typename C>
class BinaryTree {
public:
    BinaryTree(const C& _cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();

    void Add(const T& key);
    bool Has(const T& key);

    void Traverse(void (*visit)(const T&)) const { traverse(root, visit); };
private:
    struct Node {
        Node* left;
        Node* right;
        T key;
        Node(const T& key) : left(nullptr), right(nullptr), key(key) {}
    };
    Node* root;
    C cmp;

    void traverse(Node* node, void (*visit)(const T&)) const;
};


template<typename T, typename C>
BinaryTree<T, C>::~BinaryTree() 
{
    if (root == nullptr) return;

    std::stack<Node*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node* curr = nodes.top();
        nodes.pop();

        if (curr->left)  nodes.push(curr->left);
        if (curr->right) nodes.push(curr->right);

        delete curr;
    }

    root = nullptr;
}

template<typename T, typename C>
void BinaryTree<T, C>::Add(const T& key)
{
    Node* newNode = new Node(key);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* curr = root;
    while (true) {
        if (cmp(key, curr->key)) {
            if (curr->left == nullptr) {
                curr->left = newNode;
                return;
            }
            curr = curr->left;
        } else if (cmp(curr->key, key)) {
            if (curr->right == nullptr) {
                curr->right = newNode;
                return;
            }
            curr = curr->right;
        } else {
            delete newNode;
            return;
        }
    }
}

template<typename T, typename C>
bool BinaryTree<T, C>::Has(const T& key) 
{
    if (root == nullptr) {
        return false;
    }

    Node* curr = root;
    while (true) {
        if (cmp(key, curr->key)) {
            if (curr->left == nullptr) {
                return false;
            }
            curr = curr->left;
        } else if (cmp(curr->key, key)) {
            if (curr->right == nullptr) {
                return false;
            }
            curr = curr->right;
        } else {
            return true;
        }
    }
}

template<typename T, typename C>
void BinaryTree<T, C>::traverse(Node* node, void (*visit)(const T&)) const
{
    if (node == nullptr) return;

    std::stack<Node*> stack;
    std::stack<bool> visited;

    stack.push(node);
    visited.push(false);

    while (!stack.empty()) {
        Node* curr = stack.top();
        bool isVisited = visited.top();
        visited.pop();
        stack.pop();

        if (isVisited) {
            visit(curr->key);
        } else {
            stack.push(curr);
            visited.push(true);

            if (curr->right) {
                stack.push(curr->right);
                visited.push(false);
            }
            if (curr->left) {
                stack.push(curr->left);
                visited.push(false);
            }
        }
    }
}


struct IntCmp {
    bool operator()(int l, int r) const { return l < r; }
};

int main()
{
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int el;
        std::cin >> el;
        tree.Add(el);
    }

    tree.Traverse([](const int& key) {std::cout << key << " ";});
    std::cout << "\n";
} 


#include <iostream>
#include <vector>
#include <queue>

template<typename T, typename C>
class BTree {
public:
    BTree(size_t _t, const C& _cmp) : root(nullptr), t(_t), cmp(_cmp) {
        if (t < 2) {
            throw std::invalid_argument("t must be >= 2");
        }
    }
    ~BTree() { delete root; }

    void Add(const T& key);
    std::vector<std::vector<T>> getLevels() const;

private:
    struct Node {
        std::vector<T> Keys;
        std::vector<Node*> Children;
        bool IsLeaf;
        Node(bool isLeaf) : IsLeaf(isLeaf) {}
        ~Node() { for (auto* child : Children) { delete child; } }
    };

    Node* root;
    size_t t;
    C cmp;

    bool isNodeFull(Node* node) const { return node->Keys.size() == 2 * t - 1; }
    void splitChild(Node* node, size_t pos);
    void insertNonFull(Node* node, const T& key);
};

template<typename T, typename C>
void BTree<T, C>::Add(const T& key) {
    if (root == nullptr) {
        root = new Node(true);
    }

    if (isNodeFull(root)) {
        Node* newRoot = new Node(false);
        newRoot->Children.push_back(root);
        root = newRoot;
        splitChild(root, 0);
    }

    insertNonFull(root, key);
}

template<typename T, typename C>
void BTree<T, C>::insertNonFull(Node* node, const T& key) {
    if (node->IsLeaf) {
        size_t i = 0;
        while (i < node->Keys.size() && cmp(node->Keys[i], key)) {
            ++i;
        }
        node->Keys.insert(node->Keys.begin() + i, key);
    }
    else {
        size_t i = 0;
        while (i < node->Keys.size() && cmp(node->Keys[i], key)) {
            ++i;
        }

        if (isNodeFull(node->Children[i])) {
            splitChild(node, i);
            if (cmp(node->Keys[i], key)) {
                ++i;
            }
        }

        insertNonFull(node->Children[i], key);
    }
}

template<typename T, typename C>
void BTree<T, C>::splitChild(Node* parent, size_t pos) {
    Node* fullChild = parent->Children[pos];
    Node* newNode = new Node(fullChild->IsLeaf);

    T median = fullChild->Keys[t - 1];

    for (size_t i = 0; i < t - 1; ++i) {
        newNode->Keys.push_back(fullChild->Keys[t + i]);
    }

    if (!fullChild->IsLeaf) {
        for (size_t i = 0; i < t; ++i) {
            newNode->Children.push_back(fullChild->Children[t + i]);
        }
        fullChild->Children.erase(
            fullChild->Children.begin() + t,
            fullChild->Children.end()
        );
    }

    fullChild->Keys.resize(t - 1);

    parent->Children.insert(parent->Children.begin() + pos + 1, newNode);
    parent->Keys.insert(parent->Keys.begin() + pos, median);
}

template<typename T, typename C>
std::vector<std::vector<T>> BTree<T, C>::getLevels() const {
    std::vector<std::vector<T>> result;
    if (!root) return result;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        size_t levelSize = q.size();
        std::vector<T> currentLevel;

        for (size_t i = 0; i < levelSize; ++i) {
            Node* node = q.front();
            q.pop();

            for (const T& k : node->Keys) {
                currentLevel.push_back(k);
            }

            for (Node* child : node->Children) {
                if (child) q.push(child);
            }
        }

        result.push_back(currentLevel);
    }

    return result;
}

struct UIntCmp {
    bool operator()(unsigned int l, unsigned int r) const {
        return l < r;
    }
};

int main() {
    size_t t;
    std::cin >> t;

    UIntCmp cmp;
    BTree<unsigned int, UIntCmp> tree(t, cmp);

    unsigned int key;
    while (std::cin >> key) {
        tree.Add(key);
    }

    auto levels = tree.getLevels();
    for (const auto& level : levels) {
        for (size_t i = 0; i < level.size(); ++i) {
            if (i > 0) std::cout << " ";
            std::cout << level[i];
        }
        std::cout << "\n";
    }

    return 0;
} */

#include <iostream>
#include <vector>

class AVL {
private:
    struct Node {
        int key;
        int height;
        int size;
        Node *left, *right;
        Node(int k) : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int height(Node* n) { return n ? n->height : 0; }
    int size(Node* n) { return n ? n->size : 0; }

    void update(Node* n) {
        if (n) {
            n->height = 1 + std::max(height(n->left), height(n->right));
            n->size = 1 + size(n->left) + size(n->right);
        }
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* B = x->right;
        x->right = y;
        y->left = B;
        update(y);
        update(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* B = y->left;
        y->left = x;
        x->right = B;
        update(x);
        update(y);
        return y;
    }

    int balance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key > node->key) node->left = insert(node->left, key);
        else node->right = insert(node->right, key);
        update(node);
        int bal = balance(node);
        if (bal > 1) {
            if (key > node->left->key) return rotateRight(node);
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bal < -1) {
            if (key <= node->right->key) return rotateLeft(node);
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* kth(Node* node, int k) {
        if (!node) return nullptr;
        int left = size(node->left);
        if (k == left) return node;
        if (k < left) return kth(node->left, k);
        return kth(node->right, k - left - 1);
    }

    Node* deleteKey(Node* node, int key) {
        if (!node) return node;
        if (key > node->key) node->left = deleteKey(node->left, key);
        else if (key < node->key) node->right = deleteKey(node->right, key);
        else {
            if (!node->left) {
                Node* r = node->right;
                delete node;
                return r;
            }
            if (!node->right) {
                Node* l = node->left;
                delete node;
                return l;
            }
            Node* suc = kth(node->right, 0);
            node->key = suc->key;
            node->right = deleteKey(node->right, suc->key);
        }
        update(node);
        int bal = balance(node);
        if (bal > 1) {
            if (balance(node->left) >= 0) return rotateRight(node);
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bal < -1) {
            if (balance(node->right) <= 0) return rotateLeft(node);
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    int rank(Node* node, int key) {
        if (!node) return 0;
        if (key > node->key) return rank(node->left, key);
        if (key < node->key) return 1 + size(node->left) + rank(node->right, key);
        return size(node->left);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVL() : root(nullptr) {}
    ~AVL() { destroy(root); }

    int add(int key) {
        root = insert(root, key);
        return rank(root, key);
    }

    void remove(int index) {
        Node* n = kth(root, index);
        if (n) root = deleteKey(root, n->key);
    }
};

int main() {
    int n;
    std::cin >> n;

    AVL tree;
    std::vector<int> res;

    for (int i = 0; i < n; ++i) {
        int op, x;
        std::cin >> op >> x;
        if (op == 1) {
            int pos = tree.add(x);
            res.push_back(pos);
        } else {
            tree.remove(x);
        }
    }

    for (int pos : res) {
        std::cout << pos << '\n';
    }

    return 0;
}