#include "terminal.h"

static uint16_t* video = (uint16_t*)0xB8000;
static size_t row = 0;
static size_t col = 0;
static uint8_t color = 0x07;

void terminal_initialize() {
    terminal_clear();
}

void terminal_clear() {
    for (int i = 0; i < 80 * 25; i++) {
        video[i] = (color << 8) | ' ';
    }
    row = 0;
    col = 0;
}

void terminal_putchar(char c) {
    if (c == '\n') {
        row++;
        col = 0;
        return;
    }

    video[row * 80 + col] = (color << 8) | c;
    col++;

    if (col >= 80) {
        col = 0;
        row++;
    }
}

void terminal_writestring(const char* str) {
    for (size_t i = 0; str[i]; i++) {
        terminal_putchar(str[i]);
    }
}

void terminal_setcolor(uint8_t c) {
    color = c;
}

char terminal_getchar() {
    char c;
    __asm__ volatile (
        "xor %%ah, %%ah\n"
        "int $0x16\n"
        : "=a"(c)
        :
    );
    return c;
}
