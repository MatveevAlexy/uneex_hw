#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_LEN 1024

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Usage: %s infile outfile\n", argv[0]);
        return 0;
    }
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Infile and outfile cannot be the same file\n");
        return 0;
    }
    int fd_in, fd_out;
    if ((fd_in = open(argv[1], O_RDONLY)) == -1) {
        fprintf(stderr, "Error opening infile %s\n", argv[1]);
        return 1;
    }
    if ((fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        fprintf(stderr, "Error opening outfile %s\n", argv[2]);
        if (close(fd_in) == -1) {
            fprintf(stderr, "Error closing infile %s\n", argv[1]);
        }
        return 2;
    }
    char buf[BUF_LEN];
    int got;
    while (got = read(fd_in, buf, sizeof(buf))) {
        if (got == -1) {
            fprintf(stderr, "Error reading infile %s\n", argv[1]);
            if (close(fd_out) == -1) {
                fprintf(stderr, "Error closing outfile %s\n", argv[2]);
            }
            if (unlink(argv[2]) == -1) {
                fprintf(stderr, "Error deleting outfile %s\n", argv[2]);
            }
            if (close(fd_in) == -1) {
                fprintf(stderr, "Error closing infile %s\n", argv[1]);
            }
            return 3;
        }
        if (write(fd_out, buf, got) == -1) {
            fprintf(stderr, "Error writing to outfile %s\n", argv[2]);
            if (close(fd_in) == -1) {
                fprintf(stderr, "Error closing infile %s\n", argv[1]);
            }
            if (unlink(argv[2]) == -1) {
                fprintf(stderr, "Error deleting outfile %s\n", argv[2]);
            }
            if (close(fd_out) == -1) {
                fprintf(stderr, "Error closing outfile %s\n", argv[2]);
            }
            return 4;
        }
    }
    if (close(fd_out) == -1) {
        fprintf(stderr, "Error closing outfile %s\n", argv[2]);
        return 5;
    }
    if (unlink(argv[1]) == -1) {
        fprintf(stderr, "Error deleting infile %s\n", argv[1]);
        return 6;
    }
    if (close(fd_in) == -1) {
        fprintf(stderr, "Error closing infile %s\n", argv[1]);
        return 7;
    }
    return 0;
}