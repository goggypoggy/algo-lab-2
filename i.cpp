#include <iostream>
#include <cstdlib>
#include <cstdint>

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

const int kMaxN = 50'000;
const int kBitsPerDigit = 4;
const int kDigCount = 16;
uint32_t extra[kMaxN];
int count[kDigCount];

int getDigit( uint32_t num, int b ) {
    return (num >> b) & (kDigCount - 1);
}

void CountSort( uint32_t *arr, int n, int b ) {
    // initialize arrays
    for (int i = 0; i < kDigCount; i++) {
        count[i] = 0;
    }

    // count each element depending on type
    for (int i = 0; i < n; i++) {
        int dig = getDigit(arr[i], b);
        count[dig]++;
    }

    // leading sum
    for (int i = 0; i < kDigCount; i++) {
        for (int j = i + 1; j < kDigCount; j++) {
            count[j] += count[i];
        }
    }

    // assemble sorted array
    for (int i = n - 1; i >= 0; i--) {
        int dig = getDigit(arr[i], b);
        extra[count[dig]--] = arr[i];
    }

    // copy memory
    for (int i = 0; i < n; i++) {
        arr[i] = extra[i];
    }
}

void RadixSort( uint32_t *arr, int n ) {
    for (int b = 0; b < 32 / kBitsPerDigit; b++) {
        CountSort(arr, n, b);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    uint32_t n, a, b;
    std::cin >> t >> n >> a >> b;

    while (t--) {
        uint32_t arr[kMaxN];

        for (uint32_t i = 0; i < n; i++) {
            arr[i] = nextRand32(a, b);  // генерируем i-й элемент
        }

        // здесь будет ваш алгоритм
    }
}