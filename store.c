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
 * This program should take take a command-line argument, which is the name of a file that 
 * you want to store in /dev/memdrv.
 * 
 * If the length of the file is greater than 4864 bytes it should be truncated and the word 
 * truncated printed to stderr.
 * 
 * The program should take an optional second command-line argument -r which specifies 
 * a random ordering of the blocks in the direct and indirect indexes.
*/


static char buf[BLOCK_SIZE];

int main(int argc, char *argv[]) {
    
    if(argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(0);
    }

    int fd, res;

    open_device();

    for()
    fd = open(argv[1], O_RDONLY);
    read(fd, buf, 128);


    write_block(1, buf);
    // read_block(n, buf);
    return EXIT_SUCCESS;
}