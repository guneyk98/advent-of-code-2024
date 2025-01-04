#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define MAX_LEVELS_PER_LINE 32

bool IsReportSafe(size_t n, int reportLevels[static n]);

int main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		fprintf(stderr, "Failed to open input.txt\n");
		return EXIT_FAILURE;
	}
	
	int numSafeReports = 0;
	char lineStr[MAX_LINE_LEN];
	int reportLevels[MAX_LEVELS_PER_LINE];
	int reportLevelsNew[MAX_LEVELS_PER_LINE-1];


	while (fgets(lineStr, sizeof(lineStr), fp)) {
		if (ferror(fp)) {
			fprintf(stderr, "Failed to read line\n");
			return EXIT_FAILURE;
		}
		
		int temp, offset;
		char *p = lineStr;
		size_t numLevels = 0;

		while (sscanf(p, "%d%n ", &temp, &offset) == 1) {
			if (numLevels >= MAX_LEVELS_PER_LINE) {
				fprintf(stderr, "Max readable levels per line reached\n");
				return EXIT_FAILURE;
			}
			reportLevels[numLevels] = temp;
			++numLevels;
			p += offset;
		}
		
		if (numLevels <= 1)
			continue;
		
		if (IsReportSafe(numLevels, reportLevels)) {
			++numSafeReports;
			continue;
		}

		if (numLevels <= 2)
			continue;
		
		printf("Failed report: %s", lineStr);

		for (size_t i = 0; i < numLevels; ++i) {
			memcpy(reportLevelsNew, reportLevels, i * sizeof(reportLevels[0]));
			memcpy(reportLevelsNew+i, reportLevels+i+1, (numLevels-i-1) * sizeof(reportLevels[0]));
			
			printf("Without %zu:", i);
			for (size_t j = 0; j < numLevels-1; ++j)
				printf(" %d", reportLevelsNew[j]);
			printf("\n");


			if (IsReportSafe(numLevels-1, reportLevelsNew)) {
				++numSafeReports;
				break;
			}
		}
	}

	printf("Number of safe reports: %d\n", numSafeReports);

	fclose(fp);
}

bool IsReportSafe(size_t n, int reportLevels[static n])
{
	bool increasing = false;
	bool decreasing = false;

	for (size_t i = 1; i < n; ++i) {
		int delta = reportLevels[i] - reportLevels[i-1];

		if (delta > 0)
			increasing = true;
		else if (delta < 0)
			decreasing = true;
		else
			return false;

		if ((increasing && decreasing) || abs(delta) > 3)
			return false;
	}
	return true;
}