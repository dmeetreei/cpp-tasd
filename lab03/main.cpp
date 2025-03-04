#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>


using namespace std;

int distanceLevensteinIterace(string s1, string s2, int lengthS1, int lengthS2) {
    cout << "Нерекурсивный метод нахождения расстояния Левенштейна:" << endl;

    vector<vector<int>> distance(lengthS1 + 1, vector<int>(lengthS2 + 1, 0));

    //Первая строка и первый столбец
    for (int i = 0; i < lengthS1; i++) {
        distance[i][0] = i;
    }
    for (int i = 0; i < lengthS2; i++) {
        distance[0][i] = i;
    }

    //Остальные элементы матрицы
    int insertion, deletion, substitution;

    for (int i = 1; i <= lengthS1; i++) {
        for (int j = 1; j <= lengthS2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            insertion = distance[i][j - 1] + 1;    // (I) Вставка
            deletion = distance[i - 1][j] + 1;     // (D) Удаление
            substitution = distance[i - 1][j - 1] + cost; // (R) Замена
            distance[i][j] = min({insertion, deletion, substitution});
        }
    }


    //вывод матрицы
    for (int i = 0; i < lengthS1 + 1; i++) {
        for (int j = 0; j < lengthS2 + 1; j++) {
            cout << distance[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "Расстояние Левенштейна D = " << distance[lengthS1][lengthS2] << endl;
    return distance[lengthS1][lengthS2];
}

int disLevRec(string s1, string s2, int lengthS1, int lengthS2) {

    if (lengthS1 == 0) return lengthS2;
    if (lengthS2 == 0) return lengthS1;

    if (lengthS1 > lengthS2) {
        return disLevRec(s2, s1, lengthS2, lengthS1);
    }
    int cost;
    if (s1[lengthS1 - 1] != s2[lengthS2 - 1]) {
        cost = 1;
    } else {
        cost = 0;
    }
    return min(min(
                       disLevRec(s1, s2, lengthS1 - 1, lengthS2) + 1,
                       disLevRec(s1, s2, lengthS1, lengthS2 - 1) + 1),
               disLevRec(s1, s2, lengthS1 - 1, lengthS2 - 1) + cost);
}

int disLevRecMem(string s1, string s2, int lengthS1, int lengthS2, vector<vector<int>> cache) {
    if (lengthS1 == 0) return lengthS2;
    if (lengthS2 == 0) return lengthS1;

    if (cache[lengthS1][lengthS2] != -1) {
        return cache[lengthS1][lengthS2];
    }

    int cost;
    if (s1[lengthS1 - 1] != s2[lengthS2 - 1]) {
        cost = 1;
    } else {
        cost = 0;
    }

    int result = min(min(
                             disLevRecMem(s1, s2, lengthS1 - 1, lengthS2) + 1,
                             disLevRecMem(s1, s2, lengthS1, lengthS2 - 1) + 1),
                     disLevRecMem(s1, s2, lengthS1 - 1, lengthS2 - 1) + cost);

    cache[lengthS1][lengthS2] = result;
    return result;
}

int distanceLevensteinRecursive(string s1, string s2, int lengthS1, int lengthS2) {
    cout << "Рекурсивный метод нахождения расстояния Левенштейна:" << endl;
    int a = disLevRec(s1, s2, lengthS1, lengthS2);

    cout << "Расстояние Левенштейна D = " << a << endl;
}

void distanceLevensteinRecursiveMemorization(string s1, string s2, int lengthS1, int lengthS2) {
    cout << "Рекурсивный метод нахождения расстояния Левенштейна с кэшированием:" << endl;
    vector<vector<int>> cache(lengthS1 + 1, vector<int>(lengthS2 + 1, -1));
    int a = disLevRecMem(s1, s2, lengthS1, lengthS2, cache);

    cout << "Расстояние Левенштейна D = " << a << endl;
}

int distanceDamerauLevenstein(string s1, string s2, int lengthS1, int lengthS2) {
    cout << "Метод нахождения расстояния Дамерау - Левенштейна:" << endl;

    vector<vector<int>> distance(lengthS1 + 1, vector<int>(lengthS2 + 1, 0));

    //Первая строка и первый столбец
    for (int i = 0; i < lengthS1; i++) {
        distance[i][0] = i;
    }
    for (int i = 0; i < lengthS2; i++) {
        distance[0][i] = i;
    }

    //Остальные элементы матрицы
    int insertion, deletion, substitution, transposition;

    for (int i = 1; i <= lengthS1; i++) {
        for (int j = 1; j <= lengthS2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            insertion = distance[i][j - 1] + 1;    // Вставка
            deletion = distance[i - 1][j] + 1;     // Удаление
            substitution = distance[i - 1][j - 1] + cost; // Замена
            distance[i][j] = min({insertion, deletion, substitution});
            if (i > 1 && j > 1 && (s1[i - 1] == s2[j - 2]) && (s1[i - 2] == s2[j - 1])) {
                transposition = distance[i - 2][j - 2] + 1;
                distance[i][j] = min(distance[i][j], transposition);
            }
        }
    }

//вывод матрицы
    for (
            int i = 0;
            i < lengthS1 + 1; i++) {
        for (
                int j = 0;
                j < lengthS2 + 1; j++) {
            cout << distance[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "Расстояние Дамерау - Левенштейна D = " << distance[lengthS1][lengthS2] <<
         endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    string s1, s2;
    int lengthS1, lengthS2;
    cout << "Введите строку s1" << endl;
    cin >> s1;
    lengthS1 = s1.length();
    cout << "Введите строку s2" << endl;
    cin >> s2;
    lengthS2 = s2.length();


    distanceLevensteinIterace(s1, s2, lengthS1, lengthS2);
    distanceDamerauLevenstein(s1, s2, lengthS1, lengthS2);
    distanceLevensteinRecursive(s1, s2, lengthS1, lengthS2);
    distanceLevensteinRecursiveMemorization(s1, s2, lengthS1, lengthS2);

}
