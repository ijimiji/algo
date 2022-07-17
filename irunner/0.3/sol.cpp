#include <fstream>
#include <vector>

struct Node {
    int64_t key;
    int64_t left;
    int64_t right;
    Node(int64_t key) : key(key) {
        left = INT64_MIN;
        right = INT64_MAX;
    }
};

int main() {
    std::ifstream input("bst.in");
    std::ofstream output("bst.out");
    int32_t n, parentIndex; int64_t key;
    char direction;
    input >> n;
    std::vector<Node *> nodes(n + 1);
    nodes[0] = nullptr;
    input >> key;
    nodes[1] = new Node(key);
    bool isSearch = true;

    for (size_t i = 2; i <= n; i++) {
        input >> key;
        input >> parentIndex;
        input >> direction;
        nodes[i] = new Node(key);

        nodes[i]->left = nodes[parentIndex]->left;
        nodes[i]->right = nodes[parentIndex]->right;

        if (direction == 'R') {
            nodes[i]->left = nodes[parentIndex]->key;
        } else {
            nodes[i]->right = nodes[parentIndex]->key;
        }

        if (key < nodes[i]->left || key >= nodes[i]->right) {
            isSearch = false;
            break;
        }
    }

    output << (isSearch ? "YES" : "NO");
    return 0;
}