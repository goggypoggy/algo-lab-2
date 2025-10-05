#include <iostream>
#include <iomanip>

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

const int kMaxN = 50'000;
const int kBitsPerDigit = 4;
const int kDigCount = 16;
uint32_t extra[kMaxN];
int count[kDigCount];

int getDigit( uint32_t num, int b ) {
    return (num >> (b * kBitsPerDigit)) & (kDigCount - 1);
}

void CountSort( uint32_t *arr, int n, int b ) {
    // initialize arrays
    for (int i = 0; i < kDigCount; i++) {
        count[i] = 0;
    }

    // count each element depending on digit
    for (int i = 0; i < n; i++) {
        int dig = getDigit(arr[i], b);
        count[dig]++;
    }

    // leading sum
    for (int i = 1; i < kDigCount; i++) {
        count[i] += count[i - 1];
    }

    // accounting for incorrect numeration
    for (int i = 0; i < kDigCount; i++) {
        count[i]--;
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

int main( int argc, char **argv ) {
    int n;
    uint32_t arr[kMaxN];

    
    /*
    uint32_t testnum = 0x115;
    std::cout << std::hex << testnum << ' ';
    for (int b = 0; b < 8; b++) {
        std::cout << std::hex << (testnum >> (b * kBitsPerDigit)) << ' ';
    }
    std::cout << '\n';
    */

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    //OutputArrayHex(arr, n);
    RadixSort(arr, n);
    //OutputArrayHex(arr, n);
    OutputArray(arr, n);
}

/*
5
23 46 12 95 78

6
12 130926 3941054950 2013898548 197852696 2753287507

10
77328 93 5511095 467991221 83991 2200349 759124 445521 76123985 17774
*/