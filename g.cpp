#include <iostream>

int main( int argc, char **argv ) {
    int n;
    std::cin >> n;
    int c[101] = {0};

    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        std::cout << c[num] << (i == n - 1 ? "" : " ");
        for (int i = num; i <= 100; i++) {
            c[i]++;
        }
    }
    
    return 0;
}