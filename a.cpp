#include <iostream>

int Sort( int *A, int N ) {
    int count = 0;

    for (int i = 1; i < N; i++) {
        int mem = A[i];
        
        int j = i;
        
        while (j > 0) {
            count++;
            if (mem < A[j - 1]) {
                A[j] = A[j - 1];               
            } else {
                break;
            }
            j--;
        }

        A[j] = mem;
        
        /*
        // Output for debugging
        for (int k = 0; k < N; k++)
            std::cout << A[k] << " ";
        std::cout << ": inserting " << mem << ", count = " << count << std::endl;
        */
    }
    
    return count;
}

int main( int argc, char **argv ) {
    int A[100];
    int N;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::cout << Sort(A, N);

    return 0;
}