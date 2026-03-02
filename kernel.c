#include <stddef.h>
#include <stdint.h>
#include "terminal.h"

void kernel_main(void) {
    terminal_initialize();

    terminal_writestring("FreezeOS v0.6\n");
    terminal_writestring("> ");

    char input[128];
    int pos = 0;

    while (1) {
        char c = terminal_getchar();

        if (c == '\n') {
            input[pos] = 0;

            if (strcmp(input, "help") == 0) {
                terminal_writestring("\nCommands: help, clear, echo, color\n");
            }
            else if (strcmp(input, "clear") == 0) {
                terminal_clear();
            }
            else if (strncmp(input, "echo ", 5) == 0) {
                terminal_writestring("\n");
                terminal_writestring(input + 5);
                terminal_putchar('\n');
            }
            else if (strcmp(input, "color") == 0) {
                terminal_setcolor(0x0A);
            }
            else {
                terminal_writestring("\nUnknown command\n");
            }

            pos = 0;
            terminal_writestring("> ");
        } else {
            input[pos++] = c;
            terminal_putchar(c);
        }
    }
}
