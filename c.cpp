#include <iostream>

const int kMaxN = 1000;

void OutputArray( int *A, int N ) {
    for (int i = 0; i < N; i++) {
        std::cout << A[i] << (i == N - 1 ? "\n" : " ");
    }
}

void OutputFilter( int *I, int *filter, int N ) {
    for (int i = 0; i < N; i++) {
        std::cout << filter[I[i]] << (i == N - 1 ? "\n" : " ");
    }
}

void OutputIndex( int *I, int N ) {
    for (int i = 0; i < N; i++) {
        std::cout << I[i] + 1 << (i == N - 1 ? "\n" : " ");
    }
}

void Swap( int *a, int *b ) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// [l;r)
void MergeSort( int *I, int *filter, int l, int r ) {
    static int B[kMaxN] = {0};

    int mid = (l + r) / 2;

    if (r - l < 2) {
        return;
    }

    MergeSort(I, filter, l, mid);
    MergeSort(I, filter, mid, r);
    
    int i = l;
    int j = mid;
    int k = l;

    while (k < r) {
        if (i < mid && j < r) {
            if (filter[I[i]] <= filter[I[j]]) {
                B[k] = I[i];
                i++;
            } else {
                B[k] = I[j];
                j++;
            }
        } else {
            B[k] = i == mid ? I[j++] : I[i++];
        }
        
        k++;
    }

    for (int k = l; k < r; k++) {
        I[k] = B[k];
    }
}

void Sort( int *I, int *filter, int N ) {
    MergeSort(I, filter, 0, N);
}

int main( int argc, char **argv ) {
    int N;

    int popularity[kMaxN];
    int stability[kMaxN];

    int I[kMaxN];

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        int pop;
        int stab;

        std::cin >> pop >> stab;

        I[i] = i;
        popularity[i] = pop;
        stability[i] = stab;
    }

    std::cout << "Starting array:\n";
    std::cout << "popularity: "; OutputFilter(I, popularity, N);
    std::cout << "stability:  "; OutputFilter(I, stability, N);
    std::cout << "index:      "; OutputIndex(I, N);
    
    Sort(I, stability, N);

    std::cout << "\nSorted by stability:\n";
    std::cout << "popularity: "; OutputFilter(I, popularity, N);
    std::cout << "stability:  "; OutputFilter(I, stability, N);
    std::cout << "index:      "; OutputIndex(I, N);
    
    Sort(I, popularity, N);

    std::cout << "\nSorted by popularity:\n";
    std::cout << "popularity: "; OutputFilter(I, popularity, N);
    std::cout << "stability:  "; OutputFilter(I, stability, N);
    std::cout << "index:      "; OutputIndex(I, N);

    return 0;
}