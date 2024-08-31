# screensaver
This project implements a parallelized screensaver using OpenMP and SDL in C. The screensaver generates a number of moving objects circles that bounce within a defined canvas. The main focus of the project is to demonstrate the use of parallel computing to enhance the performance of a traditionally sequential program.

<p align="center">
  <br>
  <img src="https://i.imgur.com/da0ka7g.png" alt="pic" width="500">
  <br>
</p>
<p align="center" >
  <a href="#features">Features</a> •
  <a href="#dependencies">Dependencies</a> •
  <a href="#inspiration">Inspiration</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#documentation">Documentation</a> 
</p>

## Features
- **Parallelization with OpenMP:** The program is designed to leverage multiple CPU cores for improved performance.
- **Configurable Elements:** The user can define the number of circles to render (`N`), and the program will generate them with random colors and sizes.
- **Physics Simulation:** Each circle moves and rebounds within the canvas, simulating basic physical interactions.
- **Frame Rate Display:** The program displays the current frames per second (FPS) to monitor performance.

## Dependencies
- **OpenMP:** Used for parallelizing the computation.
- **SDL (Simple DirectMedia Layer):** A library used for rendering graphics.

## Inspiration
This screensaver was inspired by the classic bouncing ball screensavers. The design and concept were based on [this image](https://i.ytimg.com/vi/VYC5Q_9-rB4/maxresdefault.jpg), which provided the visual and functional framework for our implementation.

<p align="center">
  <br>
  <img src="https://i.ytimg.com/vi/VYC5Q_9-rB4/maxresdefault.jpg" alt="Inspiration pic" width="500">
  <br>
</p>

## How To Use
### Compiling the Project
```bash
# Sequential version
gcc -o sequential sequential.c -lSDL2 -lm

# Parallel version
gcc -o parallel parallel.c -fopenmp -lSDL2
```
### Running the Project
```bash
# Sequential version
./sequential <number of circles>

# Parallel version
./parallel <number of circles>
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
