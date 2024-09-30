#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "copy.h"

#define MAX_STR_LEN 128
#define LEN 5

int compare(const void* s1, const void* s2) {
	return strlen((char*)s2) - strlen((char*)s1);
}

int main() {
	char words[LEN][MAX_STR_LEN];
    int a = 0;
    while (a < 5) {
    scanf("%s", words[a]);
    a++;
}
	printf("Before sorting...\n");
	for (int i = 0; i < LEN; i++) {
		printf("%s\n", words[i]);
	}
	printf("\n");

	qsort(words, LEN, MAX_STR_LEN, compare);

	for (int i = 0; i < LEN; i++) {
		printf("%s\n", words[i]);
	}
}
