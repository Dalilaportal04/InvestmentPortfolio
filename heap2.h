//
// Created by 9tail on 12/4/2024.
//

#ifndef CATCHPRACTICE_HEAP2_H
#define CATCHPRACTICE_HEAP2_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function Declarations
void heapify(int arr[], int size, int index);
int Top(int arr[], int& size);
int* extractMax(int arr[], int& size);
void insertStock(int arr[], int& size, int& capacity, int value);
void deleteStock(int arr[], int& size, int key);
void printHeap(int arr[], int size);
void buildHeap(int arr[], int size);

#endif //CATCHPRACTICE_HEAP2_H
