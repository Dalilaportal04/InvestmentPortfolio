//
// Created by 9tail on 12/4/2024.
//
//
// Created by 9tail on 12/2/2024.
//

#include <iostream>
#include <algorithm>

using namespace std;
// Partner: Esther O.

int b_plus_tree_root;

void heapify(int arr[], int size, int index)
{
    // largest in max heap is root
    int largest = index;
    // assigning children
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    // check left child
    if (left < size && arr[left] > arr[largest]){
        largest = left;
    }
    // check right child
    if (right < size && arr[right] > arr[largest]){
        largest = right;
    }
    // swap if new max is found and continue
    if (largest != index){
        swap(arr[index], arr[largest]);
        heapify(arr, size, largest);
    }
}


int* extractMax(int arr[], int size)
{
    arr[0] = arr[size - 1];
    size--;
    heapify(arr, size, 0);
    return arr;
    // main prints the final heap array from 0 to size - 2
    // you don't need to print the array but instead return
}