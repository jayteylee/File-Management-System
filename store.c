#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmemdrv.h"
#include "fs.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// function that shuffles the storage position of data blocks
void shuffle(int8_t *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int8_t t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

// function to check if the file exists
void checkerror(int val, char *msg) {
    if (val < 0) {
        perror(msg);
        exit(0);
    }
}

/**
 * This program should take take a command-line argument, which is the name of a file that 
 * you want to store in /dev/memdrv.
 * 
 * If the length of the file is greater than 4864 bytes it should be truncated and the word 
 * truncated printed to stderr.
 * 
 * The program should take an optional second command-line argument -r which specifies 
 * a random ordering of the blocks in the direct and indirect indexes.
*/

char file_buf[BLOCK_SIZE], indirect_buf[BLOCK_SIZE];
int fd, size, num_blocks;
struct stat st;
static int8_t free_list[MAX_BID];

int main(int argc, char *argv[]) {
    Inode *inode = malloc(BLOCK_SIZE);

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
        printf("truncated\n");
        num_blocks = 77;
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