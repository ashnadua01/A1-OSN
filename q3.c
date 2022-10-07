#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define buffersize 100000
#define lli long long int

int main(int argc, char *argv[])
{
    int flag = 0;

    struct stat checker;

    // checking if directory created or not
    if (stat(argv[3], &checker) == 0 && S_ISDIR(checker.st_mode))
    {
        char direc[] = "Directory is created: Yes\n";
        lli len = strlen(direc);
        write(1, direc, len);
    }
    else
    {
        flag = 1;
        char direc[] = "Directory is created: No\n";
        lli len = strlen(direc);
        write(1, direc, len);
    }

    // initialising buffer
    char buffer[buffersize];
    char buffer2[buffersize];
    char buffer3[buffersize];

    int newFile = open(argv[1], O_RDONLY);
    int oldFile = open(argv[2], O_RDONLY);

    lli num_of_bytes_per_read;
    lli check1, check2;
    int finalCheck = 0;
    int count_bytes = 0;

    lli bytes_newFile = lseek(newFile, 0, SEEK_END);
    lli bytes_oldFile = lseek(oldFile, 0, SEEK_END);

    // if size is not same, then file1 cannot be reverse of file2
    if (bytes_newFile != bytes_oldFile)
    {
        finalCheck = 1;
    }
    else
    {
        // initialising number of bytes per read, number of iterations and leftover bytes
        if (bytes_oldFile >= 100000)
        {
            num_of_bytes_per_read = 100000;
            check1 = bytes_oldFile / num_of_bytes_per_read;
            check2 = bytes_oldFile % num_of_bytes_per_read;
        }
        else
        {
            if (bytes_oldFile >= 1000)
            {
                num_of_bytes_per_read = 1000;
                check1 = bytes_oldFile / num_of_bytes_per_read;
                check2 = bytes_oldFile % num_of_bytes_per_read;
            }
            else
            {
                num_of_bytes_per_read = 1;
                check1 = bytes_oldFile / num_of_bytes_per_read;
                check2 = bytes_oldFile % num_of_bytes_per_read;
            }
        }

        // reading and writing bytes
        lseek(oldFile, -num_of_bytes_per_read, SEEK_END);
        lseek(newFile, 0, SEEK_SET);
        lli check3 = 1;
        while(check1 > 0){
            lseek(oldFile, -(check3 * num_of_bytes_per_read), SEEK_END);
            read(oldFile, buffer, num_of_bytes_per_read);
            lseek(newFile, (check3-1)*num_of_bytes_per_read, SEEK_SET);
            read(newFile, buffer2, num_of_bytes_per_read);
            lli index = num_of_bytes_per_read - 1;
            for(lli i=0; i<num_of_bytes_per_read; i++){
                buffer3[i] = buffer[index--];
            }
            for(lli i=0; i<num_of_bytes_per_read; i++){
                if(buffer2[i] != buffer3[i]){
                    finalCheck = 1;
                    break;
                }
            }
            check1--;
            check3++;
        }
        //reading and writing remaning bytes
        if(check2 != 0){
            lseek(oldFile, -((check3 - 1) * num_of_bytes_per_read) - check2, SEEK_END);
            read(oldFile, buffer, check2);
            lseek(newFile, ((check3 - 1) * num_of_bytes_per_read) + check2, SEEK_SET);
            read(newFile, buffer2, check2);
            lli index = check2 - 1;
            for(lli i=0; i<check2; i++){
                buffer3[i] = buffer[index--];
            }
            for(lli i=0; i<check2; i++){
                if(buffer2[i] != buffer3[i]){
                    finalCheck = 1;
                    break;
                }
            }
        }
    }

    // checking for file reversal
    if (finalCheck == 1)
    {
        char rev[] = "Whether file contents are reversed in newfile: No\n";
        lli len = strlen(rev);
        write(1, rev, len);
    }
    else
    {
        char rev[] = "Whether file contents are reversed in newfile: Yes\n";
        lli len = strlen(rev);
        write(1, rev, len);
    }

    if(newFile > 0){
        // checking user permissions

        // read
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IRUSR)){
            char string[] = "User has read permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has read permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // write
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IWUSR)){
            char string[] = "User has write permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has write permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IXUSR)){
            char string[] = "User has execute permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has execute permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // checking group permissions

        //read
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IRGRP)){
            char string[] = "Group has read permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has read permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // write
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IWGRP)){
            char string[] = "Group has write permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has write permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IXGRP)){
            char string[] = "Group has execute permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has execute permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //checking others permissions

        //read
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IROTH)){
            char string[] = "Others has read permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has read permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //write
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IWOTH)){
            char string[] = "Others has write permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has write permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[1], &checker) == 0 && (checker.st_mode&S_IXOTH)){
            char string[] = "Others has execute permissions on newFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has execute permissions on newFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }
    }
    else{
        char string[] = "Can't open newFile\n";
        lli len = strlen(string);
        write(1, string, len);
    }

    if(oldFile > 0){
        // checking user permissions

        // read
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IRUSR)){
            char string[] = "User has read permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has read permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // write
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IWUSR)){
            char string[] = "User has write permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has write permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IXUSR)){
            char string[] = "User has execute permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has execute permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // checking group permissions

        //read
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IRGRP)){
            char string[] = "Group has read permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has read permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // write
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IWGRP)){
            char string[] = "Group has write permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has write permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IXGRP)){
            char string[] = "Group has execute permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has execute permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //checking others permissions

        //read
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IROTH)){
            char string[] = "Others has read permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has read permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //write
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IWOTH)){
            char string[] = "Others has write permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has write permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[2], &checker) == 0 && (checker.st_mode&S_IXOTH)){
            char string[] = "Others has execute permissions on oldFile: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has execute permissions on oldFile: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }
    }
    else{
        char string[] = "Can't open oldFile\n";
        lli len = strlen(string);
        write(1, string, len);
    }

    if(flag != 1){
        // checking user permissions

        // read
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IRUSR)){
            char string[] = "User has read permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has read permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // write
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IWUSR)){
            char string[] = "User has write permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has write permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IXUSR)){
            char string[] = "User has execute permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "User has execute permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // checking group permissions

        //read
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IRGRP)){
            char string[] = "Group has read permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has read permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        // write
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IWGRP)){
            char string[] = "Group has write permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has write permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IXGRP)){
            char string[] = "Group has execute permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Group has execute permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //checking others permissions

        //read
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IROTH)){
            char string[] = "Others has read permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has read permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //write
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IWOTH)){
            char string[] = "Others has write permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has write permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }

        //execute
        if(stat(argv[3], &checker) == 0 && (checker.st_mode&S_IXOTH)){
            char string[] = "Others has execute permissions on directory: Yes\n";
            lli len = strlen(string);
            write(1, string, len);
        }
        else{
            char string[] = "Others has execute permissions on directory: No\n";
            lli len = strlen(string);
            write(1, string, len);
        }
    }
    else{
        char string[] = "Can't open directory\n";
        lli len = strlen(string);
        write(1, string, len);
    }

    return 0;
}