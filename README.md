# Development Log 

Starting off the assignment our first thought is to try to understand what's happening in the debug.c file which turns out just outputs the inode and everything in the block.

A function to fill up the memdrv with 0 then press "ctrl c" to "clear" the memdrv: `cat /dev/zero > /dev/memdrv`