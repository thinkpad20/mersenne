#include <stdio.h>

void ms_init(int);
int ms_rand(void);
void ms_generate(void);

// Create a length 624 array to store the state of the generator
int MT[624];
int idx;
// Initialize the generator from a seed
void ms_init(int seed) {
    idx = 0;
    MT[0] = seed;
    for (int i=1; i < 624; ++i) { // loop over each other element
        unsigned long p = 1812433253 * (MT[i-1] ^ (MT[i-1] >> 30)) + i;
        MT[i] = p & 0xffffffff; // get last 32 bits of p
    }
}
 
 // Extract a tempered pseudorandom number based on the index-th value,
 // calling generate_numbers() every 624 numbers
int ms_rand() {
    if (idx == 0)
        ms_generate();

    int y = MT[idx];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 2636928640);
    y = y ^ ((y << 15) & 4022730752);
    y = y ^ (y >> 18);

    idx = (idx + 1) % 624;
    return y;
}
 
// Generate an array of 624 untempered numbers
void ms_generate() {
    for (int i = 0; i < 624; ++i) {
        int y = (MT[i] & 0x80000000)                // bit 31 (32nd bit) of MT[i]
                + (MT[(i+1) % 624] & 0x7fffffff);   // bits 0-30 (first 31 bits) of MT[...]
        MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
        if (y % 2) { // y is odd
            MT[i] = MT[i] ^ (2567483615); // 0x9908b0df
        }
    }
}

#ifndef __NOMAIN__

int main() {
    ms_init(47);
    int array[20];
    for (int i = 0; i < 20; ++i)
        array[i] = 0;
    for (int i = 0; i < 1e8; ++i)
        array[ms_rand() % 20]++;
    for (int i = 0; i < 20; ++i)
        printf("%d\n", array[i]);

    return 0;
}

#endif