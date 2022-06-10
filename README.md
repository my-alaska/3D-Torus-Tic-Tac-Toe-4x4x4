# 3D-Torus-Tic-Tac-Toe-4x4x4
AGH university of science and technology Kraków - Poland - June 2022.
A project for my C++ course at the 2nd year of computer science studies.
The project is a 3 dimensional 4x4x4 tic tac toe game on 3 dimensional torus written in C++ language.
To implement GUI I used SDL library with SDL_image and SDL_ttg.

There are 2 players in the game - red and blue.
Red player starts and they take turns by placing a tile of their own color on one of unoccupied spaces on the game map.
When one player places 4 tiles of his colour in a row they win and winning tiles change colour to green.
clicking the map after victory or pressing space at any moment resets the game to the starting point.

The difficulty of the game lies in it's use of torus surface generalised to 3d space.
The most intuitive way of understanding torus is by referencing a classic game Pacman.
When Pacman leaves the map on one of the sides, he enters it back from the opposite side. 
Just as if he lived on a surface of a doughnut.
This can be easily generalised to 3 dimensions.
For anyone interested in the topic I recommend Michael Stevens' video that explains the torus mechanics further.
https://youtu.be/mbJVYN0w6rg

The project was written entirely using Clion ide on windows 10 operating system.
I also included CMakeList.txt file with needed SDL configurations.
The font used in the project can be found at https://www.1001fonts.com/pixel-font.html 
It is marked as "Free for commercial use".
Implemented game_map can be used to create bigger maps for similar games.
Images used in the game as tiles were drawn by me.
