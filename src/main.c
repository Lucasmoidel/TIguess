#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <debug.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#define MAX_LINES 10
#define MAX_LINE_LEN 30

char lines[MAX_LINES][MAX_LINE_LEN];
uint8_t line_count = 0;

void redraw_screen(void) {
    os_ClrHome();
    for (uint8_t i = 0; i < line_count; i++) {
        os_SetCursorPos(i, 0);
        os_PutStrLine(lines[i]);
    }
}

void scroll_add(const char *line) {
    if (line_count < MAX_LINES) {
        strncpy(lines[line_count], line, MAX_LINE_LEN - 1);
        lines[line_count][MAX_LINE_LEN - 1] = '\0';
        line_count++;
    } else {
        memmove(lines[0], lines[1], (MAX_LINES - 1) * MAX_LINE_LEN);
        strncpy(lines[MAX_LINES - 1], line, MAX_LINE_LEN - 1);
        lines[MAX_LINES - 1][MAX_LINE_LEN - 1] = '\0';
    }
    redraw_screen();
}

int main(void) {
    srand(time(NULL));
    int randomint = (rand() % 100) + 1;

    char guess[8] = {0};
    char msg[MAX_LINE_LEN] = {0};

    os_ClrHome();
    line_count = 0;

    while (1) {
        memset(guess, 0, sizeof(guess));
        os_GetStringInput("guess a number (1-100):", guess, sizeof(guess));
        int intguess = atoi(guess);

        scroll_add("");

        if (intguess <= 0 || intguess > 100) {
            snprintf(msg, sizeof(msg), "%s is out of range", guess);
            scroll_add(msg);
            scroll_add("");
            
        } else if (intguess < randomint) {
            snprintf(msg, sizeof(msg), "%s was too low", guess);
            scroll_add(msg);
            scroll_add("");
        } else if (intguess > randomint) {
            snprintf(msg, sizeof(msg), "%s was too high", guess);
            scroll_add(msg);
            scroll_add("");
        } else {
            snprintf(msg, sizeof(msg), "%s was correct", guess);
            scroll_add("you did it");
            scroll_add(msg);
            break;
        }
    }

    while (!os_GetCSC());
    return 0; // exit cleanly
}
