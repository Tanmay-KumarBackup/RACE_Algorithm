# RACE Algorithm
In this repository i am trying to create a prototype of race algorithm in c++ code 
<hr>
RACE algorithm is a page replacement algorithm which helps for segmentation of the cache memory into three <br>
different section and which will also change their sizes Dynamically.<br>
You have to input total number of blocks, block value, inode, current time and Program Counter<br>
RACE algorithm will dynamically saperate the for different type of references and will allocate the space dynamically for each block<br>
there will be two tables File table and PC table will decide that how the partition is to be maintained.<br>
Dynamically the partition will change and will be displayed respectively.
<br><br>
<hr>
right now there are few errors in the code such as:
<br>i am inable to understand what is "ghost" reference time in line number 5 of pseudo code<br>
what to update in the last reference time of the 1st block in line number 9 of pseudo code<br>
how to check whether the access direction is reversed<br>
how to extend existing sequence in line number 13<br>
what is threshold which is used in line 21<br>
<hr>
things other then that are all good and i guess that after solving these problem the code will be in working condition.<br>
Thank You
