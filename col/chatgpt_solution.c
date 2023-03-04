// Prompt:
// What are 5 4 byte ints whose sum equals 0x21DD09EC?
#include <stdio.h>

int main() {
    unsigned long target = 0x21DD09EC;
    unsigned long i, j, k, l, m;
    for (i = 0; i <= 0xFFFFFFFF; i++) {
        for (j = 0; j <= 0xFFFFFFFF; j++) {
            for (k = 0; k <= 0xFFFFFFFF; k++) {
                for (l = 0; l <= 0xFFFFFFFF; l++) {
                    m = target - i - j - k - l;
                    if (m <= 0xFFFFFFFF) {
                        printf("%08lx %08lx %08lx %08lx %08lx\n", i, j, k, l, m);
                        return 0;
                    }
                }
            }
        }
    }
    printf("No solution found.\n");
    return 0;
}
