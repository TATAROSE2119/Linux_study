#include <stdio.h>

// 使用 restrict 关键字的函数
void add_arrays(int *restrict a, int *restrict b, int *restrict c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    size_t n = 5;
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {10, 20, 30, 40, 50};
    int c[n];

    add_arrays(a, b, c, n);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    return 0;
}