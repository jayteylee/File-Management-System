#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmemdrv.h"
#include "fs.h"

/**
 * The retrieving program should take no more than one command-line argument. If there
 * is no argument, the retrieved 􏰂le should be printed to the standard output. If there is
 * an argument in the command e.g. ./retrieve-prog newfile, the retrieved file should
 * be saved to a file with the name newfile. You have to make sure not to overwrite an
 * existing file or to ask con􏰂rmation from the user to overwrite.
 * 
 * The program should not assume any sequence of the stored data blocks. They could be
 * stored anywhere randomly on the RAMDISK.
 * 
 * The retrieved file should be exactly the same as the stored file. You can use the command
 * e.g. ./store-prog myfile.txt to store any file to the device according to the indexed
 * allocation. Then you can compare the stored file and retrieved file with diff.
*/

int main()
{

}