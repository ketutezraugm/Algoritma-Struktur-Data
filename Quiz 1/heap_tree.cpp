#include <iostream>
using namespace std;

class Node {
private:
    int iData;

public:
    Node(int key) {
        iData = key;
    }

    int getKey() {
        return iData;
    }

    void setKey(int id) {
        iData = id;
    }
};

class Heap {
private:
    Node** heapArray;
    int maxSize;
    int currentSize;

    void trickleDown(int index) {
        int smallerChild;
        Node* top = heapArray[index];
        while (index * 2 <= currentSize) {
            int leftChild = index * 2;
            int rightChild = leftChild + 1;

            if (rightChild <= currentSize && heapArray[rightChild]->getKey() < heapArray[leftChild]->getKey()) {
                smallerChild = rightChild;
            } else {
                smallerChild = leftChild;
            }

            if (top->getKey() <= heapArray[smallerChild]->getKey()) {
                break;
            }
            heapArray[index] = heapArray[smallerChild];
            index = smallerChild;
        }
        heapArray[index] = top;
    }

public:
    Heap(int mx) {
        maxSize = mx;
        currentSize = 0;
        heapArray = new Node*[maxSize + 1];
    }

    ~Heap() {
        for (int i = 1; i <= currentSize; ++i) {
            delete heapArray[i];
        }
        delete[] heapArray;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == maxSize;
    }

    bool insert(int key) {
        if (isFull()) {
            return false;
        }
        Node* newNode = new Node(key);
        heapArray[++currentSize] = newNode;
        trickleUp(currentSize);
        return true;
    }

    void trickleUp(int index) {
        int parent = index / 2;
        Node* bottom = heapArray[index];

        while (index > 1 && heapArray[parent]->getKey() > bottom->getKey()) {
            heapArray[index] = heapArray[parent];
            index = parent;
            parent = parent / 2;
        }
        heapArray[index] = bottom;
    }

    int extractMin() {
        if (isEmpty()) {
            return -1;
        }
        int minVal = heapArray[1]->getKey();
        delete heapArray[1];
        heapArray[1] = heapArray[currentSize--];
        if (currentSize > 0) {
            trickleDown(1);
        }
        return minVal;
    }

    void heapSort(int sortedArr[]) {
        Heap tempHeap(maxSize);
        for (int i = 1; i <= currentSize; i++) {
            tempHeap.insert(heapArray[i]->getKey());
        }
        for (int i = 0; i < currentSize; i++) {
            sortedArr[i] = tempHeap.extractMin();
        }
    }

    void displayHeap() {
        for (int i = 1; i <= currentSize; ++i) {
            cout << heapArray[i]->getKey() << " ";
        }
        cout << endl;
    }
};

int main() {
    int arr[] = {12, 3, 5, 7, 19, 1, 8, 15, 4, 11, 6, 9, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Initial array: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;

    Heap heap(20);
    for (int i = 0; i < size; ++i) {
        heap.insert(arr[i]);
    }

    cout << "Min Heap: ";
    heap.displayHeap();

    heap.insert(2);
    cout << "Min Heap after insert number 2: ";
    heap.displayHeap();
    cout << endl;

    int sortedArr[size];
    heap.heapSort(sortedArr);
    cout << "Heap Sort in increasing order: ";
    for (int i = 0; i < size; i++) {
        cout << sortedArr[i] << " ";
    }
    cout << endl;

    cout << "Heap Sort in decreasing order: ";
    for (int i = size - 1; i >= 0; i--) {
        cout << sortedArr[i] << " ";
    }
    cout << endl << endl;

    cout << "Priority Queue 1 (smallest element): " << heap.extractMin() << endl;
    cout << "Min Heap after deletion: ";
    heap.displayHeap();

    cout << "Priority Queue 2 (next smallest element): " << heap.extractMin() << endl;
    return 0;
}
