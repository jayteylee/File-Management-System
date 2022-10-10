/* block_hexdump.c - prints contents of memdrv block(s) */
#include <stdio.h>
#include <stdlib.h>
#include "libmemdrv.h"
#include "fs.h"

static unsigned char buf[BLOCK_SIZE];

void print16Bytes(int block, unsigned offset) {
    printf("| %03X | %02d | ", block, offset);
    for (int i = 0; i < 8; i++) {
        printf("%02X ", buf[i + offset]);
    }
    printf(" ");
    for (int i = 8; i < 16; i++) {
        printf("%02X ", buf[i + offset]);
    }
    printf(" |");
    for (int i = 0; i < 16; i++) {
        char c = buf[i + offset];
        printf("%c", c < 32 ? '.' : c);
    }
    printf("|");
    printf("\n");
}

void printBlock(int block) {
    printf("|block|addr| hex dump                                          | ASCII          |\n");
    printf("+-----+----+---------------------------------------------------+----------------+\n");    
    int b = 0;
    while (b < BLOCK_SIZE) {
        print16Bytes(block, b);
        b += 16;
    }
    printf("+-----+----+---------------------------------------------------+----------------+\n");

}

int main(int argc, char *argv[]) {
   
    // if block id provided as an arg
    if (argc == 2) {
        int b = atoi(argv[1]);
        open_device();
        read_block(b, (char*)buf);
        printBlock(b);
        close_device();
    }

    // if no block id provided
    if (argc == 1) {
        open_device();
        for(int b = 0; b <= MAX_BID; b++) {
            read_block(b, (char*)buf);
            printBlock(b);
        }
        close_device();
    }
   
    return EXIT_SUCCESS;
}