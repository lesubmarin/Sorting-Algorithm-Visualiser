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
    int barWidth = WindowWidth / vec.size();

    // Insertion sort
    int i, poz;
    int n = vec.size();
    int comparisons = 0; // Counter for comparisons
    auto startTime = std::chrono::high_resolution_clock::now();
    for(i = 1; i < n; i++) {
        int val = vec[i];
        // Search for the position where the element should be inserted
        for(poz = i; poz != 0 && vec[poz - 1] > val; poz--) {
            // Shift elements to the right
            vec[poz] = vec[poz-1];
            comparisons++; // Increment the comparisons counter

            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Draw state
            draw_state(vec, renderer, i, poz, barWidth);

            // Render
            SDL_RenderPresent(renderer);

            // Delay
            SDL_Delay(1);
        }

        vec[poz] = val;

        // Print comparisons count and time to console
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        std::cout << "Comparisons: " << comparisons << ", Total time: " << duration << " ms" << std::endl;
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
