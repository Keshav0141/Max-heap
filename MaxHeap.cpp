

#include <iostream>
using namespace std;

class maxHeap {
    int* heap;
    int size;

    // Swap two elements
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Max-heapify to maintain heap property
    void maxHeapify(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            maxHeapify(largest);
        }
    }

public:
    maxHeap(int* arr, int n) {
        heap = arr;
        size = n;
        buildHeap();
    }

    void buildHeap() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            maxHeapify(i);
        }
    }

    // Extract the maximum element 
    int extractMaxElement() {
        if (size == 0) {
            return -1;
        }
        
        swap(heap[0], heap[size - 1]);  // Swap the root (max element) with the last element in the heap
        size--;  // Reduce the size of the heap
        maxHeapify(0);  // Restore heap property
        return heap[size];  // The max element is now at the end of the array, outside heap
    }

    // Print the current heap
    void printHeap() {
        if (size == 0) {
            cout << ">> HEAP IS EMPTY!!" << endl;
            return;
        }
        cout << "\n>> Current heap: " << "[ ";
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << "]" <<endl;
    }

    // Print full array including extracted elements
    void printFullArray(int* extractedElements, int n, int extractedCount) {
        cout << "\n>> Full array (including extracted elements): " << "[ ";
        for (int i = 0; i < n; i++) {
            cout << heap[i] << " ";
            // Print a placeholder when we reach the current size of the heap
            if (i == size - 1) {
                cout << "| ";
            }
        }

        cout << "]"<< endl;
    }
};

int main() {
    int choice, element, n;

    cout << "Enter the number of elements to build the heap: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    maxHeap h(arr, n);
    h.printHeap();

    int* extractedElements = new int[n];
    int extractedCount = 0;

    do {
        cout << "\nMax Heap Operations:\n";
        cout << "\t1. Delete (extract max) element\n";
        cout << "\t2. Print sorted sequence of deleted elements\n";
        cout << "\t3. Print full array (including deleted elements)\n";
        cout << "\t4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                element = h.extractMaxElement();
                if (element != -1) {
                    cout << "\n>> Extracted max element: " << element << endl;
                    extractedElements[extractedCount++] = element; // Store extracted element
                }
                h.printHeap();
                break;
            case 2:
                // Print only the sorted sequence of deleted elements
                if (extractedCount == 0) {
                    cout << "\nNo elements have been deleted yet." << endl;
                } else {
                    
                    cout << "\n>> Sorted sequence of deleted elements: " << "[ ";
                    for (int i = extractedCount - 1; i >= 0; i--) {
                        cout << extractedElements[i] << " ";
                    }
                    cout << "]" << endl;
                }
                break;
            case 3:
                // Print full array including extracted elements
                h.printFullArray(extractedElements, n, extractedCount);  
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please enter 1, 2, 3, or 4.\n";
        }
    } while (choice != 4);

    delete[] arr;
    delete[] extractedElements;

    return 0;
}