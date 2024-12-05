#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <string>
#include <vector>
#include <iostream>

// Stock structure for the B+ Tree result
struct Stock {
    double last_price;
    std::string ticker;

    Stock(double price, const std::string& ticker_symbol)
            : last_price(price), ticker(ticker_symbol) {}
};

// BPlusTreeNode class declaration
class BPlusTreeNode {
public:
    bool is_leaf;
    std::vector<double> keys;
    std::vector<std::string> values;
    std::vector<BPlusTreeNode*> children;

    BPlusTreeNode(bool leaf) : is_leaf(leaf) {}
};

// BPlusTree class declaration
class BPlusTree {
private:
    int order; // Maximum number of keys in a node
    BPlusTreeNode* root;

    void splitChild(BPlusTreeNode* parent, int index);
    void insertNonFull(BPlusTreeNode* node, double key, const std::string& value);
    void inOrderTraversal(BPlusTreeNode* node, std::vector<Stock>& result);

public:
    BPlusTree(int order) : order(order), root(nullptr) {}
    void insert(double key, const std::string& value);
    std::vector<Stock> getAllStocks();
    BPlusTreeNode* getRoot() {
        return root; // Assuming 'root' is the member holding the root node
    }
    void printTree(BPlusTreeNode* node, int level = 0);
};

// Function to load data from a JSON file and insert into a BPlusTree
void loadDataFromFile(const std::string& filepath, BPlusTree& tree);

#endif
