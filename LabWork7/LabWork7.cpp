#include <iostream>
#include <random>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <string>

#if _WIN32
#define NOMINMAX
#include <windows.h>
#endif // _WIN32
#include <functional>

// генерація випадкового числа
int randInt(int start, int end) {
    static std::random_device rand_dev; 
    static std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(start, end); 
    return distr(generator);
}

// Зчитування введення з перевіркою
template <typename T>
T readInput(const char* prompt) {
    while (true) {
        try {
            T value;

            std::cout << prompt;
            std::cin >> value;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Введено некоректне значення!");
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            return value;
        }
        catch (std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }
}

// Заповнення масиву випадковими числами
void randIntArr(int* arr, int size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = randInt(0, 200); // значення 0 - 200
    }
}

// Створення 2-мірного масиву
int** genInt2dArr(int rows, int columns) {

    int** arr = new int* [rows]; // масив вказівників

    for (size_t i = 0; i < rows; i++) {
        arr[i] = new int[columns]; // створення рядка
        randIntArr(arr[i], columns);
    }

    return arr;
}

// Виведення 2-мірного масиву
void printArr(int** arr, int rows, int columns) {

    for (size_t j = 0; j < columns; j++) {
        for (size_t i = 0; i < rows; i++) {

            std::cout << std::left
                << std::setw(5) << arr[i][j]; 
        }

        std::cout << "\n";
    }
}

// Сума елементів масиву
long long arr2dSum(int** arr, int rows, int columns) {

    long long sum = 0;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {

            sum += arr[i][j];
        }
    }

    return sum;
}

// Видалення 2-мірного масиву
void delInt2dArr(int** arr, int rows) {

    for (int i = 0; i < rows; i++)
        delete[] arr[i]; 

    delete[] arr;
}

// Стек
class Stack {

public:

    // конструктор
    Stack(int size = 10) {
        capacity = size;

        data = new int[capacity]; // основний стек
        minStack = new int[capacity]; // стек мінімумів

        topIndex = -1;
        minIndex = -1;
    }

    // деструктор
    ~Stack() {
        delete[] data;
        delete[] minStack;
    }

    // додавання елемента
    void push(int value) {

        if (topIndex + 1 == capacity)
            resize(); // збільшення стеку

        data[++topIndex] = value;

        // оновлення мінімуму
        if (minIndex == -1 || value <= minStack[minIndex]) {
            minStack[++minIndex] = value;
        }
    }

    // видалення верхнього елемента
    void pop() {

        if (isEmpty())
            throw std::underflow_error("Стек порожній");

        if (data[topIndex] == minStack[minIndex])
            minIndex--;

        topIndex--;
    }

    // отримання верхнього елемента
    int top() const {

        if (isEmpty())
            throw std::underflow_error("Стек порожній");

        return data[topIndex];
    }

    // отримання мінімального елемента
    int getMin() const {

        if (isEmpty())
            throw std::underflow_error("Стек порожній");

        return minStack[minIndex];
    }

    // перевірка на порожність
    bool isEmpty() const {
        return topIndex == -1;
    }

    // розмір стеку
    int size() const {
        return topIndex + 1;
    }

private:

    int* data; // основний масив
    int* minStack; // масив мінімумів

    int capacity;
    int topIndex;
    int minIndex;

    // збільшення розміру стеку
    void resize() {

        int newCapacity = capacity * 2;

        int* newData = new int[newCapacity];
        int* newMin = new int[newCapacity];

        // копіювання даних
        for (int i = 0; i <= topIndex; i++)
            newData[i] = data[i];

        for (int i = 0; i <= minIndex; i++)
            newMin[i] = minStack[i];

        delete[] data;
        delete[] minStack;

        data = newData;
        minStack = newMin;

        capacity = newCapacity;
    }
};

// тестування стеку
void testStack(Stack& s, int iterations) {

    std::cout << std::left
        << std::setw(15) << "Операція"
        << std::setw(10) << "Значення"
        << std::setw(10) << "Top"
        << std::setw(10) << "Min"
        << "\n";

    // додавання елементів
    for (int i = 0; i < iterations; i++) {

        int value = randInt(-100, 100);
        \\
        s.push(value);

        std::cout << std::setw(15) << "push"
            << std::setw(10) << value
            << std::setw(10) << s.top()
            << std::setw(10) << s.getMin()
            << "\n";
    }

    std::cout << "\n";

    // видалення елементів
    while (!s.isEmpty()) {

        int top = s.top();
        int min = s.getMin();

        s.pop();

        std::cout << std::setw(15) << "pop"
            << std::setw(10) << top
            << std::setw(10) << (s.isEmpty() ? "-" : std::to_string(s.top()))
            << std::setw(10) << (s.isEmpty() ? "-" "\n\nСтек порожній." : std::to_string(s.getMin()))
            << "\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    try {
        // Завдання 5
        int rows = readInput<unsigned int>("Введіть кількість рядків: ");
        int columns = readInput<unsigned int>("Введіть кількість стовпців: ");

        int** intArr2d = genInt2dArr(rows, columns);

        printArr(intArr2d, rows, columns);

        std::cout << "Сума всіх елементів масиву: "
            << arr2dSum(intArr2d, rows, columns) << "\n\n";

        delInt2dArr(intArr2d, rows);

        // Завдання 12
        Stack s(10);
        testStack(s, 10);

        columns = readInput<unsigned int>("Введіть кількість рядків: ");

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }

    return 0;
}