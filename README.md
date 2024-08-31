# screensaver
This project implements a parallelized screensaver using OpenMP and SDL in C. The screensaver generates a number of moving objects circles that bounce within a defined canvas. The main focus of the project is to demonstrate the use of parallel computing to enhance the performance of a traditionally sequential program.

<p align="center">
  <br>
  <img src="https://i.imgur.com/da0ka7g.png" alt="pic" width="500">
  <br>
</p>
<p align="center" >
  <a href="#features">Features</a> •
  <a href="#files">Files</a> •
  <a href="#dependencies">Dependencies</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#documentation">Documentation</a> •
  <a href="#inspiration">Inspiration</a> •
  <a href="#contributors">Contributors</a>
</p>

## Features
- **Parallelization with OpenMP:** The program is designed to leverage multiple CPU cores for improved performance.
- **Configurable Elements:** The user can define the number of circles to render (`N`), and the program will generate them with random colors and sizes.
- **Physics Simulation:** Each circle moves and rebounds within the canvas, simulating basic physical interactions.
- **Frame Rate Display:** The program displays the current frames per second (FPS) to monitor performance.

## Files
### 1. sequential.c
This file contains the implementation of the screensaver in its sequential form. The key characteristics of this version are:
- **Single-threaded execution:** All circles are processed in a loop within a single thread.
- **Basic structure:** This version is straightforward, processing each circle's position update and rendering sequentially.
- **Use of SDL:** Utilizes SDL for handling graphics rendering and window management.

### 2. parallel.c
This file contains the parallelized implementation of the screensaver using OpenMP. Key characteristics include:
- **Multi-threaded execution:** The circle updates are distributed across multiple threads using OpenMP, allowing simultaneous processing.
- **OpenMP directives:** The program leverages OpenMP's `#pragma omp` directives to parallelize loops, enhancing performance on multi-core processors.
- **Optimized performance:** Designed to take full advantage of modern CPUs by distributing the workload across available cores, resulting in potentially higher FPS compared to the sequential version.

Both files utilize SDL for rendering and are designed to demonstrate the benefits of parallel computing in a visually engaging way.

## Dependencies
- **OpenMP:** Used for parallelizing the computation.
- **SDL (Simple DirectMedia Layer):** A library used for rendering graphics.

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

## Inspiration
This screensaver was inspired by the classic bouncing ball screensavers. The design and concept were based on [this image](https://i.ytimg.com/vi/VYC5Q_9-rB4/maxresdefault.jpg), which provided the visual and functional framework for our implementation.

<p align="center">
  <br>
  <img src="https://i.ytimg.com/vi/VYC5Q_9-rB4/maxresdefault.jpg" alt="Inspiration pic" width="500">
  <br>
</p>

## Contributors
[@MelissaPerez09](https://github.com/MelissaPerez09) | [@bl33h](https://github.com/bl33h) | [@Mendezg1](https://github.com/Mendezg1)
