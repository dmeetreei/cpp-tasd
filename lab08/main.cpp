#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// Функция для генерации массива случайных чисел
vector<int> generateRandomArray(int size, int minVal, int maxVal) {
    vector<int> arr;
    srand(time(0));

    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % (maxVal - minVal + 1) + minVal);
    }

    return arr;
}

// Бинарный поиск
bool binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return true;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return false;
}

int main() {
    // Генерация случайного массива
    vector<int> arr = generateRandomArray(100, 1, 100);
    
    // Сортировка массива для бинарного поиска
    sort(arr.begin(), arr.end());

    // Вывод массива (можно закомментировать)
    cout << "Сортированный массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Запрос числа у пользователя
    int target;
    cout << "Введите число для поиска: ";
    cin >> target;

    // Выполнение бинарного поиска
    if (binarySearch(arr, target)) {
        cout << "Число найдено!" << endl;
    } else {
        cout << "Число не найдено." << endl;
    }

    return 0;
}
