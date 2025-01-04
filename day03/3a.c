#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 3

int main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		fprintf(stderr, "Failed to open input.txt\n");
		return EXIT_FAILURE;
	}
	
	int result = 0;
	int ch, n1, n2;

	while ((ch = getc(fp)) != EOF) {
		if (ch != 'm')
			continue;

		if ((ch = getc(fp)) == 'u' && (ch = getc(fp)) == 'l' && (ch = getc(fp)) == '(') {
			if (fscanf(fp, "%3d", &n1) != 1)
				break;

			if ((ch = getc(fp)) != ',') {
				if (ch == EOF)
					break;
				continue;
			}

			if (fscanf(fp, "%3d", &n2) != 1)
				break;

			if ((ch = getc(fp)) != ')') {
				if (ch == EOF)
					break;
				continue;
			}
			result += n1*n2;

		} else if (ch == EOF)
			break;
	}
	
	if (ferror(fp)) {
		fprintf(stderr, "Read error\n");
		return EXIT_FAILURE;
	}

	printf("Result: %d\n", result);
	fclose(fp);
}
