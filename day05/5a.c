#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 512
#define MAX_NUM_PAGES 100

static bool rules[MAX_NUM_PAGES][MAX_NUM_PAGES];

int ComparePages(const void *p, const void *q);

int main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		fprintf(stderr, "Failed to open input.txt\n");
		return EXIT_FAILURE;
	}
	
	int result = 0;
	char lineBuf[MAX_LINE_LEN];
	
	while (fgets(lineBuf, sizeof(lineBuf), fp) != NULL) {
		if (lineBuf[0] == '\n')
			continue;
		
		char *end;
		int num1 = (int)strtol(lineBuf, &end, 10);
		if (end == lineBuf)
			break;

		if (*end == '|') {
			int num2 = (int)strtol(end+1, &end, 10);
			if (end == lineBuf)
				break;

			rules[num1][num2] = true;
		} else if (*end == ',') {
			static int updatePages[MAX_NUM_PAGES];
			updatePages[0] = num1;
			size_t updateSize = 1;

			while (*end != '\n' && *end != EOF) {
				num1 = (int)strtol(end+1, &end, 10);
				if (end == lineBuf)
					break;
				updatePages[updateSize] = num1;
				++updateSize;
			}
			
			bool correctOrder = true;
			for (size_t j = updateSize-1; j >= 1; --j) {
				for (size_t i = 0; i < j; ++i) {
					if (rules[updatePages[j]][updatePages[i]]) {
						correctOrder = false;
						break;
					}
				}
			}
			
			if (correctOrder)
				result += updatePages[updateSize/2];
		}
	}
	
	if (ferror(fp)) {
		fprintf(stderr, "Failed to read line");
		return EXIT_FAILURE;
	}
	
	printf("Result: %d\n", result);
	fclose(fp);
}
