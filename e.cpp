#include <cstdint>
#include <cstdlib>
#include <iostream>

uint32_t cur = 0;  // беззнаковое 32-битное число

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

int SpecialPartition(uint32_t *arr, uint32_t l, uint32_t r, uint32_t k) {
    uint32_t pivot = arr[rand(l, r)];

    uint32_t i = l;
    uint32_t j = r - 1;

    while (i <= j) {
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

    if (arr[k] == pivot) {
        return pivot;
    } else if (arr[k] < pivot) {
        return SpecialPartition(arr, l, j + 1, k);
    } else {
        return SpecialPartition(arr, i, r, k);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, k, a, b;
    std::cin >> n >> k >> a >> b;

    uint32_t arr[n];

    for (uint32_t i = 0; i < n; i++) {
        arr[i] = nextRand32(a, b);  // генерируем i-й элемент
    }

    std::cout << SpecialPartition(arr, 0, n, k - 1);
}