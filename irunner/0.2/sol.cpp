#include <cstdint>
#include <fstream>
#include <functional>
#include <inttypes.h>
#include <iostream>

using namespace std;

template <typename T> class Tree {
  public:
    class Node {
      public:
        T key;
        Node *left;
        Node *right;
        Node(T key) : key(key) {
            left = nullptr;
            right = nullptr;
        }
    };

    Tree() { this->root = nullptr; }
    void insert(T key) {
        Node **cur = &(this->root);
        while (*cur) {
            Node *node = *cur;
            if (key < node->key) {
                cur = &node->left;
            } else if (key > node->key) {
                cur = &node->right;
            } else {
                return;
            }
        }
        *cur = new Node(key);
    }

    void preOrderLeftTraversal(Node *node, function<void(Node *node)> f) {
        if (node) {
            f(node);
            preOrderLeftTraversal(node->left, f);
            preOrderLeftTraversal(node->right, f);
        }
    }

    Node *root;
    Node *find_min_node(Node *node) {
        if (node->left == nullptr) {
            return node;
        }
        return find_min_node(node->left);
    }
    void remove(T key) { this->root = remove_recursively(this->root, key); }
    Node *remove_recursively(Node *node, T key) {
        if (!node) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = remove_recursively(node->left, key);
            return node;
        } else if (key > node->key) {
            node->right = remove_recursively(node->right, key);
            return node;
        }

        if (!node->left) {
            return node->right;
        } else if (!node->right) {
            return node->left;
        } else {
            auto min_key = find_min_node(node->right)->key;
            node->key = min_key;
            node->right = remove_recursively(node->right, min_key);
            return node;
        }
    }
};

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt", output.app | output.out);
    Tree<int32_t> tree;
    int32_t temp;
    int32_t keyToDelete;
    input >> keyToDelete;
    while (input >> temp) {
        tree.insert(temp);
    }
    tree.remove(keyToDelete);

    bool first = true;
    tree.preOrderLeftTraversal(tree.root,
                               [&output, &first](Tree<int32_t>::Node *node) {
                                   if (!first) {
                                       output << "\n";
                                   } else {
                                       first = false;
                                   }
                                   output << node->key;
                               });
    return 0;
}