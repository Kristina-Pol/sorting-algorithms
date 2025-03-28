#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <string>
#include <locale>
#include <ratio>

using namespace std;
//Первая сортировка: сортировка бинарными вставками
void binaryInsertionSort(int* arr, int n) {
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > key)
                right = mid - 1;
            else
                left = mid + 1;
        }
        for (int j = i - 1; j >= left; j--)
            arr[j + 1] = arr[j];
        arr[left] = key;
    }
}
//Вторая сортировка: сортировка qsort
bool compare(int a, int b) {
    return a < b;
}

void qsort(int* arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (compare(arr[i], pivot)) {
            i++;
        }
        while (compare(pivot, arr[j])) {
            j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) {
        qsort(arr, left, j);
    }
    if (i < right) {
        qsort(arr, i, right);
    }
}
//Третья сортировка: пирамидальная сортировка
void pyramid(int* arr, int n, int i) {
    int k = i;  // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1;  // Левый потомок узла i
    int r = 2 * i + 2;  // Правый потомок узла i

    // Если левый потомок больше корня
    if (l < n && arr[l] > arr[k]) {
        k = l;
    }

    // Если правый потомок больше корня
    if (r < n && arr[r] > arr[k]) {
        k = r;
    }

    // Если наибольший элемент не является корневым
    if (k != i) {
        swap(arr[i], arr[k]);

        // Рекурсивно применяем процедуру heapify к поддереву
        pyramid(arr, n, k);
    }
}

void pyrSort(int* arr, int n) {
    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--) {
        pyramid(arr, n, i);
    }

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // Вызываем процедуру heapify на уменьшенной куче
        pyramid(arr, i, 0);
    }
}
//Функция вывода массива
void printArray(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

}
void writeArrayToFile(int* arr, int n, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (int i = 0; i < n; i++) {
            file << arr[i] << " ";
        }
        file.close();
        cout << "Data successfully written to the file." << endl;
    }
    else {
        cout << "Unable to open the file." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    string namefile;
    int n; // кол-во элем ентов в массиве
    cout << "Введите название файла ";
    cin >> namefile;
    cout << "Введите размер массива";
    cin >> n;
    int* arr = new int [n]; //вектор
    int m; // выбор сортировка
    ifstream filen;
    filen.open(namefile);
    if (filen.is_open()) {
        cout << "Файл открыт" << endl;
    }
    else {
        cout << "Файл не открыт" << endl;
        return -1;
    }

    for (int i = 0; i < n; i++) {
        filen >> arr[i];
    }
    filen.close();
    cout << "Исходный массив: " << endl;
    printArray(arr, n);
    cout << "Выберите сортировку: бинарная сортировка - 1" << endl;
    cout << "qsort сортировка - 2" << endl;
    cout << "пирамидальная сортировка - 3" << endl;
    cin >> m;
    auto start = chrono::high_resolution_clock::now();

    if (m == 1) {
        binaryInsertionSort(arr, n);
    }
    if (m == 2) {
        qsort(arr, 0, n - 1);
    }
    if (m == 3) {
        pyrSort(arr, n);
    }
    

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    cout << "Отсортированный массив: ";
    printArray(arr, n);
    if (n == 16) {
        writeArrayToFile(arr,n,"d16-s.txt");
    }
    if (n == 100) {
        writeArrayToFile(arr, n, "d100-s.txt");
       
    }
    if (n == 500) {
        writeArrayToFile(arr, n, "d500-s.txt");
        
    }
    if (n == 1000) {
        writeArrayToFile(arr, n, "d1000-s.txt");
       
    }
    if (n == 5000) {
        writeArrayToFile(arr, n, "d5000-s.txt");
        
    }
    
    
    delete[] arr;

    cout << "Время выполнения: " << duration.count() << " микросекунд" << endl;
}