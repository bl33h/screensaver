# Screensaver Project

## Overview
This project implements a parallelized screensaver using OpenMP and SDL in C. The screensaver generates a number of moving objects circles that bounce within a defined canvas. The main focus of the project is to demonstrate the use of parallel computing to enhance the performance of a traditionally sequential program.

## Features

- **Parallelization with OpenMP:** The program is designed to leverage multiple CPU cores for improved performance.
- **Configurable Elements:** The user can define the number of circles to render (`N`), and the program will generate them with random colors and sizes.
- **Physics Simulation:** Each circle moves and rebounds within the canvas, simulating basic physical interactions.
- **Frame Rate Display:** The program displays the current frames per second (FPS) to monitor performance.

## Dependencies

- **OpenMP:** Used for parallelizing the computation.
- **SDL (Simple DirectMedia Layer):** A library used for rendering graphics.

## Usage
### Compiling the Project
```bash
# Sequential version
gcc -o sequential sequential.c -lSDL2

# Parallel version
gcc -o parallel parallel.c -fopenmp -lSDL2
```
### Running the Project
```bash
# Sequential version
./sequential <number_of_circles>

# Parallel version
./parallel <number_of_circles>
```

## Documentation
### Program Flow
The program first captures user input (number of circles) and initializes the SDL graphics context. Depending on the chosen version (sequential or parallel), the circles are then generated and updated in a loop until the program is terminated. Each frame is rendered to the screen, and the FPS is calculated and displayed.

### Functionality
- Initialization: Sets up the SDL environment and prepares the necessary data structures.
- Rendering: Draws the circles on the canvas, updating their positions in each frame.
- Parallelization: In the parallel version, OpenMP is used to distribute the circle update calculations across multiple threads.

### Defensive Programming
The program includes checks for user input and handles potential errors, such as invalid parameters or failed SDL initialization.

## Contributors
[@MelissaPerez09](https://github.com/MelissaPerez09) | [@bl33h](https://github.com/bl33h) | [@Mendezg1](https://github.com/Mendezg1)