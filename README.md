# ascii-maze




This simple terminal-based maze game generates random mazes with a single entry and exit point. The player controls a red square that moves through the maze using the arrow keys. The goal is to navigate from the entry point to the exit point. When the player reaches the exit, a new maze is generated, and the player starts again at the new entry point.

Instructions:

Compile the C code using GCC with the following command: gcc maze.c -o maze
Run the compiled program with ./maze
Use the arrow keys to navigate the red square through the maze.
When you reach the exit, a new maze will be generated, and the player starts at the new entry point.
Press 'CTRL + C' to exit the game.

Code Explanation:

The code defines the maze's width and height as constants.
The CarveMaze function carves out paths within the maze.
The GenerateMaze function creates a random maze layout using the CarveMaze function.
The ShowMaze function prints the current maze state, including the player's red square, in the terminal.
The MoveSquare function processes user input to move the red square within the maze.
The getch function reads a single character input without echoing it to the screen.
The main function orchestrates the maze generation, user input handling, and maze display. It also checks for the player's position at the exit and generates a new maze if needed.


Dependencies:

This code requires the C standard library.
The code has been tested on Unix-like systems (macOS, Linux) and may not work as expected on other platforms.

Note:

The game might experience some occasional jittering due to the terminal's rendering limitations.
