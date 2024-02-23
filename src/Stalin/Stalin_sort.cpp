#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <ranges>
#include <SDL2/SDL.h>
#include <chrono>

const int WindowWidth = 1280;
const int WindowHeight = 640;

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue, int barWidth) {
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);
    
    for (int i = 0; i < v.size(); ++i) {
        int x = i * barWidth;
        if (i == red) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else if (i == blue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, x, height, x, height - v[i]);
    }
}

int main(int argc, char *argv[])
{
    // Create window
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(WindowWidth, WindowHeight, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    // Create vector with numbers from 1 to 640
    std::vector<int> vec(640);
    std::iota(vec.begin(), vec.end(), 1); // Fill vector with numbers from 1 to 100

    // Shuffle the vector randomly
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
   
    // Calculate bar width
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);
    int barWidth = width / vec.size();

    // Stalin sort
    int comparisons = 0; // Counter for comparisons
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < vec.size(); i++) {
        if (i > 0 && vec[i] < vec[i-1]) {
            vec.erase(vec.begin() + i);

            // Draw the current state
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(vec, renderer, i, i-1, barWidth);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            i--;
        }
    }


    // Main loop flag
    bool quit = false;

    // Main loop
    while (!quit)
    {
        // Event handling
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true; // Set the quit flag if the user closes the window
            }
        }
    }

    // Clean up resources and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
