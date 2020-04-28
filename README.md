# Focus

The Project

This project is a relatively simplified implementation of the board game Focus/Domination using linked lists to manage 
the stacks. I used the code given to us in the slides as a guide and I updated certain aspects such as the format in which
the board was printed. I made that a bit bigger so that one would be able to see the pieces move each time.
This project was split into 3 source and  2 header files;

	The main.c: That had the function in a while loop to continue to play the game until a winner is found and the 
game was ended. Then it would print out the ending statement wen the game was over showing who won how many pieces 
they had left in their reserve and how many they captured in the process of the game

	The game.c: This file had the game logic and functionalities that helped to play the game smoothly such as like 
the initial board formation the function to print the board after every move. instructions on how to move the pieces, 
how to capture pieces the way the pieces would be stacked that included the max number of steps to take making sure 
each player moves their own piece. 

	The stack.c: This file had the implementation of my stacks and linked lists to carry out the functionality and logic
behind the moving of each piece into a stack and moving a stack to another stack

