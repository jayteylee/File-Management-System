#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmemdrv.h"
#include "fs.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// cat /dev/zero > /dev/memdrv

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


static char fileBuf[BLOCK_SIZE], indirectBuf[BLOCK_SIZE];

int main(int argc, char *argv[]) {
    
    if(argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(0);
    }

    int fd, res;
    int size;
    struct stat st;
    Inode *inode = malloc(BLOCK_SIZE);

    open_device();
    fd = open(argv[1], O_RDONLY);
    fstat(fd, &st);
    size = st.st_size;

    inode->size = size;
    int numBlocks = size/BLOCK_SIZE + 1;

    if(numBlocks > 77){
        printf("truncated\n");
        numBlocks = 77;
    }

    for(int i = 1; i <= numBlocks; i++){
        if(i != 13){
            read(fd, fileBuf, BLOCK_SIZE);
            write_block(i, fileBuf);
        }
        if(i < 14){
            inode->addrs[i - 1] = i;
        } 
        else{
            indirectBuf[i - 14] = i;
        }
        
        
        // read_block(n, fileBuf);

    }

    write_block(0, (char *)inode);
    write_block(inode->addrs[NDIRECT], indirectBuf);

    printf("file stored\n");

    // read_block(n, buf);
    
    

    return EXIT_SUCCESS;
}