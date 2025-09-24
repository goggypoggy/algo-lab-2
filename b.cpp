#include <iostream>

void OutputArray( int *A, int N ) {
    for (int i = 0; i < N; i++) {
        std::cout << A[i] << (i == N - 1 ? "\n" : " ");
    }
}

void Swap( int *a, int *b ) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// [l; r)
void Partition( int l, int r, int *A ) {
    int pivot = A[(l + r) / 2];
    int i = l;
    int j = r - 1;
    
    while (i <= j) {
        while (A[i] < pivot && i < r) {
            i++;
        }

        while (A[j] > pivot && j >= l) {
            j--;
        }

        if (i <= j) {
            Swap(A + i, A + j);
            i++;
            j--;
        }
    }

    if (l < j) {
        Partition(l, j + 1, A);
    }
    if (i < r - 1) {
        Partition(i, r, A);
    }
}

void QuickSort( int *A, int N ) {
    Partition(0, N, A);
}

int main( int argc, char **argv ) {
    int A[100000] = {0};
    int N;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    QuickSort(A, N);
    OutputArray(A, N);

    return 0;
}