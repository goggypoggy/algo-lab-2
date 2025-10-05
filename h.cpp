#include <iostream>
#include <cstdint>

const int kMaxN = 10'000;

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
        std::cin >> popularity[i] >> stability[i];
        I[i] = i;
    }

    Sort(I, stability, N);
    Sort(I, popularity, N);

    OutputIndex(I, N);

    int headliner_count = 1;
    int headliners[kMaxN] = {I[N - 1]};
    int highest_stab = stability[I[N - 1]];

    for (int i = N - 2; i >= 0; i--) {
        if (stability[I[i]] > highest_stab) {
            headliners[headliner_count++] = I[i];
            highest_stab = stability[I[i]];
        }
    }

    std::cout << headliner_count << std::endl;
    OutputIndex(headliners, headliner_count);

    return 0;
}

/*
8   
-1 1
-1 4
0 2
0 10
1 7
1 9
2 1
2 3
*/