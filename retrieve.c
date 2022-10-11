#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmemdrv.h"
#include "fs.h"
#include <fcntl.h>
#include <errno.h>

char buf[BLOCK_SIZE];
int bytes_left, fd;

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
 * A function to write blocks to either the standard output or file (depending on fd)
*/
void write_buf(){
    if (bytes_left < BLOCK_SIZE) {
        write(fd, buf, bytes_left);
    }else {
        write(fd, buf, BLOCK_SIZE);
        bytes_left -= BLOCK_SIZE;
    }
}

/**
 * A retrieving program reads stored data blocks and writes them into either the standard output or
 * a new textfile that is defined in the command-line as an argument.
 * 
 * Parameters: 
 * int argc -> The number of command line arguments
 * char *argv[] -> the array of command line arguments
 * 
 * Returns:
 * int based on success or failure of program execution
 */
int main(int argc, char *argv[]) {
    int num_blocks, size;
    Inode *inode = malloc(BLOCK_SIZE);
    char indirectBuf[BLOCK_SIZE];
    if (argc > 2){
        printf("Usage: %s <file>\n", argv[0]);
        exit(0);
    } else if(argc == 2) {
        fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0700);
        checkerror(fd, "open");
    }
    else {
        fd = 1;
    }
    open_device();
    read_block(0, (char *)inode);

    // initialise the size of the file
    size = inode->size;
    bytes_left = size;

    // calculate the number of blocks used in the file.
    num_blocks = size / BLOCK_SIZE + 1;

    // if number of blocks are more than 12 - set to 12.
    if (num_blocks > NDIRECT){
        num_blocks = NDIRECT;
    }
    // loop through and read/write direct addresses
    for (int i = 0; i < num_blocks; i++){
        read_block(inode->addrs[i], buf);
        write_buf();
    }
    // read empty indirect buffer into 13th inode address.
    read_block(inode->addrs[NDIRECT], indirectBuf);

    // loops through indirect addresses and write to indirect block
    int indirect_size = size / BLOCK_SIZE - NDIRECT;
    for (int i = 0; i <= indirect_size; i++){
        read_block(indirectBuf[i], buf);
        write_buf();
    }
    close_device();
    return EXIT_SUCCESS;
}
