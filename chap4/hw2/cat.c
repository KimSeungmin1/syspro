#include <stdio.h>
#include <string.h>
#define MAXLINE 80

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2, *fp3;
    int c;
    int line = 0;
    char buffer[MAXLINE];
    int line_numbers = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        line_numbers = 1;
        argc--;
        argv++;
    }

    if (argc < 2) {
        fp1 = stdin;
    } else {
        fp1 = fopen(argv[1], "r");
    }

    if (argc < 3) {
        fp2 = NULL;
    } else {
        fp2 = fopen(argv[2], "r");
    }

    if (argc < 4) {
        fp3 = NULL;
    } else {
        fp3 = fopen(argv[3], "r");
    }

    while (fgets(buffer, MAXLINE, fp1) != NULL) {
        if (line_numbers == 1) {
            line++;
            printf("%3d %s", line, buffer);
        } else {
            printf("%s", buffer);
        }
    }

    if (fp2 != NULL) {
        while (fgets(buffer, MAXLINE, fp2) != NULL) {
            if (line_numbers == 1) {
                line++;
                printf("%3d %s", line, buffer);
            } else {
                printf("%s", buffer);
            }
        }
        fclose(fp2);
    }

    if (fp3 != NULL) {
        while (fgets(buffer, MAXLINE, fp3) != NULL) {
            if (line_numbers == 1) {
                line++;
                printf("%3d %s", line, buffer);
            } else {
                printf("%s", buffer);
            }
        }
    }

    if (fp1 != stdin) fclose(fp1);

    return 0;
}


