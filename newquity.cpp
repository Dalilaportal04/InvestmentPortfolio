//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//struct Equity {
//    std::string stockName;
//    double stockPrice;
//};
//
//int main() {
//    std::ifstream file("C:/Users/dalil/CLionProjects/InvestmentPortfolio/newquity.json");
//    if (!file.is_open()) {
//        std::cerr << "Error: Could not open the file 'newquity.json'." << std::endl;
//        return 1;
//    }
//
//    std::string line, json;
//    while (std::getline(file, line)) {
//        json += line; // Combine all lines into a single string
//    }
//    file.close();
//
//    std::vector<Equity> equities;
//    std::size_t start = 0, end = 0;
//
//    // Find each JSON object within the array
//    while ((start = json.find("{", start)) != std::string::npos) {
//        end = json.find("}", start);
//        std::string entry = json.substr(start, end - start + 1);
//
//        // Extract stockName
//        std::size_t nameStart = entry.find("\"stockName\":") + 13;
//        std::size_t nameEnd = entry.find("\"", nameStart);
//        std::string stockName = entry.substr(nameStart, nameEnd - nameStart);
//
//        // Extract stockPrice
//        std::size_t priceStart = entry.find("\"stockPrice\":") + 13;
//        std::size_t priceEnd = entry.find(",", priceStart);
//        if (priceEnd == std::string::npos) {
//            priceEnd = entry.find("}", priceStart);
//        }
//        double stockPrice = std::stod(entry.substr(priceStart, priceEnd - priceStart));
//
//        // Add to vector
//        equities.push_back({stockName, stockPrice});
//
//        start = end + 1;
//    }
//
//    // Print the parsed data
//    std::cout << "Equity Data:" << std::endl;
//    for (const auto& equity : equities) {
//        std::cout << "Stock Name: " << equity.stockName
//                  << ", Purchase Price: $" << equity.stockPrice << std::endl;
//    }
//
//    return 0;
//}
