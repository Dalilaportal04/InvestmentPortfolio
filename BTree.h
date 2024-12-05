#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <vector>

// Stock class to hold ticker and price
class Stock {
public:
    std::string ticker;
    double price;

    Stock(std::string t = "", double p = 0.0) : ticker(t), price(p) {}
};

// BTree Node
class BTreeNode {
public:
    std::vector<std::string> keys; // Tickers
    std::vector<double> values;    // Prices
    std::vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool leaf = false);
};

// BTree Class
class BTree {
public:
    BTree(int order);
    void insert(const std::string& ticker, double price);
    Stock searchByTicker(const std::string& ticker);
    static void loadDataFromFile(const std::string& filepath, BTree& tree);
    void inOrderTraversal(BTreeNode* node) const;

    BTreeNode* root;
private:
    int order;

    // Insert a new stock into a node that is not full
    void insertNonFull(BTreeNode* node, const std::string& ticker, double price);

    // Split the child of a node
    void splitChild(BTreeNode* parent, int index);

    // Search for a ticker in the tree
    Stock search(BTreeNode* node, const std::string& ticker);
};

#endif // BTREE_H
