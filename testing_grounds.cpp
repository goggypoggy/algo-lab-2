#include <iostream>
#include <iomanip>

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

void OutputArray( uint32_t *arr, int n ) {
    for (int i = 0; i < n; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << arr[i] << (i == n - 1 ? '\n' : ' ');
    }
}

int main( int argc, char **argv ) {
    int n;
    uint32_t arr[kMaxN];

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    OutputArray(arr, n);
}