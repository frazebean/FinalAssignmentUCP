# What is this?

This is a video game that runs on the linux terminal. It is written in C.

The game is a car game. The map of the game is based on a text file. This is for an assignment.

To run the code, type this in a linux terminal (Steps are shown below):

1. make

'make' will compile all the necessary files to allow the program to be run.

2. ./traffic *your file*

In the case of the given 3 sample files, the file name can be:

- game_1.txt
- game_2.txt
- game_3.txt

PLEASE NOTE: This is a program for an assessment. As such, the game does have limitations in
regards to what text file works with it.

The limitations are:

- Path must be a [circuit](https://en.wikipedia.org/wiki/Race_track)
- There can only be one car character and it **MUST** initially be in the path
- There can only be one player character and it **MUST** initially be on an empty space

# The text file format

The text file's first line has two integers separated by a space. The first integer denotes
the number of rows in the map, while the second integer denotes the number of columns.

For example:

`10` `15` creates a map with 10 rows and 15 columns.

The rest of the text file (line 2 onwards):

- *1* represents the path/road in the game
- *2* represents the car character
- *3* represents the player character
- *4* represents the goal
