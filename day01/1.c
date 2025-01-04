#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 124

size_t CountLines(FILE *fp);
int CompareInts(const void *p, const void *q);

int main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		fprintf(stderr, "Failed to open input.txt\n");
		return EXIT_FAILURE;
	}
	
	const size_t numLines = CountLines(fp);

	int *L = malloc(sizeof(int) * numLines); 
	int *R = malloc(sizeof(int) * numLines);
	if (!R || !L) {
		fprintf(stderr, "Failed to allocate memory\n");
		return EXIT_FAILURE;
	}
	
	char lineStr[MAX_LINE_LEN];
	for (size_t i = 0; i < numLines; ++i) {
		if (!fgets(lineStr, sizeof(lineStr), fp)) {
			fprintf(stderr, "Failed to read line %zu\n", i);
			return EXIT_FAILURE;
		}
		if (sscanf(lineStr, "%d %d", L+i, R+i) != 2) {
			fprintf(stderr, "Failed to parse string for line %zu\n", i);
			return EXIT_FAILURE;
		}
	}

	qsort(L, numLines, sizeof(int), CompareInts);
	qsort(R, numLines, sizeof(int), CompareInts); 
	
	int totalDistance = 0;
	for (size_t i = 0; i < numLines; ++i)
		totalDistance += abs(L[i] - R[i]);

	printf("Total distance: %d\n", totalDistance);

	// part 2
	int similarity = 0;
	for (size_t i = 0, j = 0; i < numLines; ++i) {
		while (j < numLines && L[i] > R[j])
			++j;
		while (j < numLines && L[i] == R[j]) {
			similarity += L[i];
			++j;
		}
	}

	printf("Similarity: %d\n", similarity);

	free(L); free(R);
	fclose(fp);
}

size_t CountLines(FILE *fp) {
	char buffer[65536];
	size_t count = 0;

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

int CompareInts(const void *p, const void *q)
{
    return (*(int *)p > *(int *)q) - (*(int *)p < *(int *)q);
}
