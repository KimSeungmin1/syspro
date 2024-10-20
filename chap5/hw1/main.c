#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 10
#define MAX_LINE_LENGTH 100

int main() {
    int fd;
    char buf;
    char savedText[MAX_LINES][MAX_LINE_LENGTH];
    int row = 0;
    int col = 0;

    if((fd = open("test.txt", O_RDONLY)) == -1){
        printf("File Open Error\n");
        close(fd);
        exit(0);
    }
	else{ 
        fd = open("test.txt", O_RDONLY);
	}
    
    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[row][col] = '\0';  
            row++;
            col = 0;
        } 
        else {
            savedText[row][col++] = buf;
        }
    }
    close(fd);

    char input[10];
    printf("You can choose (1~%d) Line\n Pls 'Enter' the line to select : ",row);
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < row; i++) {
            printf("%d: %s\n", i + 1, savedText[i]);
        }
    } 
	else {
        int num = atoi(input);		
            printf("%s\n", savedText[num - 1]);
    }
    return 0;
}
