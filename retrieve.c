#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmemdrv.h"
#include "fs.h"
#include <fcntl.h>
#include <errno.h>

/**
 * The retrieving program should take no more than one command-line argument. If there
 * is no argument, the retrieved file should be printed to the standard output. If there is
 * an argument in the command e.g. ./retrieve-prog newfile, the retrieved file should
 * be saved to a file with the name newfile. You have to make sure not to overwrite an
 * existing file or to ask confirmation from the user to overwrite.
 * 
 * The program should not assume any sequence of the stored data blocks. They could be
 * stored anywhere randomly on the RAMDISK.
 * 
 * The retrieved file should be exactly the same as the stored file. You can use the command
 * e.g. ./store myfile.txt to store any file to the device according to the indexed
 * allocation. Then you can compare the stored file and retrieved file with diff.
*/

char buf[BLOCK_SIZE], indirectBuf[BLOCK_SIZE];

int main(int argc, char *argv[])
{
    Inode *inode = malloc(BLOCK_SIZE);
    if(argc > 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(0);
    }

    open_device();
    read_block(0, (char *)inode);

    // if(inode->size/BLOCK_SIZE + 1 < 13){
    //     NDIRECT--;
    // }

        // int bytes_left = inode->size;
        // int numBlocks = inode->size/BLOCK_SIZE + 1;
        // for(int i = 0; i < num_blocks; i++){
            
        // }
        
    // int bytes_left = inode->size;
    // for (int i = 0; i < NDIRECT; i++) {
    //     if(bytes_left < BLOCK_SIZE){
    //     read_block(inode->addrs[i], buf);
    //     write(1, buf, bytes_left);
    //     }else{
    //     read_block(indirectBuf[i], buf);
    //     write(1, buf, BLOCK_SIZE);
    //     bytes_left -= BLOCK_SIZE;
    //     }
    // }
    // read_block(inode->addrs[NDIRECT],indirectBuf);

    // int indirect_size = inode->size/BLOCK_SIZE - NDIRECT;

    // if(indirect_size > BLOCK_SIZE){
    //     indirect_size = BLOCK_SIZE;
    // }
    // for (int i = 0; i < indirect_size; i++) {
    //     if(bytes_left < BLOCK_SIZE){
    //         read_block(indirectBuf[i], buf);
    //         write(1, buf, bytes_left);
    //     }else{
    //     read_block(indirectBuf[i], buf);
    //     write(1, buf, BLOCK_SIZE);
    //     bytes_left -= BLOCK_SIZE;
    //     }
    // }
    close_device();
    return EXIT_SUCCESS;

}