#include "BPlusTree.h"
#include "../libs/json.hpp"
#include <fstream>

using json = nlohmann::json;

// Function to read JSON data from a file and insert it into the B+ Tree
void loadDataFromFile(const std::string& filepath, BPlusTree& tree) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    // Parse JSON
    json data;
    file >> data;
    file.close();

    // Insert each stock into the B+ tree
    for (const auto& stock : data) {
        double price = stock["last_price"];
        std::string ticker = stock["ticker"];

        // Debugging output
        if (ticker.empty()) {
            std::cerr << "Warning: Empty ticker for price " << price << "\n";
        } else {
            std::cout << "Inserting: Price=" << price << ", Ticker=" << ticker << "\n";
        }

        tree.insert(price, ticker);
    }
}

void BPlusTree::splitChild(BPlusTreeNode* parent, int index) {
    std::cout << "Splitting child at index " << index << "\n";
    BPlusTreeNode* node = parent->children[index];
    int mid = node->keys.size() / 2;

    BPlusTreeNode* newNode = new BPlusTreeNode(node->is_leaf);

    // Move keys and children
    newNode->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
    node->keys.resize(mid);

    if (node->is_leaf) {
        newNode->values.assign(node->values.begin() + mid + 1, node->values.end());
        node->values.resize(mid + 1);
    } else {
        newNode->children.assign(node->children.begin() + mid + 1, node->children.end());
        node->children.resize(mid + 1);
    }

    parent->keys.insert(parent->keys.begin() + index, node->keys[mid]);
    parent->children.insert(parent->children.begin() + index + 1, newNode);

    // Ensure the mid key is moved to the parent
    if (node->is_leaf) {
        newNode->values.insert(newNode->values.begin(), node->values[mid]);
        node->values.erase(node->values.begin() + mid);
    }

    std::cout << "Split completed\n";
}

void BPlusTree::insertNonFull(BPlusTreeNode* node, double key, const std::string& value) {
    if (node->is_leaf) {
        // Ensure correct insertion position for both price and ticker
        auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
        int pos = it - node->keys.begin();

        node->keys.insert(it, key);
        node->values.insert(node->values.begin() + pos, value);  // Insert ticker in the right position
    } else {
        // Recurse into the correct child if internal node
        auto it = std::upper_bound(node->keys.begin(), node->keys.end(), key);
        int pos = it - node->keys.begin();

        if (node->children[pos]->keys.size() == order - 1) {
            splitChild(node, pos);  // Split child if full
            if (key > node->keys[pos]) pos++;
        }

        insertNonFull(node->children[pos], key, value);
    }
}

void BPlusTree::insert(double key, const std::string& value) {
    if (!root) {
        root = new BPlusTreeNode(true);
    }

    if (root->keys.size() == order - 1) {
        BPlusTreeNode* newRoot = new BPlusTreeNode(false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        root = newRoot;
    }
    insertNonFull(root, key, value);
}

void BPlusTree::inOrderTraversal(BPlusTreeNode* node, std::vector<Stock>& result) {
    if (node->is_leaf) {
        // Traverse all keys (prices) and their corresponding values (tickers) in this leaf node
        for (size_t i = 0; i < node->keys.size(); i++) {
            result.emplace_back(node->keys[i], node->values[i]);  // Correctly add price and ticker pair
        }
    } else {
        // Traverse internal nodes (non-leaf)
        for (size_t i = 0; i < node->keys.size(); i++) {
            inOrderTraversal(node->children[i], result);
            // Add the current key and the correct ticker
            result.emplace_back(node->keys[i], "");  // Ensure this is only done for internal nodes, if necessary
        }
        inOrderTraversal(node->children[node->keys.size()], result);
    }
}

std::vector<Stock> BPlusTree::getAllStocks() {
    std::vector<Stock> result;
    inOrderTraversal(root, result);
    return result;
}
