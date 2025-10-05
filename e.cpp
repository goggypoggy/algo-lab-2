#include <cstdint>
#include <cstdlib>
#include <iostream>

const int kMaxN = 10'000'000;

uint32_t cur = 0;  // беззнаковое 32-битное число

void OutputArray( uint32_t *A, uint32_t N, uint32_t k, uint32_t pivot ) {
    for (uint32_t i = 0; i < N; i++) {
        if (i == k) {
            std::cout << ">" << A[i] << "<";
        } else if (A[i] == pivot) {
            std::cout << "[" << A[i] << "]";
        } else {
            std::cout << A[i];
        }
        std::cout << (i == N - 1 ? "\n" : " ");
    }
}

// Генератор 24-битного числа
uint32_t nextRand24(uint32_t a, uint32_t b) {
    cur = cur * a + b;      // вычисляется с переполнениями по модулю 2^32
    return cur >> 8;         // число от 0 до 2^24 - 1
}

// Генератор 32-битного числа на основе двух 24-битных
uint32_t nextRand32(uint32_t a, uint32_t b) {
    uint32_t x = nextRand24(a, b);
    uint32_t y = nextRand24(a, b);
    return (x << 8) ^ y;     // число от 0 до 2^32 - 1
}

// [min; max)
uint32_t rand( uint32_t min, uint32_t max ) {
    return nextRand32(42, 42) % (max - min) + min;
}

void swap(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(uint32_t *arr, int l, int r) {
    uint32_t pivot = arr[rand(l, r)];

    int i = l;
    int j = r - 1;

    while (i <= j && j != (uint32_t)-1) {        
        while (i < r && arr[i] < pivot) {
            i++;
        }
        
        while (j >= l && arr[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(arr + i, arr + j);
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, k, a, b;
    std::cin >> n >> k >> a >> b;

    uint32_t arr[kMaxN];

    for (uint32_t i = 0; i < n; i++) {
        arr[i] = nextRand32(a, b);  // генерируем i-й элемент
        //std::cin >> arr[i];
    }

    std::cout << QuickSearch(arr, 0, n, k - 1);
}

/*
7 3
1 1
8 5 4 6 2 7 9
*/