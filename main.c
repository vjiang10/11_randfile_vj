#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// generates a random number from /dev/random
int randomInt() {
    int randNum[1];
    int randFile = open("/dev/random", O_RDONLY);
    if (randFile == -1) { 
        printf("Error when opening; errno: %s\n", strerror(errno));
        return 0;
    }
    int num = read(randFile, randNum, sizeof(randNum));
    if (num == -1) {
        printf("Error when opening; errno: %s\n", strerror(errno));
        return 0;
    }
    close(randFile);
    return randNum[0];
}

int main() {
    printf("Generating random numbers:\n");
    int randArr[10];
    int i = 0;
    while (i < 10) {
        randArr[i] = randomInt();
        printf("\trandom %d: %d\n", i, randArr[i]);
        i++;
    }
    printf("\n");

    printf("Writing numbers to file...\n");
    // opening and creating output file
    int output = open("output.out", O_WRONLY | O_CREAT, 0664);
    if (output == -1) {
        printf("Error when opening; errno: %s\n", strerror(errno));
        return 0;
    }
    int output_write = write(output, randArr, sizeof(randArr));
    if (output_write == -1) {
        printf("Error when opening; errno: %s\n", strerror(errno));
        return 0;
    }
    printf("\n");

    printf("Reading numbers from file...\n");
    int randFile2 = open("output.out", O_RDONLY);
    if (randFile2 == -1) {
        printf("Error when opening; errno: %s\n", strerror(errno));
        return 0;
    }
    int diffArr[10];
    // reading into different array
    int output_read = read(randFile2, diffArr, sizeof(diffArr));
    if (output_read == -1) {
        printf("Error when opening; errno: %s\n", strerror(errno));
        return 0;
    }
    printf("\n");

    printf("Verification that written values were the same:\n");
    i = 0;
    while (i < 10) {
        printf("\trandom %d: %d\n", i, diffArr[i]);
        i++;
    }
    
    return 0;
}