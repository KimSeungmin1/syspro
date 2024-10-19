#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	int c;
	if (argc < 2)
		fp1 = stdin;
	else fp1 = fopen(argv[1],"r");

	if(fp1 == NULL) {
		return 1;
	}

	fp2 = fopen(argv[2], "a");
	if (fp2 == NULL){
		fclose(fp1);
		return 1;
		}
	
	while((c = getc(fp1)) != EOF) {
		putc(c, fp2);
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}
