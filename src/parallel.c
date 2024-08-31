/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, bl33h, Mendezg1, MelissaPerez09
@author Sara Echeverria, Ricardo Mendez, Melissa Perez
FileName: parallel.c
@version: I
Creation: 25/07/2024
Last modification: 30/08/2024
------------------------------------------------------------------------------*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

// window dimensions
#define WIDTH 640  
#define HEIGHT 480   

// circle structure, includes position, velocity, radius and color
typedef struct {
    float x, y;        
    float dx, dy;       
    float radius;      
    SDL_Color color;    
} Circle;

// function to generate a random number between min and max
float randRange(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

// function to initialize circles with random positions, velocities, and colors [PARALLEL]
void initCircles(Circle *circles, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        circles[i].radius = randRange(5.0, 20.0);
        circles[i].x = randRange(circles[i].radius, WIDTH - circles[i].radius);
        circles[i].y = randRange(circles[i].radius, HEIGHT - circles[i].radius);
        circles[i].dx = randRange(-2.0, 2.0);
        circles[i].dy = randRange(-2.0, 2.0);
        circles[i].color.r = rand() % 256;
        circles[i].color.g = rand() % 256;
        circles[i].color.b = rand() % 256;
        circles[i].color.a = 255;
    }
}

// function to update the positions of the circles [PARALLEL]
void updatePositions(Circle *circles, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 100; j++) {
            circles[i].x += circles[i].dx * 0.01;
            circles[i].y += circles[i].dy * 0.01;
            if (circles[i].x <= circles[i].radius || circles[i].x >= WIDTH - circles[i].radius) {
                circles[i].dx = -circles[i].dx;
            }
            if (circles[i].y <= circles[i].radius || circles[i].y >= HEIGHT - circles[i].radius) {
                circles[i].dy = -circles[i].dy;
            }
        }
    }
    #pragma omp barrier
}

// function to draw a circle using SDL
void drawCircle(SDL_Renderer *renderer, Circle *circle) {
    const int diameter = (circle->radius * 2);

    int x = (circle->radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, circle->color.a);
    
    while (x >= y) {
        SDL_RenderDrawPoint(renderer, circle->x + x, circle->y - y);
        SDL_RenderDrawPoint(renderer, circle->x + x, circle->y + y);
        SDL_RenderDrawPoint(renderer, circle->x - x, circle->y - y);
        SDL_RenderDrawPoint(renderer, circle->x - x, circle->y + y);
        SDL_RenderDrawPoint(renderer, circle->x + y, circle->y - x);
        SDL_RenderDrawPoint(renderer, circle->x + y, circle->y + x);
        SDL_RenderDrawPoint(renderer, circle->x - y, circle->y - x);
        SDL_RenderDrawPoint(renderer, circle->x - y, circle->y + x);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            x--;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

// function to calculate and display the frames per second
void calculateAndDisplayFps(SDL_Window *window, Uint32 *last_time, int *frame_count) {
    Uint32 current_time = SDL_GetTicks();
    (*frame_count)++;
    if (current_time - *last_time >= 1000) {
        float fps = *frame_count * 1000.0 / (current_time - *last_time);
        char title[256];
        snprintf(title, sizeof(title), "Parallel Screensaver - FPS: %.2f", fps);
        SDL_SetWindowTitle(window, title);
        *last_time = current_time;
        *frame_count = 0;
    }
}

// main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "-> usage: %s <number of circles>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    Circle *circles = malloc(n * sizeof(Circle));
    if (!circles) {
        fprintf(stderr, "!memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    initCircles(circles, n);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "!SDL_Init error: %s\n", SDL_GetError());
        free(circles);
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Parallel Screensaver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "!SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        free(circles);
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "!SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_Quit();
        free(circles);
        return 1;
    }

    int running = 1;
    Uint32 last_time = SDL_GetTicks();
    int frame_count = 0;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        updatePositions(circles, n);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < n; i++) {
            drawCircle(renderer, &circles[i]);
        }

        SDL_RenderPresent(renderer);
        calculateAndDisplayFps(window, &last_time, &frame_count);
    }

    free(circles);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}