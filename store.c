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

void shuffle(int8_t *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int8_t t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

static int8_t free_list[MAX_BID];
static char fileBuf[BLOCK_SIZE], indirectBuf[BLOCK_SIZE];
int fd, size, numBlocks;
struct stat st;
Inode *inode = malloc(BLOCK_SIZE);

int main(int argc, char *argv[]) {
    //initialising the free list
    for(int i = 0; i < MAX_BID; i++){
        free_list[i] = i;
    }
    //Exiting program if there are incorrect command line arguments
    if(argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(0);
    }else if(argc == 3){
        if(strcmp(argv[2], "-r") == 0){
        shuffle(free_list+1, MAX_BID-1);
        }else{
            printf("Usage: %s <file> -r\n", argv[0]);
            exit(0);
        }
    }

    open_device();
    fd = open(argv[1], O_RDONLY);
    fstat(fd, &st);
    size = st.st_size;
    inode->size = size;
    numBlocks = size/BLOCK_SIZE + 1;

    //Prints truncated if number of blocks exceeds 76
    if(numBlocks > 76){
        printf("truncated\n");
        numBlocks = 76;
    }

    //reads in the file and stores across the blocks
    for(int i = 1; i <= numBlocks + 1; i++){
        if(i != 13){
            read(fd, fileBuf, BLOCK_SIZE);
            write_block(free_list[i], fileBuf);
        }
        if(i < 14){
            inode->addrs[i - 1] = free_list[i];
        } 
        else{
            indirectBuf[i - 14] = free_list[i];
        }
    }
    write_block(0, (char *)inode);
    write_block(inode->addrs[NDIRECT], indirectBuf);
    printf("file stored\n");
    return EXIT_SUCCESS;
}