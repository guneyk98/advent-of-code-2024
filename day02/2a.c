#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 256

int main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		fprintf(stderr, "Failed to open input.txt\n");
		return EXIT_FAILURE;
	}
	
	int numSafeReports = 0;
	char lineStr[MAX_LINE_LEN];
	while (fgets(lineStr, sizeof(lineStr), fp)) {
		if (ferror(fp)) {
			fprintf(stderr, "Failed to read line\n");
			return EXIT_FAILURE;
		}
		
		bool safe = true;
		bool increasing = false;
		bool decreasing = false;
		
		int nCurr, nPrev, offset;
		char *p = lineStr;

		if (sscanf(p, "%d%n ", &nPrev, &offset) != 1)
			continue;

		p += offset;

		while (sscanf(p, "%d%n ", &nCurr, &offset) == 1) {
			if (nCurr > nPrev)
				increasing = true;
			else if (nCurr < nPrev)
				decreasing = true;
			else {
				safe = false;
				break;
			}

			if ((increasing && decreasing) || abs(nCurr - nPrev) > 3) {
				safe = false;
				break;
			}

			nPrev = nCurr;
			p += offset;
		}
		if (safe)
			++numSafeReports;
	}

	printf("Number of safe reports: %d\n", numSafeReports);

	fclose(fp);
}
