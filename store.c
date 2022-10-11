#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmemdrv.h"
#include "fs.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/**
 * A function that shuffles an array of 8 bit integers on length n
 * 
 * Parameters: 
 * int8_t *array -> the array of 8 bit integers
 * int n -> length of the array
 * 
*/
void shuffle(int8_t *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int8_t t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

/**
 * A function to print out error messages
 * 
 * Parameters:
 * int val -> int value representing files presence
 * char *msg -> error message to be printed
*/
void checkerror(int val, char *msg) {
    if (val < 0) {
        perror(msg);
        exit(0);
    }
}

/**
 * A program that reads and stores a file by splitting it up across 64 bit blocks
 * An optional command line argument of '-r' can be used to randomise the order of
 * the blocks.
 * 
 * Parameters: 
 * int argc -> The number of command line arguments
 * char *argv[] -> the array of command line arguments
 * 
 * Returns:
 * int based on success or failure of program execution
 */

int main(int argc, char *argv[]) {
    Inode *inode = malloc(BLOCK_SIZE);
    char file_buf[BLOCK_SIZE], indirect_buf[BLOCK_SIZE];
    int fd, size, num_blocks;
    struct stat st;
    static int8_t free_list[MAX_BID];

    // initialising the free list
    for(int i = 0; i < MAX_BID; i++){
        free_list[i] = i;
    }

    // exiting program if there are incorrect command line arguments
    if(argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(0);
    } else {
        fd = open(argv[1], O_RDONLY);
        checkerror(fd, "open");
    }
    if(argc == 3) {
        if(strcmp(argv[2], "-r") == 0){
            shuffle(free_list+1, MAX_BID-1);
        } else{
            printf("Usage: %s <file> -r\n", argv[0]);
            exit(0);
        }
    } 

    open_device();

    // determine the size of the file
    fstat(fd, &st);
    size = st.st_size;
    inode->size = size;

    // calculate the number of blocks needs 
    num_blocks = size / BLOCK_SIZE + 1; 

    // if the file uses indirect addresses
    if(num_blocks > 13){
        num_blocks++;
    }
    // if the file is greater than 4864 bytes
    if(size > 4864){
        inode->size = 4864;
        num_blocks = 77;
        printf("truncated\n");
    }

    // reads and writes each block from the file and stores the addresses in the inode and the indirect buffer
    for(int i = 1; i <= num_blocks; i++){
        if(i != 13){
            read(fd, file_buf, BLOCK_SIZE);
            write_block(free_list[i], file_buf);
        }
        if(i < 14){
            inode->addrs[i - 1] = free_list[i];
        }else{
            indirect_buf[i - 14] = free_list[i];
        }
    }
    // write the indirect buffer into the address of the last direct adress and then write the inode
    write_block(inode->addrs[NDIRECT], indirect_buf);
    write_block(0, (char *)inode);

    printf("file stored\n");
    return EXIT_SUCCESS;
}