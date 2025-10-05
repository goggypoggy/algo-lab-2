#include <iostream>
#include <iomanip>
#include <cstdlib>

const int kOutputWidth = 8;

void OutputArrayHex( uint32_t *arr, int n ) {
    for (int i = 0; i < n; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(kOutputWidth) << arr[i] << std::dec << (i == n - 1 ? '\n' : ' ');
    }
}

template<typename Type>
void OutputArray( Type *arr, int n ) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << (i == n - 1 ? '\n' : ' ');
    }
}

// TESTING GROUNDS ---------------------

const int kMaxN = 10'000'000;

//#define RAND_MAX INT_MAX

// [min; max)
int Rand( int min, int max ) {
    return std::rand() % (max - min) + min;
}

void Swap(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(uint32_t *arr, int l, int r) {
    uint32_t pivot = arr[Rand(l, r)];

    int i = l;
    int j = r - 1;

    while (i <= j) {        
        while (i < r && arr[i] < pivot) {
            i++;
        }
        
        while (j >= l && arr[j] > pivot) {
            j--;
        }

        if (i <= j) {
            Swap(arr + i, arr + j);
            i++;
            j--;
        }
    }
    
    return i;
}

// [l; r)
uint32_t QuickSearch(uint32_t *arr, int l, int r, int k) {
    if (l == r - 1) {
        return arr[l];
    }

    int mid = Partition(arr, l, r);

    if (k < mid) {
        return QuickSearch(arr, l, mid, k);
    } else {
        return QuickSearch(arr, mid, r, k);
    }
}

int main( int argc, char **argv ) {
    int n;
    int k;
    std::cin >> n >> k;

    uint32_t *arr = new uint32_t[n];
    std::srand(42);

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << QuickSearch(arr, 0, n, k - 1);
    delete[] arr;
    
    return 0;
}

/*
5 1
23 46 12 95 78
12

5 3
10 10 10 10 10
10

6 3
12 130926 3941054950 2013898548 197852696 2753287507
197852696

10
77328 93 5511095 467991221 83991 2200349 759124 445521 76123985 17774
*/