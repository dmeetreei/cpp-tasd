#include <iostream>
#include <string>
#include <cmath>

class Int5 {
private:
    int low;  // младшие 3 бита
    int high; // старшие 2 бита

public:
    // Конструктор, принимающий целое число
    Int5(int value) {
        high = value >> 3;      // старшие 2 бита
        low = value & 0x7;      // младшие 3 бита (0x7 = 0111 в двоичной системе)
    }

    // Преобразование в 9-ричную систему
    std::string toBase9() const {
        int decimalValue = (high << 3) | low;
        std::string result;
        while (decimalValue > 0) {
            result = std::to_string(decimalValue % 9) + result;
            decimalValue /= 9;
        }
        return result.empty() ? "0" : result;
    }

    // Оператор "+"
    Int5 operator+(const Int5& other) const {
        int result = ((high << 3) | low) + ((other.high << 3) | other.low);
        return Int5(result & 0x1F); // ограничиваем результат 5 битами
    }

    // Оператор "-"
    Int5 operator-(const Int5& other) const {
        int result = ((high << 3) | low) - ((other.high << 3) | other.low);
        return Int5(result & 0x1F); // ограничиваем результат 5 битами
    }

    // Оператор "*"
    Int5 operator*(const Int5& other) const {
        int result = ((high << 3) | low) * ((other.high << 3) | other.low);
        return Int5(result & 0x1F); // ограничиваем результат 5 битами
    }

    // Оператор сравнения ">"
    bool operator>(const Int5& other) const {
        int thisValue = (high << 3) | low;
        int otherValue = (other.high << 3) | other.low;
        return thisValue > otherValue;
    }

    // Оператор сравнения "<"
    bool operator<(const Int5& other) const {
        return !(*this > other) && !(*this == other);
    }

    // Оператор сравнения ">="
    bool operator>=(const Int5& other) const {
        return *this > other || *this == other;
    }

    // Оператор сравнения "<="
    bool operator<=(const Int5& other) const {
        return *this < other || *this == other;
    }

    // Оператор сравнения "=="
    bool operator==(const Int5& other) const {
        int thisValue = (high << 3) | low;
        int otherValue = (other.high << 3) | other.low;
        return thisValue == otherValue;
    }

    // Оператор сравнения "!="
    bool operator!=(const Int5& other) const {
        return !(*this == other);
    }

    // Присваивание
    void assign(const Int5& value) {
        high = value.high;
        low = value.low;
    }

    // Печать в 9-ричной системе
    void print() const {
        std::cout << toBase9() << std::endl;
    }

    // Статическая функция для преобразования строки в Int5
    static Int5 fromBase9String(const std::string& base9Value) {
        int intValue = 0;
        for (char ch : base9Value) {
            intValue = intValue * 9 + (ch - '0');
        }
        return Int5(intValue);
    }
};

int main() {
    std::string base9Value1, base9Value2;

    // Ввод первого числа
    std::cout << "Введите значение первого числа в 9-ричной системе (макс. 4): ";
    std::cin >> base9Value1;
    Int5 val1 = Int5::fromBase9String(base9Value1);

    // Ввод второго числа
    std::cout << "Введите значение второго числа в 9-ричной системе (макс. 4): ";
    std::cin >> base9Value2;
    Int5 val2 = Int5::fromBase9String(base9Value2);

    // Операции
    std::cout << "[СЛОЖЕНИЕ]: ";
    val1.print();
    val1 = val1 + val2;
    val1.print();

    std::cout << "[ВЫЧИТАНИЕ]: ";
    val1.print();
    val1 = val1 - val2;
    val1.print();

    std::cout << "[УМНОЖЕНИЕ]: ";
    val1.print();
    val1 = val1 * val2;
    val1.print();

    std::cout << "[СРАВНЕНИЕ >]: " << (val1 > val2 ? "true" : "false") << std::endl;
    std::cout << "[СРАВНЕНИЕ <]: " << (val1 < val2 ? "true" : "false") << std::endl;
    std::cout << "[СРАВНЕНИЕ >=]: " << (val1 >= val2 ? "true" : "false") << std::endl;
    std::cout << "[СРАВНЕНИЕ <=]: " << (val1 <= val2 ? "true" : "false") << std::endl;
    std::cout << "[СРАВНЕНИЕ ==]: " << (val1 == val2 ? "true" : "false") << std::endl;
    std::cout << "[СРАВНЕНИЕ !=]: " << (val1 != val2 ? "true" : "false") << std::endl;

    // Присваивание
    val1.assign(val2);
    std::cout << "[ПРИСВАИВАНИЕ]: ";
    val1.print();
    val2.print();

    return 0;
}
