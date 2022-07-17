#include <cstdint>
#include <fstream>
#include <functional>
#include <inttypes.h>

using namespace std;

template <typename T> class Tree {
  public:
    class Node {
      public:
        T value;
        Node *left;
        Node *right;
        Node(T value) : value(value) {
            left = nullptr;
            right = nullptr;
        }
    };
    Node *root = nullptr;
    Node *add(T value, Node *root) {
        if (!this->root) {
            this->root = new Node(value);
            return root;
        }
        if (!root) {
            return new Node(value);
        }
        if (root->value == value){
            return root;
        }
        if (root->value > value) {
            root->right = add(value, root->right);
        } else {
            root->left = add(value, root->left);
        }
        return root;
    }
    void postOrderTraversal(Node *node, function<void(Node *)> f) {
        if (node == nullptr) {
            return;
        }
        postOrderTraversal(node->right, f);
        postOrderTraversal(node->left, f);
        f(node);
    }
    void preOrderTraversal(Node *node, function<void(Node *)> f) {
        if (node == nullptr) {
            return;
        }
        f(node);
        postOrderTraversal(node->left, f);
        postOrderTraversal(node->right, f);
    }
    int64_t sumOfKeys(Node *subRoot) {
        if (subRoot == nullptr) {
            return 0;
        }
        return (subRoot->value + sumOfKeys(subRoot->left) +
                sumOfKeys(subRoot->right));
    }
    ~Tree() {
        postOrderTraversal(root, [](Node *node) { delete node; });
    }
};

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    Tree<int32_t> tree;
    int32_t temp;
    while (input >> temp) {
        tree.add(temp, tree.root);
    }
    output << tree.sumOfKeys(tree.root);
    return 0;
}