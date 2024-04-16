# Cub3D

This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable us to explore ray-casting. Our goal will be to create a dynamic view inside a maze, where players will navigate to find their way out.

![Peek 2024-03-20 22-18](https://github.com/LuisBalsa/Cub3d/assets/81270660/5ca81258-e10a-4aa4-b3bb-258862b09789)

## Introduction

Cub3D is a project that delves into the fascinating world of ray-casting, a technique pivotal in the development of early first-person shooter (FPS) games. Through this project, we aim to understand the fundamentals of ray-casting and implement them to construct a maze-like environment with interactive exploration.


## Ray-Casting Technique

Ray-casting involves simulating the behavior of rays projected from a player's perspective to render a 3D environment on a 2D screen. In our implementation, we utilize a camera vector to achieve this effect. To achieve this, we need the player's direction vector (blue in the image below) and the camera vector (pink vector in the image below). This camera vector is essentially a perpendicular vector pointing to the right relative to the direction vector (it must be to the right to prevent the image from appearing inverted on our screen).

![Screenshot from 2024-04-16 16-52-46](https://github.com/LuisBalsa/Cub3d/assets/81270660/aa35d05c-bc0c-4e22-96a3-0c5b70315ee7)

The camera vector is multiplied by values ranging from -1 (for the leftmost vertical line of pixels on our screen) to 1 (for the rightmost vertical line of pixels on our screen). By adding the result to the direction vector, we obtain the green vector represented in the GIF below.
![Peek 2024-04-16 16-49](https://github.com/LuisBalsa/Cub3d/assets/81270660/7ef589a6-453b-446b-bada-4d3cdbfb7cb9)


This process effectively scans the entire field of view, enabling us to measure distances necessary for ray-casting, as illustrated by the green vector.
This green vector is the vector we will use to take measurements needed for each iteration, for every vertical row of pixels on our screen.

For a more in-depth explanation of the ray-casting technique and its implementation, refer to the tutorial available [here](https://lodev.org/cgtutor/raycasting.html).

## Installation

To run Cub3D on your machine, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the project directory.
3. Compile the source code using the provided Makefile.
   ```
   make bonus
   ```
4. Run the executable with the desired map file. You can specify the map file from 1.cub to 4.cub like so:
   ```
   ./cub3D maps/1.cub
   ```


## Controls


- Use the left and right arrow keys to look left and right in the maze.
- Use the W, A, S, and D keys to move the point of view through the maze.
- Press ESC to close the window and quit.
- Clicking on the red cross on the window’s frame also closes the window and quits.

Additionally, you can rotate the point of view using the mouse. To activate mouse control, click the left button. Once activated, click ESC once to revert to keyboard control.



## Authors  - [Luis Balsa](https://github.com/LuisBalsa) - [Adam Kirst](https://github.com/adamckirst)

---

Feel free to explore and modify Cub3D to suit your needs and preferences. Happy gaming! 🎮



