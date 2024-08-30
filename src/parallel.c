/*
    parallel.c
    Parallel implementation of the screen saver

    Authors:
    * Ricardo Mendez
    * Sara Echeverria
    * Melissa Perez
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define WIDTH 640       // Window width
#define HEIGHT 480      // Window height

// Structure to represent a circle
typedef struct {
    float x, y;         // Positions of the circle's center
    float dx, dy;       // Velocities in X and Y directions
    float radius;       // Radius of the circle
    SDL_Color color;    // Color of the circle
} Circle;

// Function to generate a random number between min and max
float rand_range(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

// Function to initialize circles with random positions, velocities, and colors
void init_circles(Circle *circles, int n) {
    // Parallelize the initialization of the circles
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        // Random radius between 5 and 20
        circles[i].radius = rand_range(5.0, 20.0);

        // Random X and Y positions within the window bounds
        circles[i].x = rand_range(circles[i].radius, WIDTH - circles[i].radius);
        circles[i].y = rand_range(circles[i].radius, HEIGHT - circles[i].radius);

        // Random velocity in X and Y directions
        circles[i].dx = rand_range(-2.0, 2.0);
        circles[i].dy = rand_range(-2.0, 2.0);

        // Random color (RGB) with maximum alpha value
        circles[i].color.r = rand() % 256;
        circles[i].color.g = rand() % 256;
        circles[i].color.b = rand() % 256;
        circles[i].color.a = 255;
    }
}

void render_frame(SDL_Renderer *renderer, Circle *circles, int n) {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Actualizar posiciones y manejar colisiones con los bordes
            for (int i = 0; i < n; i++) {
                circles[i].x += circles[i].dx;
                circles[i].y += circles[i].dy;

                if (circles[i].x <= circles[i].radius || circles[i].x >= WIDTH - circles[i].radius) {
                    circles[i].dx = -circles[i].dx;
                }
                if (circles[i].y <= circles[i].radius || circles[i].y >= HEIGHT - circles[i].radius) {
                    circles[i].dy = -circles[i].dy;
                }
            }
        }

        #pragma omp section
        {
            // Limpiar la pantalla y dibujar todos los círculos en una sección crítica
            #pragma omp critical
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                for (int i = 0; i < n; i++) {
                    SDL_SetRenderDrawColor(renderer, circles[i].color.r, circles[i].color.g, circles[i].color.b, circles[i].color.a);
                    int x, y;
                    for (y = -circles[i].radius; y <= circles[i].radius; y++) {
                        for (x = -circles[i].radius; x <= circles[i].radius; x++) {
                            if (x * x + y * y <= circles[i].radius * circles[i].radius) {
                                SDL_RenderDrawPoint(renderer, circles[i].x + x, circles[i].y + y);
                            }
                        }
                    }
                }
            }
        }
    }
}

// Draw multiple circles
void draw_circles(SDL_Renderer *renderer, Circle *circles, int n) {
    for (int i = 0; i < n; i++) {
        draw_circle(renderer, &circles[i]);
    }
}

// Function to calculate and display FPS (Frames Per Second)
void calculate_fps(Uint32 start_time, int *frame_count, float *fps) {
    (*frame_count)++;
    Uint32 current_time = SDL_GetTicks();
    // If one second has passed, calculate FPS
    if (current_time > start_time + 1000) {
        *fps = *frame_count * 1000.0f / (current_time - start_time);
        *frame_count = 0;
        start_time = current_time;
    }
}

// Function to update the window title with the current FPS
void update_window_title(SDL_Window *window, float fps) {
    char title[64];
    snprintf(title, sizeof(title), "Screensaver - %.2f FPS", fps);
    SDL_SetWindowTitle(window, title);
}

// Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number_of_circles>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    Circle *circles = malloc(n * sizeof(Circle));
    if (!circles) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    init_circles(circles, n);

    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        free(circles);
        return 1;
    }

    // Create a window centered on the screen
    SDL_Window *window = SDL_CreateWindow("Screensaver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(circles);
        return 1;
    }

    // Create a renderer for the window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(circles);
        return 1;
    }

    // Main loop variables
    int running = 1;
    int frame_count = 0;
    float fps = 0.0f;
    Uint32 start_time = SDL_GetTicks();

    // Main loop
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        update_positions(circles, n);

        // Clear the screen with black color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw all circles
        draw_circles(renderer, circles, n);

        calculate_fps(start_time, &frame_count, &fps);
        update_window_title(window, fps);

        SDL_RenderPresent(renderer);
    }

    // Cleanup and exit
    free(circles);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
