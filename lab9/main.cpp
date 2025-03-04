#include <iostream>
#include <algorithm>

using namespace std;

// Структура узла дерева
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Функция для получения высоты узла
int getHeight(Node* n) {
    return n ? n->height : 0;
}

// Функция для получения баланса узла
int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// Функция для обновления высоты узла
void updateHeight(Node* n) {
    if (n) n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}

// Малое правое вращение
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Малое левое вращение
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Балансировка узла
Node* balance(Node* node) {
    updateHeight(node);
    int balance = getBalance(node);

    // Левый перекос
    if (balance > 1) {
        if (getBalance(node->left) < 0)
            node->left = rotateLeft(node->left);  // Большое правое вращение
        return rotateRight(node);
    }
    
    // Правый перекос
    if (balance < -1) {
        if (getBalance(node->right) > 0)
            node->right = rotateRight(node->right); // Большое левое вращение
        return rotateLeft(node);
    }

    return node;
}

// Вставка узла в АВЛ-дерево
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Дубликаты не допускаются

    return balance(node);
}

// Поиск узла с минимальным значением (для удаления)
Node* findMin(Node* node) {
    return node->left ? findMin(node->left) : node;
}

// Удаление узла
Node* remove(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        if (!node->left) {
            Node* rightChild = node->right;
            delete node;
            return rightChild;
        } else if (!node->right) {
            Node* leftChild = node->left;
            delete node;
            return leftChild;
        } else {
            Node* minLargerNode = findMin(node->right);
            node->key = minLargerNode->key;
            node->right = remove(node->right, minLargerNode->key);
        }
    }

    return balance(node);
}

// Функция для вывода дерева (прямой обход)
void printTree(Node* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    cout << root->key << " (h=" << root->height << ")" << endl;

    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

// Главное меню
void menu() {
    Node* root = nullptr;
    int choice, value;

    do {
        cout << "\nМеню:\n";
        cout << "1. Ввести последовательность чисел\n";
        cout << "2. Вывести дерево\n";
        cout << "3. Добавить узел\n";
        cout << "4. Удалить узел\n";
        cout << "5. Проверить балансировку\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите числа через пробел (окончание - Enter): ";
                while (cin >> value) {
                    root = insert(root, value);
                    if (cin.peek() == '\n') break;
                }
                break;
            case 2:
                cout << "Текущее дерево:\n";
                printTree(root);
                break;
            case 3:
                cout << "Введите число для добавления: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 4:
                cout << "Введите число для удаления: ";
                cin >> value;
                root = remove(root, value);
                break;
            case 5:
                cout << "Баланс дерева: " << getBalance(root) << endl;
                break;
            case 0:
                cout << "Выход...\n";
                break;
            default:
                cout << "Некорректный ввод! Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
