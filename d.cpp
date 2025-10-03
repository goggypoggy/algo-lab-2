#include <iostream>
#include <cstdint>

const int MAXN = 1'000'000;  // максимум n по условию
uint32_t arr[MAXN];

uint32_t cur = 0;              // текущее значение генератора

// Генератор 24-битных чисел по условию задачи
uint32_t nextRand24(uint32_t a, uint32_t b) {
    // 32-битные переполнения (uint32_t автоматически усекает до 2^32)
    cur = cur * a + b;
    return cur >> 8;  // берём старшие 24 бита (сдвиг вправо на 8)
}

int main( int argc, char **argv ) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, m, a, b;
    std::cin >> n >> m >> a >> b;

    // Генерируем n элементов
    for (uint32_t i = 0; i < n; i++) {
        uint32_t x = nextRand24(a, b) % m; // получаем 24-битное значение по модулю m
        arr[i] = x;                        // записываем в массив
    }

    // Далее используйте arr[0..n-1] для подсчёта инверсий
    
    

    return 0;
}