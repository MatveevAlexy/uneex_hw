#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage:\n%s N - range(N)\n", argv[0]);
		printf("%s N M - range(N, M)\n", argv[0]);
		printf("%s N M S - range(N, M, S)\n", argv[0]);
	} else if (argc == 2) {
		int N = strtol(argv[1], NULL, 10), S = 1;
		if (N < 0) {
			S = -1;
		}
		for (int i = 0; i != N; i+=S) {
			printf("%d ", i);
		}
		printf("\n");
	} else if (argc == 3) {
		int N = strtol(argv[2], NULL, 10), M = strtol(argv[1], NULL, 10), S = 1;
		if (M > N) {
			S = -1;
		}
		for (int i = M; i != N; i+=S) {
			printf("%d ", i);
		}
		printf("\n");
	} else if (argc >= 4) {
		int N = strtol(argv[2], NULL, 10), M = strtol(argv[1], NULL, 10), S = strtol(argv[3], NULL, 10);
		if (M > N) {
			if (S >= 0) {
				printf("Bad input\n");
			} else {
				for (int i = M; i > N; i+=S) {
					printf("%d ", i);
				}
				printf("\n");
			}
		} else {
			if (S <= 0) {
				printf("Bad input\n");
			} else {
				for (int i = M; i < N; i+=S) {
					printf("%d ", i);
				}
				printf("\n");
			}
		}
	}
	return 0;
}
