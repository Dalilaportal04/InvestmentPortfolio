//
// Created by likoy on 11/19/2024.
//

#include "Push_Test.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    std::ifstream file("data.csv");
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    cout << "please work." << endl;

    return 0;
}


