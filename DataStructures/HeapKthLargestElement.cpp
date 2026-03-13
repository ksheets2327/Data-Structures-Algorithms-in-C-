///////////////////////////////////////////////////////////////
// Name: Kassidie Sheets
// Filename: HeapKthLargestElement.cpp
// Course: Data Structures  COP3415
// Last Modification: 4/11/2024
//////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

const int MAX_HEAP_SIZE = 10000;

// Min heap implementation
class MinHeap {
public:
    int* heapArr;
    int capacity;
    int heapSize;

    MinHeap(int cap) {
        heapSize = 0;
        capacity = cap;
        heapArr = new int[cap];
    };

    //Get minimum value from heap
    int extractMin() {
        int retval;
        if (heapSize > 0) {
            retval = heapArr[1];
            heapArr[1] = heapArr[heapSize];
            heapSize--;
            percolateDown(1);
            return retval;
        }
        else
            return -1;
    }

    //Create Heap
    void Heapify() {
        for (int i = heapSize / 2; i > 0; i--)
            percolateDown(i);
    };


    void percolateDown(int index) {
        int min;
        if ((2 * index + 1) <= heapSize) {
            min = minimum(heapArr[2 * index], 2 * index, heapArr[2 * index + 1], 2 * index + 1);
            if (heapArr[index] > heapArr[min]) {
                swap(index, min);
                percolateDown(min);
            }
        }
        else if (heapSize == 2 * index) {
            if (heapArr[index] > heapArr[2 * index])
                swap(index, 2 * index);
        }
    };

    //Get minimum of two numbers
    int minimum(int a, int indexa, int b, int indexb) {
        if (a < b)
            return indexa;
        else
            return indexb;
    };

    swap 
    void swap(int index1, int index2) {
        int temp = heapArr[index1];
        heapArr[index1] = heapArr[index2];
        heapArr[index2] = temp;
    };

    MinHeap* arrayToHeap(int* values, int length) {
        MinHeap* h = new MinHeap(length);
        for (int i = 1; i <= length; i++)
            h->heapArr[i] = values[i - 1];
        h->heapSize = length;
        h->Heapify();
        return h;
    };
};

//sort an array from smallest elements to largest elements
int* sort(int values[], int length) {
    MinHeap* h = new MinHeap(length);
    h = h->arrayToHeap(values, length);
    for (int i = 0; i < length; i++)
        values[i] = h->extractMin();
    return values;
};

// Function to find the kth largest element in an array
int findKthLargest(int arr[], int n, int k) {
    int cycle = n - k; 
    int *newarr = sort(arr, n);
    return newarr[cycle];
}

//Print the contents of an array
void printArr(int* arr, int n) {
    cout << "\nnums = [";
    for (int i = 0; i < n; i++) {
        if (i == n - 1)
            cout << arr[i];
        else
            cout << arr[i] << ",";
    }
    cout << "]" << endl;
};

//Driver
int main() {
    int arr1[] = { 3,2,1,5,6,4 };

    int n = sizeof(arr1) / sizeof(arr1[0]);
    int k = 2;

    printArr(arr1, n);
    cout << "Kth largest element: " << findKthLargest(arr1, n, k) << endl;

    int arr2[] = { 3,2,3,1,2,4,5,5,6 };

    n = sizeof(arr2) / sizeof(arr2[0]);
    k = 4;

    printArr(arr2, n);
    cout << "Kth largest element: " << findKthLargest(arr2, n, k) << endl;

    int arr3[] = { 10,7,11,5,27,8,9,45 };

    n = sizeof(arr3) / sizeof(arr3[0]);
    k = 3;

    printArr(arr3, n);
    cout << "Kth largest element: " << findKthLargest(arr3, n, k) << endl;

    int arr4[] = { 100,200,300,400,500 };

    n = sizeof(arr4) / sizeof(arr4[0]);
    k = 2;

    printArr(arr4, n);
    cout << "Kth largest element: " << findKthLargest(arr4, n, k) << endl;

    int arr5[] = { 1,2,3,4,5 };

    n = sizeof(arr5) / sizeof(arr5[0]);
    k = 5;

    printArr(arr5, n);
    cout << "Kth largest element: " << findKthLargest(arr5, n, k) << endl;

    return 0;

};






