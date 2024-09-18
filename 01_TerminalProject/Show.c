#include <ncurses.h>
#include <sys/stat.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define DX 3

int main(int argc, char **argv) {
	WINDOW *win;
	int sz, i, n, m, c = 0, fd, W, H, done;
	char *buf, *curr;
	char **strings;
	size_t len;
	struct stat info;
	
	stat(argv[1], &info);
	len = info.st_size;
	buf = malloc(len+2) + 1;
	buf[-1] = '\n';
	fd = open(argv[1], O_RDONLY);
	read(fd, buf, len);
	if (buf[len-1] != '\n') {
		buf[len] = '\n';
	}
	for (sz = 0, curr = buf; curr && curr < buf + len - 1; curr = strchr(curr, '\n') + 1) {
		sz++;
	}
	strings = calloc(sz+1, sizeof(char*));
	for (i = 0, curr = buf; curr && curr < buf + len; curr = strchr(curr, '\0') + 1) {
		strchr(curr, '\n')[0] = '\0';
		strings[i++] = curr;
	}

	setlocale(LC_ALL, "");

	initscr();
	noecho();
	cbreak();
	mvprintw(0, 0, "File: %s; size: %d", argv[1], sz);
	refresh();

	W = COLS  - 2 * DX;
	H = LINES - 2 * DX;
	win = newwin(H, W, DX, DX);
	keypad(win, TRUE);
	scrollok(win, TRUE);
	n = 0, m = 0;
	done = FALSE;
	while (!done) {
		werase(win);
		for (i = 0; i < H - 2 && i + n < sz; i++) {
			mvwprintw(win, i+1, 1, "%4d: %.60s\n", i + n, m < strlen(strings[i+n]) ? &(strings[i+n][m]) : ""); //
		}
		box(win, 0, 0);
		wrefresh(win);
		switch(c = wgetch(win)) {
			case 'q':
			case 27: done = TRUE; break;
			case 32:
			case KEY_NPAGE: n = n < sz - H + 1 ? n + H - 2 : sz - 1; break;
			case KEY_PPAGE: n = n > H - 1 ? n - H + 2 : 0; break;
			case KEY_DOWN: n = n < sz - 1 ? n + 1 : n; break;
			case KEY_UP: n = n > 0 ? n - 1 : n; break;
			case KEY_RIGHT: m++; break;
			case KEY_LEFT: m = m > 0 ? m - 1: 0; break;
		}
	}
	endwin();
	return 0;
}
