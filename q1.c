#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define buffersize 100000
#define lli long long int

int main(int argc, char *argv[]){
    // initialising buffer for reading and buffer2 for writing
    char buffer[buffersize];
    char buffer2[buffersize];
    char perc[20];

    // opening the input file in read only mode
    lli fd1 = open(argv[1], O_RDONLY);
    if(fd1 < 0){
        perror("Input File");
        exit(1);
    }

    // Making directory with read, write and execute permission
    lli dir = mkdir("Assignment", 0700);

    // Concatenating strings for a customised output name of the file
    lli len = strlen("Assignment/") + strlen(argv[1]) + strlen("1_");
    char *str = (char *)malloc(len);
    strcat(str, "Assignment/");
    strcat(str, "1_");
    strcat(str, argv[1]);

    // creating the output file
    // 0644 is used to give read and write persmission
    lli fd2 = creat(str, 0644);
    if(fd2 < 0){
        perror("Output File");
        exit(1);
    }

    // checking the size of the file
    lli bytes = lseek(fd1, 0, SEEK_END);

    // file size is zero
    if(bytes == 0){
        printf("100%c\n", 37);
        exit(1);
    }

    // positioning pollier to beginnign of output file
    lli start = lseek(fd2, 0, SEEK_SET);

    // defining chunk size according to the size of the file
    lli num_of_bytes_per_read;
    lli check1, check2;
    lli count_bytes = 0;

    // initialising number of bytes per read, number of iterations and leftover bytes
    if(bytes < 100000){
        if(bytes >= 1000){
            num_of_bytes_per_read = 1000;
            check1 = bytes / num_of_bytes_per_read;
            check2 = bytes % num_of_bytes_per_read;
        }
        else{
            num_of_bytes_per_read = 1;
            check1 = bytes / num_of_bytes_per_read;
            check2 = bytes % num_of_bytes_per_read;
        }
    }
    else{
        num_of_bytes_per_read = 100000;
        check1 = bytes / num_of_bytes_per_read;
        check2 = bytes % num_of_bytes_per_read;
    }

    // in case of extra bits at the end
    // reading and writing them first
    if(check2 != 0){
        lseek(fd1, -check2, SEEK_END);
        read(fd1, buffer, check2);
        // printf("%s\n", buffer);

        lli index = check2 - 1;
        
        for(lli i=0; i<check2; i++){
            buffer2[i] = buffer[index--];
        }

        // printf("%s\n", buffer2);
        write(fd2, buffer2, check2);
        count_bytes += check2;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }

    // reading and writing the remaining bits
    lli check3 = 0;
    while(count_bytes != bytes){
        check3++;
        lseek(fd1, -(check3 * num_of_bytes_per_read) - check2, SEEK_END);
        read(fd1, buffer, num_of_bytes_per_read);
        // printf("%s\n", buffer);

        lli index = num_of_bytes_per_read - 1;

        // reversing string
        for(lli i=0; i<num_of_bytes_per_read; i++){
            buffer2[i] = buffer[index--];
        }

        // printf("%s\n", buffer2);
        write(fd2, buffer2, num_of_bytes_per_read);
        count_bytes += num_of_bytes_per_read;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }
    // printf("%s\n", perc);
    printf("\n");

    // closing the files
    close(fd1);
    close(fd2);
    return 0;
}