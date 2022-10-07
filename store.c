#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmemdrv.h"
#include "fs.h"

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
int main(int argc, char *argv[]) {

}