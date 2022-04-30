#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;

int linearSearchIterative (const int arr[], const int len, const int val);
int linearSearchRecursive (const int arr[], const int len, const int val, const int index = 0);
int binarySearch          (const int arr[], const int len, const int val);
int jumpSearch            (const int arr[], const int len, const int val);

void sArrayGen (int* arr, const int len); // Sorted array generator
void swap(int* a, int* b);

int main() {
    // Driver code

    // Most of the information is grouped as arrays for easy testing later
    int const arrCount = 12;
    int const sizes[arrCount] = {10, 20, 50, 100, 200, 500, 1000, 1500, 2500, 5000, 10000, 12345};
    int* arrs[arrCount];
    for (int i = 0; i < arrCount; i++) {
        int *tmp = new int[sizes[i]];

        int* ptr = tmp;

        arrs[i] = ptr;
    }

    string const algNames[arrCount] = {"Iterative Linear Search", "Recursive Linear Search", "Binary Search", "Jump Search"};
    char const cases[4] = {'a', 'b', 'c', 'd'};

    // Key arrays' template:
    // keys[#] = {.., fromStart, fromMiddle, fromEnd, non-existent, ..}
    int keys[arrCount * 4];

    for (int arrCnt = 0; arrCnt < arrCount; arrCnt++) {
        sArrayGen(arrs[arrCnt], sizes[arrCnt]);
        keys[arrCnt * 4 + 0] = (arrs[arrCnt])[sizes[arrCnt] / 10 * 1];
        keys[arrCnt * 4 + 1] = (arrs[arrCnt])[sizes[arrCnt] / 10 * 5];
        keys[arrCnt * 4 + 2] = (arrs[arrCnt])[sizes[arrCnt] / 10 * 9];

        // Finding a value that is not in the array but in the array's value range
        int n = (arrs[arrCnt])[sizes[arrCnt] / 10 * 4];
        while (binarySearch(arrs[arrCnt], sizes[arrCnt], n) != -1 || n < sizes[arrCnt] * 10)
            n++;
        keys[arrCnt * 4 + 3] = n;
    }

    int measMult = 5000000; // Measure multiplier
    for (int i = 0; i < 4; i++) { // To choose algorithm
        if (i == 2) {measMult = 5000000 * 50;}
        else if (i == 3) {measMult = 5000000 * 2;}
        else {measMult = 5000000;}
        for (int j = 0; j < 4; j++) { // To choose case (a,b,c,d)
            for (int k = 0; k < arrCount; k++) { // To choose array
                double duration;
                clock_t startTime = clock();

                switch (i) {
                    case 0:
                        for (int s = 0; s < measMult / sizes[k]; s++) {
                            linearSearchIterative(arrs[k], sizes[k], keys[k * 4 + j]);
                        } break;
                    case 1:
                        for (int s = 0; s < measMult / sizes[k]; s++) {
                            linearSearchRecursive(arrs[k], sizes[k], keys[k * 4 + j]);
                        } break;
                    case 2:
                        for (int s = 0; s < measMult / sizes[k]; s++) {
                            binarySearch(arrs[k], sizes[k], keys[k * 4 + j]);
                        } break;
                    case 3:
                        for (int s = 0; s < measMult / sizes[k]; s++) {
                            jumpSearch(arrs[k], sizes[k], keys[k * 4 + j]);
                        } break;
                }

                duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
                duration = (duration) / (measMult / sizes[k]);

                cout << "Duration of " << algNames[i] << " with array length " << sizes[k] << " for the case " << cases[j] << " is " << duration << " milliseconds.\n";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

int linearSearchIterative(const int arr[], const int len, const int val) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == val)
            return i;
    }
    return -1;
}

int linearSearchRecursive(const int arr[], const int len, const int val, const int index) {
    if (len == 0)
        return -1;

    if (arr[index] == val)
        return index;

    if (index == len - 1)
        return -1;

    return linearSearchRecursive(arr, len, val, index + 1);
}

int binarySearch(const int arr[], const int len, const int val) {
    int low = 0, high = len - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] < val)
            low = mid + 1;
        else if (arr[mid] > val)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}

int jumpSearch(const int arr[], const int len, const int val) {
    int step = sqrt(len);

    int prev = 0;
    while (arr[min(step, len) - 1] < val) {
        prev = step;
        step += sqrt(len);

        if (prev >= len)
            return -1;
    }

    while (arr[prev] < val) {
        prev++;

        if (prev == min(step, len))
            return -1;
    }

    if (arr[prev] == val)
        return prev;

    return -1;
}

void sArrayGen (int arr[], const int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = rand() % (len * 10);
    }

    // Built-in bubble sort
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
