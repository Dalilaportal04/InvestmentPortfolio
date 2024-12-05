#include <iostream>
#include <fstream>
#include "BTree.h"
#include "heap2.h"
#include "jsoncpp/json.hpp"

using json = nlohmann::json;


int main() {
    BTree tree(3);  // B-tree of order 3

    // Read data from the JSON file
    std::ifstream inputFile("../Data/all_stocks.json");
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    // Parse the JSON data
    json stockData;
    inputFile >> stockData;

    // Insert stock data into the tree
    for (const auto& stock : stockData) {
        std::string ticker = stock["ticker"];
        int price = stock["last_price"];
        tree.insert(ticker, price);
    }

    // Display the in-order traversal
    std::cout << "In-order traversal of the BTree:" << std::endl;
    tree.inOrderTraversal(tree.root);
    std::cout << std::endl;

    // Initialize the heap (size and capacity are defined)
    int arr[20] = {0};  // Initialize with zeros (size 20 for flexibility)
    int size = 0;  // Start with an empty heap
    int capacity = 20;  // Initial capacity of the heap array

    // Build the initial heap using heapify (though it's empty at this point)
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    // Loop to continuously accept user inputs
    while (true) {
        std::string tickerInput;
        int purchasePrice;
        // Prompt the user for ticker and purchase price
        std::cout << "Enter ticker (or -1 to quit): ";
        std::cin >> tickerInput;
        // Check if the user wants to exit the loop
        if (tickerInput == "-1") {
            std::cout << "Exiting program." << std::endl;
            break;
        }
        std::cout << "Enter purchase price: ";
        std::cin >> purchasePrice;
        // Search for stock by ticker
        Stock foundStock = tree.searchByTicker(tickerInput);
        if (foundStock.ticker.empty()) {
            std::cout << "Stock with ticker " << tickerInput << " not found.\n";
        }
        else {
            int delta = foundStock.price - purchasePrice;
            insertStock(arr, size, capacity, delta);
            for (int i = size; i >= 0; i--) {
                heapify(arr, size, i);
            }
            cout << "Heap after inserting delta: ";
            printHeap(arr, size);
        }
    }

    return 0;
}