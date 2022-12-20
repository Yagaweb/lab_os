#include <iostream>

void app() {
    int a = 0, b = 3, c = 3;

    for (int i = 0; i < 100000000; i++) {
        a += b * 2 + c - i;
    }
}

int main() {
    const clock_t start = clock();
    
    app();

    const clock_t end = clock();
    
    std::cout << "command took " << (double)(end - start) / CLOCKS_PER_SEC * 100 << " ms\n";
    std::cout << "command took " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

	return 0;
}