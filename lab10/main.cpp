#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Node {
public:
    string name;
    vector<Node*> children;

    Node(string n) : name(n) {}
};

void addChild(Node* parent, Node* child) {
    parent->children.push_back(child);
}

Node* createOrGraph() {
    Node* nodeA = new Node("A");
    Node* nodeB = new Node("B");
    Node* nodeC = new Node("C");
    Node* nodeD = new Node("D");
    Node* nodeE = new Node("E");
    Node* nodeF = new Node("F");
    Node* nodeG = new Node("G");
    Node* nodeH = new Node("H");

    addChild(nodeA, nodeB);
    addChild(nodeA, nodeC);
    addChild(nodeB, nodeD);
    addChild(nodeC, nodeE);
    addChild(nodeF, nodeG);
    addChild(nodeG, nodeH);

    return nodeA;
}

// Поиск в глубину (DFS) - обход с конца
void dfs(Node* node, unordered_set<string>& visitedNodes) {
    if (visitedNodes.find(node->name) != visitedNodes.end()) {
        return;
    }

    visitedNodes.insert(node->name);
    cout << "Посещен узел " << node->name << endl;

    // Обход потомков в обратном порядке
    for (int i = node->children.size() - 1; i >= 0; --i) {
        if (visitedNodes.find(node->children[i]->name) == visitedNodes.end()) {
            dfs(node->children[i], visitedNodes);
        }
    }
}

// Поиск в ширину (BFS)
void bfs(Node* node) {
    unordered_set<string> visitedNodes;
    queue<Node*> q;

    q.push(node);
    visitedNodes.insert(node->name);

    while (!q.empty()) {
        Node* currentNode = q.front();
        q.pop();
        cout << "В очереди: " << currentNode->name << endl;

        for (Node* child : currentNode->children) {
            if (visitedNodes.find(child->name) == visitedNodes.end()) {
                q.push(child);
                cout << "В очередь добавлена: " << child->name << endl;
                visitedNodes.insert(child->name);
            }
        }
    }
    cout << "Итоговое посещение узлов: ";
    for (const auto& nodeName : visitedNodes) {
        cout << nodeName << " ";
    }
    cout << endl;
}

// Показать граф
void showGraph(Node* node, unordered_set<string>& visitedNodes) {
    if (visitedNodes.find(node->name) != visitedNodes.end()) {
        return;
    }

    visitedNodes.insert(node->name);

    cout << node->name << " -> [";
    for (size_t i = 0; i < node->children.size(); ++i) {
        cout << node->children[i]->name;
        if (i != node->children.size() - 1) cout << " , ";
    }
    cout << "]" << endl;

    for (Node* child : node->children) {
        showGraph(child, visitedNodes);
    }
}

int main() {
    Node* graphHead = createOrGraph();

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Показать граф (список потомков)\n";
        cout << "2. Поиск в ширину (BFS)\n";
        cout << "3. Поиск в глубину (DFS)\n";
        cout << "0. Выход\n";
        cout << "Введите номер команды: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {  // Показать граф
                cout << "Граф (узел -> потомки):\n";
                unordered_set<string> visitedNodes;
                showGraph(graphHead, visitedNodes);
                break;
            }

            case 2: {  // Поиск в ширину
                cout << "Результат поиска в ширину (BFS):\n";
                bfs(graphHead);
                break;
            }

            case 3: {  // Поиск в глубину
                cout << "Результат поиска в глубину (DFS):\n";
                unordered_set<string> visitedNodes;
                dfs(graphHead, visitedNodes);
                cout << "Порядок посещения узлов: ";
                for (const auto& nodeName : visitedNodes) {
                    cout << nodeName << " ";
                }
                cout << endl;
                break;
            }

            case 0: {  // Выход
                cout << "Выход.\n";
                return 0;
            }

            default:
                cout << "Неверная команда. Попробуйте снова.\n";
        }
    }
}
