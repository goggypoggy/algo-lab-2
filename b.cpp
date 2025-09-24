#include <cmath>
#include <cstring>
#include <iostream>

/* -- DEBUG FUNCTIONS AND VARIABLES -- */
int kHeapOutTabSize = 1;

void NumOut( int x, int desired_size ) {
    int actual_size = 1;
    if (abs(x) >= 10) {
        actual_size = std::ceil(std::log10(x));
    }

    std::cout << x;
    if (actual_size < desired_size) {
        for (int i = 0; i < desired_size - actual_size; i++) {
            std::cout << ".";
        }
    }
}

void TabOut( int desired_size ) {
    for (int i = 0; i < desired_size; i++) {
        std::cout << " ";
    }
}

void HeapOut( int *heap, int N ) {
    int max_level = std::ceil(std::log2(N));

    int ind = 0;
    for (int l = max_level; l > 0; l--) {
        std::cout << max_level - l << ": ";
        
        TabOut(kHeapOutTabSize * (std::pow(2, l - 1) - 1));
        
        for (int k = 0; k < std::pow(2, max_level - l); k++) {
            NumOut(heap[ind], kHeapOutTabSize);
            TabOut(kHeapOutTabSize * (std::pow(2, l) - 1));
            ind++;
            if (ind >= N) {
                break;
            }
        }

        std::cout << std::endl;
    }
}

int ConvertStrToInt( char *str ) {
    int result = 0;

    int max_pow10 = 0;
    while (str[max_pow10] != 0) {
        max_pow10++;
    }

    for (int i = 0; i < max_pow10; i++) {
        result += (str[i] - '0') * std::pow(10, max_pow10 - 1 - i);
    }

    return result;
}

void ParseArgs( int argc, char **argv ) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i - 1], "--tab-size") == 0) {
            kHeapOutTabSize = ConvertStrToInt(argv[i]);
        }
    }
}
/* -- END OF DEBUG FUNCS AND VARS -- */

void Swap( int *a, int *b ) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void SiftDown( int i, int *heap, int heap_size ) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left >= heap_size) {
        return;
    }

    int j = left;
    if (right < heap_size && heap[right] > heap[left]) {
        j = right;
    }

    if (heap[i] < heap[j]) {
        Swap(heap + i, heap + j);
    } else {
        return;
    }

    SiftDown(j, heap, heap_size);
}

void BuildHeap( int *heap, int heap_size ) {
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        SiftDown(i, heap, heap_size);
        std::cout << "After SiftDown-ing " << i << ":\n";
        HeapOut(heap, heap_size);
    }
}

int main( int argc, char **argv ) {
    ParseArgs(argc, argv);
    
    int A[100000] = {0};
    int N;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::cout << "Unbuilt heap:\n";
    HeapOut(A, N);

    BuildHeap(A, N);

    std::cout << "Built heap:\n";
    HeapOut(A, N);

    return 0;
}