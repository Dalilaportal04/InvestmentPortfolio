#include "BTree.h"
#include <iostream>

BTreeNode::BTreeNode(bool leaf) : isLeaf(leaf) {}

BTree::BTree(int order) : order(order), root(new BTreeNode(true)) {}

void BTree::insertNonFull(BTreeNode* node, const std::string& ticker, double price) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
        while (i >= 0 && ticker < node->keys[i]) {
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, ticker);
        node->values.insert(node->values.begin() + i + 1, price);
    } else {
        while (i >= 0 && ticker < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * order - 1) {
            splitChild(node, i);
            if (ticker > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], ticker, price);
    }
}

void BTree::splitChild(BTreeNode* parent, int index) {
    BTreeNode* fullChild = parent->children[index];
    BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
    parent->keys.insert(parent->keys.begin() + index, fullChild->keys[order - 1]);
    parent->values.insert(parent->values.begin() + index, fullChild->values[order - 1]);

    newChild->keys.assign(fullChild->keys.begin() + order, fullChild->keys.end());
    newChild->values.assign(fullChild->values.begin() + order, fullChild->values.end());

    if (!fullChild->isLeaf) {
        newChild->children.assign(fullChild->children.begin() + order, fullChild->children.end());
    }

    fullChild->keys.resize(order - 1);
    fullChild->values.resize(order - 1);
    fullChild->children.resize(order);
}

Stock BTree::search(BTreeNode* node, const std::string& ticker) {
    int i = 0;
    while (i < node->keys.size() && ticker > node->keys[i]) {
        i++;
    }

    if (i < node->keys.size() && ticker == node->keys[i]) {
        return Stock(node->keys[i], node->values[i]);
    }

    if (node->isLeaf) {
        return Stock("", 0); // Not found
    }

    return search(node->children[i], ticker);
}

void BTree::insert(const std::string& ticker, double price) {
    BTreeNode* rootNode = root;
    if (rootNode->keys.size() == 2 * order - 1) {
        BTreeNode* newRoot = new BTreeNode(false);
        newRoot->children.push_back(rootNode);
        splitChild(newRoot, 0);
        root = newRoot;
    }
    insertNonFull(root, ticker, price);
}

Stock BTree::searchByTicker(const std::string& ticker) {
    return search(root, ticker);
}

void BTree::inOrderTraversal(BTreeNode* node) const {
    if (node == nullptr) return;

    // Traverse all children of the node (left to right)
    int i;
    for (i = 0; i < node->keys.size(); ++i) {
        // Recurse on the child before this key
        if (!node->isLeaf) {
            inOrderTraversal(node->children[i]);
        }

        // Visit the key-value pair at index i and print in the desired format
        std::cout << "Ticker: " << node->keys[i] << "; Price: " << node->values[i] << std::endl;
    }

    // If the node is not a leaf, recurse on the last child
    if (!node->isLeaf) {
        inOrderTraversal(node->children[i]);
    }
}
