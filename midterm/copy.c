#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char c;
	int copy_num = 0;
	FILE *fp1, *fp2;

	if(argc > 1 && *argv[1] == '0') {
		copy_num = 1;
		argc--;
		argv++;
	}
	
	if(argc > 1 && *argv[1] == '1') {
		copy_num = 2;
		argc--;
		argv++;
	}

	if(argc > 1 && *argv[1] == '2') {
		copy_num = 3;
		argc--;
		argv++;
	}

	if(argc != 3) {
		fprintf(stderr, "How to use: %s File 1 File2\n", argv[0]);
		return 1;
	}
	
	fp1 = fopen(argv[1], "r");
	if (fp1 == NULL) {
		fprintf(stderr, "File %s Opne Error\n", argv[1]);
		return 2;
	}
	if (copy_num == 1){
	fp2 = fopen(argv[2], "w");
	while((c = fgetc(fp1)) != EOF)
		fputc(c, fp2);
	}

	if (copy_num == 2){
		fp2 = fopen(argv[2], "w");
		while((c = fgetc(fp1)) != EOF)
			fputc(tolower(c), fp2);
	}

	if (copy_num == 3){
		fp2 = fopen(argv[2], "w");
		while((c = fgetc(fp1)) != EOF)
			fputc(toupper(c), fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

