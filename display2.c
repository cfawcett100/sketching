// You don't need to change this file, or understand anything in it.
// Use this if you can't get SDL to work.

#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct display {
    bool testing;
    char *file;
    char *actual;
    char **expected;
};

// Fail, including the SDL error message if any, and stop the program.
static void fail(char *s1, char *s2) {
    fprintf(stderr, "%s %s\n", s1, s2);
    exit(1);
}

// Check an actual call against the next expected call.
static void check(display *d) {
    bool ended = d->expected[0] == NULL;
    if (!ended && strcmp(d->actual, d->expected[0]) == 0) {
        d->expected = d->expected + 1;
    } else {
        fprintf(stderr, "Failure in sketching: %s\n", d->file);
        if (ended) fail("Unexpected extra call", d->actual);
        fprintf(stderr, "Bad call  %s\n", d->actual);
        fail("Expecting", d->expected[0]);
    }
}

// Create a dummy display for testing.
display *newDisplay(char *file, int width, int height, char **expected) {
    if (expected == NULL) fail("No graphics", "");
    display *d = malloc(sizeof(display));
    d->testing = true;
    d->file = file;
    d->expected = expected;
    d->actual = malloc(100);
    return d;
}

void line(display *d, int x0, int y0, int x1, int y1) {
    sprintf(d->actual, "line(d,%d,%d,%d,%d)", x0, y0, x1, y1);
    check(d);
}

void cline(display *d, int x0, int y0, int x1, int y1, int rgba) {
    sprintf(d->actual, "cline(d,%d,%d,%d,%d,%d)", x0, y0, x1, y1, rgba);
    check(d);
}

void clear(display *d) {
    sprintf(d->actual, "clear(d)");
    check(d);
}

void pause(display *d, int ms) {
    sprintf(d->actual, "pause(d,%d)", ms);
    check(d);
}

char key(display *d) {
    sprintf(d->actual, "key(d)");
    check(d);
    return '?';
}

void end(display *d) {
    bool ended = d->expected[0] == NULL;
    if (! ended) {
        fprintf(stderr, "Failure in sketching: %s\n", d->file);
        fail("Expecting further call", d->expected[0]);
    }
    else printf("Sketch %s OK\n", d->file);
}
