#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <tgmath.h>

void div_convert(uint32_t n, int base, char *out) {
    char temp [65]; // Temporary buffer
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    // Extract digits from right to left
    while (n > 0) {
        int remainder = n % base;
        n = n / base;

        // Convert digit to character
        if (remainder < 10)
            temp[pos++] = '0' + remainder;
        else
            temp[pos++] = 'A' + (remainder - 10);
    }

    // Reverse the result
    for (int i = 0; i < pos; ++i) {
        out[i] = temp[pos - i - 1];
    }

    out[pos] = '\0';
}

void sub_convert(uint32_t n, int base, char *out) {
    char temp[65];
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    int power = 0;
    while (pow(base, power + 1) <= n) {
        power++;
    }

    while (power >= 0) {
        uint32_t power_value = (uint32_t)pow(base, power);
        int digit = n / power_value;
        n = n - digit * power_value;

        if (digit < 10) {
            temp[pos++] = '0' + digit;
        } else {
            temp[pos++] = 'A' + (digit - 10);  // For bases > 10 (like hex)
        }

        power--;
    }

    temp[pos] = '\0';
    strcpy(out, temp);
}

void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];

    // Original number
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

    // AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);
}