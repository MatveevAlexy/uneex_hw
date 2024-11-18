#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int ncol = 6, nrow = 6;
int col_nsym, row_nsym;
char wall, pass;

void passable(char *maze, int *access, int i, int j) {
    if (maze[i * 2 * col_nsym + j * 2 + 1] == pass && !access[(i - 1) * ncol + j]) {
        access[(i - 1) * ncol + j] = 1;
        passable(maze, access, i - 1, j);
    }
    if (maze[(i * 2 + 2) * col_nsym + j * 2 + 1] == pass && !access[(i + 1) * ncol + j]) {
        access[(i + 1) * ncol + j] = 1;
        passable(maze, access, i + 1, j);
    }
    if (maze[(i * 2 + 1) * col_nsym + j * 2] == pass && !access[i * ncol + j - 1]) {
        access[i * ncol + j - 1] = 1;
        passable(maze, access, i, j - 1);
    }
    if (maze[(i * 2 + 1) * col_nsym + j * 2 + 2] == pass && !access[i * ncol + j + 2]) {
        access[i * ncol + j + 1] = 1;
        passable(maze, access, i, j + 1);
    }
}

int main(int argc, char **argv)
{
    wall = '#', pass = '.';
    srand(time(NULL));
    col_nsym = 2 * nrow + 1, row_nsym = 2 * nrow + 1;
    char *maze = calloc(row_nsym * col_nsym, sizeof(*maze));
    for (int i = 0; i < row_nsym; i += 2) {
        for (int j = 0; j < col_nsym; j++) {
            maze[i * col_nsym + j] = wall;
        }
    }
    for (int i = 1; i < row_nsym; i += 2) {
        for (int j = 0; j < col_nsym; j += 2) {
            maze[i * col_nsym + j] = wall;
        }
        for (int j = 1; j < col_nsym; j += 2) {
            maze[i * col_nsym + j] = pass;
        }
    }
    int *access = calloc(ncol * nrow, sizeof(*access)), len = 1;
    access[0] = 1;
    
    while (len < ncol * nrow) {
        for (int i = 1; i < ncol * nrow; i++) {
            access[i] = 0;
        }
        for (int i = 1; i < row_nsym - 1; i += 2) {
            for (int j = 2; j < col_nsym - 1; j += 2) {
                if (rand() % 100 < 10) {
                    maze[i * col_nsym + j] = pass;
                }
            }
        }
        for (int i = 2; i < row_nsym - 1; i += 2) {
            for (int j = 1; j < col_nsym - 1; j += 2) {
                if (rand() % 100 < 20) {
                    maze[i * col_nsym + j] = pass;
                }
            }
        }
        passable(maze, access, 0, 0);
        len = 0;
        for (int i = 0; i < ncol * nrow; i++) {
            len += access[i];
        }
    }
    for (int i = 0; i < row_nsym; i++) {
        write(0, &maze[i * col_nsym], col_nsym);
        printf("\n");
    }
    return 0;
}