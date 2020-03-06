## Maze solver 

Author: Nguyen Huynh Dang Khoa - Victor Nguyen  
Major: Embedded System  
University: Danang University of Sciences and Technology (DUT)  
Nation: Vietnam

##  ABOUT
Here is the project I learned from Computerphile, Mike Pound, here is his github [Mike Pound](https://github.com/mikepound/)

I created this project to learn Python3 and dijkstra algorithm, however I tried to approach
in different way:  
- I load the image and create nodes from the maze similar to Mike.  
  Then I load all the connections of nodes into a cache "maze_origin.txt"
  Mike's version only read the maze with entrance on the top, I try to read on both Left, Top, Right borders
- My dijkstra.c writen in C language by myself, will read the cache and try to solve  
the maze, then it write the solution in a cache "maze_solution.txt"  
- The mazeSaver.py will read the "maze_solution.txt" to write the solution in the image  
- I recently add a python code to randomly change your entrance in the maze
To do this, we can control how much memory exactly needed to solve a Dijkstra problems,   instead  
of using Python with Priority_queue and Fibonacy Heap as Mike. This is the most advantage  
of C programming, which is very powerful when we try to program in Embedded System.   

## NOTE
This project is not very optimized, because I don't have much time to develop this. Hope you  
can optimize for me the dijkstra.c so that it can run more sufficiently.  

## HOW THIS WORK ?

- ./maze_solver.sh [input_file]  
  
_example: ./maze_solver.sh resource/normal.png  
          ./maze_solver.sh resource/combo400/png  
          
- ./maze_solver.sh --clear  
- ./maze_solver.sh --clearall  
- python3 prog/mazeConfig.py [input_file] [output_file] y x color  
_example: python3 prog/mazeConfig.py resource/tiny.png resource/tiny_left_mod.png rand left white  
          -> This will clear the old entrance and create randomly new entrance in the left border.  
          python3 prog/mazeConfig.py resource/tiny.png resource/tiny_mod.png 1 0 white  
          -> By this you can change any pixel(x, y) in the maze by "color", I just code for "white" and "black"  
          you can develop it further   
# Hope you like it. Good luck  
