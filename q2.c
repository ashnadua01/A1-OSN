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
    lli len = strlen("Assignment/") + strlen(argv[1]) + strlen("2_");
    char *str = (char *)malloc(len);
    strcat(str, "Assignment/");
    strcat(str, "2_");
    strcat(str, argv[1]);

    // creating the output file
    // 0644 is used to give read and write persmission
    lli fd2 = creat(str, 0644);
    if(fd2 < 0){
        perror("Output File");
        exit(1);
    }

    // initialising pointers for input and output file
    lli bytes = lseek(fd1, 0, SEEK_END);
    lli start = lseek(fd2, 0, SEEK_SET);
    lseek(fd1, 0, SEEK_SET);

    // converting string (argv) to long long int
    lli a = atoll(argv[2]);
    lli b = atoll(argv[3]);

    // file size is zero
    if(bytes == 0){
        printf("100%c\n", 37);
        exit(1);
    }

    // initialising count of bytes
    lli count_bytes = 0;

    // initialising for first part of file - to be reversed
    lli num_of_bytes_per_read_first_reversal;
    lli check1_first_reversal;
    lli check2_first_reversal;

    // initialising number of bytes per read, number of iterations and leftover bytes
    if(a >= 100000){
        num_of_bytes_per_read_first_reversal = 100000;
        check1_first_reversal = a / num_of_bytes_per_read_first_reversal;
        check2_first_reversal = a % num_of_bytes_per_read_first_reversal;
    }
    else{
        if(a >= 1000){
            num_of_bytes_per_read_first_reversal = 1000;
            check1_first_reversal = a / num_of_bytes_per_read_first_reversal;
            check2_first_reversal = a % num_of_bytes_per_read_first_reversal;
        }
        else{
            num_of_bytes_per_read_first_reversal = 1;
            check1_first_reversal = a / num_of_bytes_per_read_first_reversal;
            check2_first_reversal = a % num_of_bytes_per_read_first_reversal;
        }
    }

    // checking for extra bytes, less than chunk size
    if(check2_first_reversal != 0){
        // initialising pointer to read extra bytes
        lseek(fd1, a - check2_first_reversal, SEEK_SET);
        read(fd1, buffer, check2_first_reversal);
        // printf("%s\n", buffer);

        lli index = check2_first_reversal - 1;

        // reversing the string
        for(lli i=0; i<check2_first_reversal; i++){
            buffer2[i] = buffer[index--];
        }

        // printf("%s\n", buffer2);
        write(fd2, buffer2, check2_first_reversal);
        count_bytes += check2_first_reversal;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }

    // reading and writing bytes equal to chunk size
    lli check3_first_traversal = 0;
    while(count_bytes != a){
        check3_first_traversal++;
        // initialising pointer to read bytes equal to chunk size
        lseek(fd1, a - (num_of_bytes_per_read_first_reversal * check3_first_traversal) - check2_first_reversal, SEEK_SET);
        read(fd1, buffer, num_of_bytes_per_read_first_reversal);

        lli index = num_of_bytes_per_read_first_reversal - 1;

        // reversing the string
        for(lli i=0; i<num_of_bytes_per_read_first_reversal; i++){
            buffer2[i] = buffer[index--];
        }

        // printf("%s\n", buffer2);
        write(fd2, buffer2, num_of_bytes_per_read_first_reversal);
        count_bytes += num_of_bytes_per_read_first_reversal;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }
    
    // initialising for second part of file - not to be reversed
    lli num_of_bytes_per_read;
    lli check1, check2;
    lli bytes_not_to_reverse = b - a + 1;
    // printf("%lld\n", bytes_not_to_reverse);

    // initialising number of bytes per read, number of iterations and leftover bytes
    if(bytes_not_to_reverse >= 100000){
        num_of_bytes_per_read = 100000;
        check1 = bytes_not_to_reverse / num_of_bytes_per_read;
        check2 = bytes_not_to_reverse % num_of_bytes_per_read;
    }
    else{
        if(bytes_not_to_reverse >= 1000){
            num_of_bytes_per_read = 1000;
            check1 = bytes_not_to_reverse / num_of_bytes_per_read;
            check2 = bytes_not_to_reverse % num_of_bytes_per_read;
        }
        else{
            num_of_bytes_per_read = 1;
            check1 = bytes_not_to_reverse / num_of_bytes_per_read;
            check2 = bytes_not_to_reverse % num_of_bytes_per_read;
        }
    }

    // checking for extra bytes, less than chunk size
    if(check2 != 0){
        // initialising pointer to read extra bytes
        lseek(fd1, a, SEEK_SET);

        // copying file content
        read(fd1, buffer, check2);
        write(fd2, buffer, check2);
        count_bytes += check2;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }

    // reading and writing bytes equal to chunk size
    lli check3 = 0;
    while(count_bytes != b + 1){
        // initialising pointer to read bytes equal to chunk size
        lseek(fd1, a + check2 + (check3 * num_of_bytes_per_read), SEEK_SET);
        check3++;

        // copying file content
        read(fd1, buffer, num_of_bytes_per_read);
        write(fd2, buffer, num_of_bytes_per_read);
        count_bytes += num_of_bytes_per_read;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }

    // initialising for second part of file - to be reversed
    lli num_of_bytes_per_read_second_reversal;
    lli check1_second_reversal, check2_second_reversal;
    lli remaining_bytes = bytes - count_bytes;

    // initialising number of bytes per read, number of iterations and leftover bytes
    if(remaining_bytes >= 100000){
        num_of_bytes_per_read_second_reversal = 100000;
        check1_second_reversal = remaining_bytes / num_of_bytes_per_read_second_reversal;
        check2_second_reversal = remaining_bytes % num_of_bytes_per_read_second_reversal;
    }
    else{
        if(remaining_bytes >= 1000){
            num_of_bytes_per_read_second_reversal = 1000;
            check1_second_reversal = remaining_bytes / num_of_bytes_per_read_second_reversal;
            check2_second_reversal = remaining_bytes % num_of_bytes_per_read_second_reversal;
        }
        else{
            num_of_bytes_per_read_second_reversal = 1;
            check1_second_reversal = remaining_bytes / num_of_bytes_per_read_second_reversal;
            check2_second_reversal = remaining_bytes % num_of_bytes_per_read_second_reversal;
        }
    }

    // checking for extra bytes, less than chunk size
    if(check2_second_reversal != 0){
        // initialising pointer to read extra bytes
        lseek(fd1, -check2_second_reversal, SEEK_END);
        read(fd1, buffer, check2_second_reversal);

        lli index = check2_second_reversal - 1;

        // reversing the string
        for(lli i=0; i<check2_second_reversal; i++){
            buffer2[i] = buffer[index--];
        }

        write(fd2, buffer2, check2_second_reversal);
        count_bytes += check2_second_reversal;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }

    // reading and writing bytes equal to chunk size
    lli check3_second_traversal = 0;
    while(count_bytes != bytes){
        check3_second_traversal++;
        // initialising pointer to read bytes equal to chunk size
        lseek(fd1, -(check3_second_traversal * num_of_bytes_per_read_second_reversal) - check2_second_reversal, SEEK_END);
        read(fd1, buffer, num_of_bytes_per_read_second_reversal);

        lli index = num_of_bytes_per_read_second_reversal - 1;

        // reversing the string
        for(lli i=0; i<num_of_bytes_per_read_second_reversal; i++){
            buffer2[i] = buffer[index--];
        }
        write(fd2, buffer2, num_of_bytes_per_read_second_reversal);
        count_bytes += num_of_bytes_per_read_second_reversal;

        // printing percentage
        long double calc = ((long double) count_bytes / (long double) bytes) * 100;
        sprintf(perc, "\r%Lf%c", calc, 37);
        write(1, perc, strlen(perc));
    }

    printf("\n");

    // closing the files
    close(fd1);
    close(fd2);
    return 0;
}