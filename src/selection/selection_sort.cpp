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
    int n = vec.size();
    int iterations = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n-1; i++) {
        // Finds the minimum element between i+1 and n
        int min_idx = i;
        for(int j = i+1; j < n; j++) {
            if(vec[j] < vec[min_idx]) {
                min_idx = j;
            }
        }
        // Interchange the minimum element with the first element
        std::swap(vec[min_idx], vec[i]);
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw state
        draw_state(vec, renderer, i, min_idx, barWidth);

        // Render
        SDL_RenderPresent(renderer);

        // Delay
        SDL_Delay(10); // Adjust delay as needed
        
        // Print iteration count and time to console
        iterations++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        std::cout << "Iteration: " << iterations << ", Total time: " << duration << " ms" << std::endl;
    }
    return 0;
}
