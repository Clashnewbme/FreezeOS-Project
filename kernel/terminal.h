#pragma once
#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_writestring(const char* data);
void terminal_clear(void);
void terminal_setcolor(uint8_t color);
char terminal_getchar(void);

int strcmp(const char* a, const char* b);
int strncmp(const char* a, const char* b, int n);
