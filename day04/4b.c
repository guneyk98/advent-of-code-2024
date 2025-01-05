#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIMENSIONS 4096

int CountLines(FILE *fp);
int CountLineWidth(FILE *fp);


int main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		fprintf(stderr, "Failed to open input.txt\n");
		return EXIT_FAILURE;
	}
	
	const int numCols = CountLineWidth(fp);
	const int numRows = CountLines(fp);
	
	if (numCols > MAX_DIMENSIONS || numRows > MAX_DIMENSIONS) {
		fprintf(stderr, "Input word search is too large\n");
		return EXIT_FAILURE;
	}

	int *letters = malloc(sizeof(int) * numCols * numRows);
	if (letters == NULL) {
		fprintf(stderr, "Failed to allocate memory\n");
		return EXIT_FAILURE;
	}
	
	int ch;
	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			if ((ch = fgetc(fp)) == '\n')
				ch = fgetc(fp);
			letters[row*numCols + col] = ch;
		}
	}

	size_t occurrences = 0;

	// the 'A' cannot be on the edge of the grid for a valid X-MAS
	for (int row = 1; row < numRows-1; ++row) {
		for (int col = 1; col < numCols-1; ++col) {
			if (letters[row*numCols + col] != 'A')
				continue;
			
			int topLeft     = letters[(row - 1) * numCols + (col - 1)];
			int topRight    = letters[(row - 1) * numCols + (col + 1)];
			int bottomLeft  = letters[(row + 1) * numCols + (col - 1)];
			int bottomRight = letters[(row + 1) * numCols + (col + 1)];
			
			bool diag1 = (topLeft == 'M' && bottomRight == 'S') || (topLeft == 'S' && bottomRight == 'M');
			bool diag2 = (topRight == 'M' && bottomLeft == 'S') || (topRight == 'S' && bottomLeft == 'M');

			if (diag1 && diag2)
				++occurrences;
		}
	}
	
	printf("'X-MAS' occurs a total of %zu times\n", occurrences);

	free(letters);
	fclose(fp);
}

int CountLines(FILE *fp)
{
	char buffer[65536];
	int count = 0;

	while (!feof(fp)) {
		size_t n = fread(buffer, 1, sizeof(buffer), fp);
		if (ferror(fp)) {
			fprintf(stderr, "Error while reading file\n");
			exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < n; ++i)
			if (buffer[i] == '\n')
				++count;
	}
	fseek(fp, 0L, SEEK_SET);
	return count;
}

int CountLineWidth(FILE *fp)
{
	int count = 0;
	int ch;
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n')
			break;
		++count;
	}
	if (ferror(fp)) {
		fprintf(stderr, "Read error\n");
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0L, SEEK_SET);
	return count;
}
