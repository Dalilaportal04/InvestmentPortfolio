//
// Created by 9tail on 12/4/2024.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void heapify(int arr[], int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(arr[index], arr[largest]);
        heapify(arr, size, largest);
    }
}

int Top(int arr[], int&size){
    int top = arr[0];
    cout << top << endl;
    return top;
}

int* extractMax(int arr[], int& size) {
    arr[0] = arr[size - 1];
    size--;
    heapify(arr, size, 0);
    return arr;
}

void insertStock(int arr[], int& size, int& capacity, int value) {
    if (size == capacity) {
        capacity *= 2;
        int* newArr = new int[capacity];

        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    arr[size] = value;
    size++;

    int i = size - 1;
    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteStock(int arr[], int& size, int key) {
    int index = -1;

    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            index = i;
            break;
        }
    }

    arr[index] = arr[size - 1];
    size--;

    heapify(arr, size, index);
}

void printHeap(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void buildHeap(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }
}

//int delta(int purchase_price, const std::string& ticker, BPlusTree& bptree) {
//
//    double actual_price = bptree.getPrice(ticker);   // getPrice() ?
//
//    int delta_value = purchase_price - actual_price;
//
//    return delta_value;
//}
//    BPlusTree::inOrderTraversal(root, sortedData);
//
//    for (int i = 0; i < sortedData.size(); ++i) {
//        arr[i] = sortedData[i].getPrice();
//    }
//    size = sortedData.size();
//    buildHeap(arr, size);

/*
int main() {

    int purchase_price;
    string ticker;
    int size = 0;
    int capacity = 10;
    int* heap = new int[capacity];
//
//    std::cout << "Enter the ticker symbol of the stock: ";
//    std::cin >> ticker;
//
//    std::cout << "Enter your purchase price for " << ticker << ": ";
//    std::cin >> purchase_price;
//
//    BPlusTree bptree(4);
//    int delta_value = delta(purchase_price, ticker, bptree);   // b tree object ??
//
//    insertStock(heap, size, capacity, delta_value);
//
//    if (delta_value != -1) {
//        cout << "Delta: " << delta_value << std::endl;
//    }


    // hard coded delta
    Stock stock1(500, "A");
    Stock stock2(400, "B");
    double delta = stock1.last_price - stock2.last_price;
    cout << "Diff of 500 and 400 is " << delta << endl;

    // Inserting some values into the heap
    insertStock(heap, size, capacity, 30);
    insertStock(heap, size, capacity, 20);
    insertStock(heap, size, capacity, 50);
    insertStock(heap, size, capacity, 40);
    insertStock(heap, size, capacity, 60);

    cout << "Max-Heap after insertions: ";
    printHeap(heap, size);

    delete[] heap;

    // populating array through insertions



    // deletions



    // heapifying




    // functions testing with pre-built array
//
//    int arr[] = {2, 3, 4, 5, 10, 15};
//    int size = 6;
//    int capacity = 6;
//
//    for (int i = size / 2 - 1; i >= 0; i--) {
//        heapify(arr, size, i);
//    }
//
//    cout << "Max Heap: ";
//    printHeap(arr, size);
//
//    arr[size] = 9;
//    size++;
//    int i = size - 1;
//
//    // code to maintain heap property
//    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
//        swap(arr[i], arr[(i - 1) / 2]);
//        i = (i - 1) / 2;
//    }
//
//    insertStock(arr, size, capacity, 25);
//
//    cout << "adding 25...";
//    cout << "Max Heap after insertion: ";
//    printHeap(arr, size);
//
//    cout << "deleting 5...";
//    deleteStock(arr, size, 5);
//
//    cout << "Max Heap after deletion of 5: ";
//    printHeap(arr, size);
//
//    Top(arr, size);
//
//    cout << "Extracting max now..." << endl;
//    int *max = extractMax(arr, size);
//    printHeap(arr, size);
//
//    cout << "New max of the max heap: " << arr[0] << endl;
//    cout << "Heap after extraction: ";
//    printHeap(arr, size);

    return 0;
}
*/
