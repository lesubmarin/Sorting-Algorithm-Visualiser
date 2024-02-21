#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ranges>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>

const int WindowWidth = 900;
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

    // Create random vector of 300 elements
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 639);
    std::vector<int> vec;
    for (int i = 0; i < 300; i++)
    {
        vec.push_back(dist(rd));
    }
   
    // Calculate bar width
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);
    int barWidth = width / vec.size();

    // Insertion sort
    int i, poz;
    int n = vec.size();
    int iterations = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    for(i = 1; i < n; i++) {
        int val = vec[i];
        // Search for the position where the element should be inserted
        for(poz = i; poz != 0 && vec[poz - 1] > val; poz--) {
            // Shift elements to the right
            vec[poz] = vec[poz - 1];

             // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw state
        draw_state(vec, renderer, i, poz, barWidth);

        // Render
        SDL_RenderPresent(renderer);

        // Delay
        SDL_Delay(10);
        }

        vec[poz] = val;

        // Print iteration count and time to console
        iterations++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        std::cout << "Iteration: " << iterations << ", Total time: " << duration << " ms" << std::endl;
    }

    return 0;
}