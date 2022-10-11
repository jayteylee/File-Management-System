# COSC204 Assignment 2

## Introduction
Firstly, we would like to acknowledge how enjoyable this project was to work on in a pair.For the majority of the project we worked with peer programming and found it very effective in giving both of us a deeper understanding of the entire program.

The workload was evenly distrubuted with both of us spending many hours together in the lab to work on it.

---

## Development Log

### *Day 1*
Starting off the assignment our first thought is to try to understand what's happening in the debug.c file which turns out it just outputs the inode and everything in the block.

We were given a function to reset the memdrv: `cat /dev/zero > /dev/memdrv`

Next, we tested the provided sample-store and sample-retrieve methods to see the expected functionality. 

Then we used the test_device method from Lab 18 as a basis for the implementation of our store method. From here we declared our block sizes to see how it changed the results.

In our store, we used the built in open and read functions to be able to read a txt file. From here we were able to use the write_block function to store the first 64 bytes of the txt file in block 1. Now we are trying to figure out how to read the rest of the txt file into the other blocks. The initial issue we are facing is that we are unsure how to read in the file from the correct location beyond the first block.

We have now figured out that the read function by default continues to read the file from where it left off.

We have now successfuly read the file into all the blocks in sequential order, from here we started development on block 0 (the inode struct), changing it's size parameter and direct addresses.
- Ran through many tests of the edge cases for the .txt files that we were storing. This uncovered some issues with out implementation that we were able to fix.

### *Day 2*
Started off by implementing the free_list into our sort program instead of using hard coded sequential values which then allows us to program the option "-r" command line function in which the blocks are stored in a random order.
- We then proceeded to complete both the random order and sequential implementations of the sort with the free_list
- Once this was complete, Hongyu spent a solid amount of time refactoring our code for the store program to make it more efficient, logical and easier to understand.
- During this, Jay began the implementation of the retrieve program.

Once Hongyu had completed the store, he jumped back into peer programming with Jay to complete the retrieve function.
- Some hurdles we faced during the switching between peer programming and solo work was working with Git. We had a bit of trouble with merging our files but we were able to overcome this with some help from the demonstrators.

For the implementation of the retrieve function, our thought process was to initially loop through all of the direct addresses (then write them to the standard output) and then repeat the process with the indirect addresses. Once we got started, we quickly realised that the last block was repeating some of the stored text. We figured out that this would be because the left over number of bytes would not be equal to the size of the blocks storing the data so we reimplemented to program to then keep track of the total file size in bytes and the number of bytes left after each block was retrieved.

Once this was complete, we saw that we have some duplicate code so we abstracted this into a separate write_buf function that tidied up our code and reduced any redundancy.

---

