#include <iostream>
#include <fstream>
#include <vector>
#include "BTree.h"
#include "heap2.h"
#include "jsoncpp/json.hpp"

using json = nlohmann::json;

int main() {
    // Step 1: Initialize the BTree (Assume it is already populated)
    BTree tree(3);  // BTree of order 3

    // Read data from the JSON file (all_stocks.json)
    std::ifstream inputFile("../Data/all_stocks.json");
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    // Parse the JSON data
    json all_stockData;
    inputFile >> all_stockData;

    // Insert stock data into the tree
    for (const auto &stock : all_stockData) {
        if (!stock.contains("ticker") || !stock.contains("last_price")) {
            std::cerr << "Error: Missing expected keys in JSON object: " << stock.dump() << std::endl;
            continue;
        }
        std::string ticker = stock["ticker"];
        int price = stock["last_price"];
        tree.insert(ticker, price);
    }

    // Open the second JSON file (newquity.json)
    std::ifstream inputFile1("../Data/newquity.json");
    if (!inputFile1) {
        std::cerr << "Error opening JSON file." << std::endl;
        return 1;
    }

    // Parse the JSON data for stock data
    json stockData;
    try {
        inputFile1 >> stockData;
    } catch (const json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return 1;
    }

    // Validate that the JSON is an array
    if (!stockData.is_array()) {
        std::cerr << "Error: Expected JSON to be an array." << std::endl;
        return 1;
    }

    // Initialize the max-heap
    int heap[20] = {0};
    int size = 0;
    int capacity = 20;

    // Vector to hold tickers and deltas
    std::vector<json> holdingData;

    // Process each stock in the JSON array (newquity.json)
    for (const auto& stock : stockData) {
        if (!stock.contains("stockName") || !stock.contains("stockPrice")) {
            std::cerr << "Error: Missing keys in JSON object: " << stock.dump() << std::endl;
            continue;
        }

        std::string stockName = stock["stockName"];
        double stockPrice = stock["stockPrice"];

        // Search for the stock in the BTree
        Stock foundStock = tree.searchByTicker(stockName);
        if (foundStock.ticker.empty()) {
            std::cerr << "Error: Stock with ticker " << stockName << " not found in the BTree." << std::endl;
            continue;
        }

        // Calculate the delta
        int delta = static_cast<int>(foundStock.price - stockPrice);

        // Insert delta into the max-heap
        insertStock(heap, size, capacity, delta);

        // Add the ticker and delta to the holdingData vector
        holdingData.push_back({{"ticker", stockName}, {"delta", delta}});
    }

    // Save the data to a JSON file for the frontend
    std::ofstream outputFile("../Data/holdings.json");
    outputFile << std::setw(4) << holdingData << std::endl;

    // Display the final heap
    std::cout << "Final max-heap:" << std::endl;
    printHeap(heap, size);

    return 0;
}
