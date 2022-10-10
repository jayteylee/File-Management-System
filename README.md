# Development Log 

Starting off the assignment our first thought is to try to understand what's happening in the debug.c file which turns out just outputs the inode and everything in the block.

A function to fill up the memdrv with 0 then press "ctrl c" to "clear" the memdrv: `cat /dev/zero > /dev/memdrv`

We tested the provided sample-store and sample-retrieve methods to see the expected functionality. 

Then we used the test_device method from Lab 18 as a basis for the implementation of our store method. From here we declared our block sizes to see how it changed the results.

In our store, we used the built in open and read functions to be able to read a txt file. From here we were able to use the write_block function to store the first 64 bytes of the txt file in block 1.