//
// Created by likoy on 11/19/2024.
//

#include "Push_Test.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(){
    ifstream file("data.csv");
    string line;

    while (getline(file, line)){
        cout << line << endl;
    }
    return 0;
}