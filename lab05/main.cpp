#include <Windows.h>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

void infixToPostfix(string toPF) {
    string result;
    stack<char> underbrackets;
    int size = toPF.size();
    string allowedChars = "abcdxyz0123456789";
    for (int i = 0; i < size; i++) {
        char c = toPF[i];
        if (allowedChars.find(c) != string::npos) {
            //cout << i << ": " << c << " a-d,x-z,0-9" << endl;
            result += c;
        } else if (c == '(') {
            //cout << i << ": " << c <<" скобка"<<endl;
            do {
                underbrackets.push(c);
                i++;
            } while (c == ')')
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    string expression;
    cout << "Введите выражение в постфиксной записи" << endl;
    cin >> expression;
    infixToPostfix(expression);
    return 0;
}
