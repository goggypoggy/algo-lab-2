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

int allowed_steps = 5;

// [l; r)
void Partition( int l, int r, int *A ) {
    if (r - l < 2) {
        return;
    }

    std::cout << "/\"\" [" << l << "; " << r << ") partition \"\"\\\n";
    std::cout << "Index:  ";
    for (int i = l; i < r; i++) {
        std::cout << i << (i == r - 1 ? "\n" : " ");
    }
    std::cout << "Start:  ";
    OutputArray(A + l, r - l);

    int pivot = A[(l + r) / 2];
    int i = l;
    int j = r - 1;
    
    std::cout << "Pivot:  A[" << (l + r) / 2 << "] = " << pivot << std::endl;
    
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

    std::cout << "Result: ";
    OutputArray(A + l, r - l);
    std::cout << "i = " << i << ", j = " << j << std::endl;
    std::cout << "\\__ [" << l << "; " << r << ") partition __/\n\n";

    Partition(l, j + 1, A);
    Partition(i, r, A);
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