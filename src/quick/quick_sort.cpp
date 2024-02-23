#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <ranges>
#include <SDL2/SDL.h>
#include <chrono>

const int WindowWidth = 1280;
const int WindowHeight = 640;

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, int red, int blue, int barWidth) {
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);
    
    for (int i = 0; i < v.size(); ++i) {
        int x = i * barWidth;
        if (i == red) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for the first element being compared
        } else if (i == blue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for the second element being compared
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, x, height, x, height - v[i]);
    }
}

int partition(std::vector<int>& arr, int start, int end, SDL_Renderer* renderer, int barWidth, int& comparisons)
{
    int pivot = arr[end]; // Choose the last element as pivot
    int i = start - 1;

    for (int j = start; j < end; j++) {
        comparisons++; // Increment comparisons counter
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]); // Swap elements
        }
    }

    std::swap(arr[i + 1], arr[end]); // Move pivot to its correct position
    int pivotIndex = i + 1;

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw state
    draw_state(arr, renderer, pivotIndex, end, barWidth);

    // Render
    SDL_RenderPresent(renderer);

    // Delay for visualization
    SDL_Delay(100);

    return pivotIndex;
}

void quickSort(std::vector<int>& arr, int start, int end, SDL_Renderer* renderer, int barWidth, int& comparisons)
{
    if (start >= end)
        return;

    int p = partition(arr, start, end, renderer, barWidth, comparisons);

    quickSort(arr, start, p - 1, renderer, barWidth, comparisons);
    quickSort(arr, p + 1, end, renderer, barWidth, comparisons);
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

    // Initialize comparisons counter
    int comparisons = 0;

    // Start quicksort
    auto startTime = std::chrono::high_resolution_clock::now();
    quickSort(vec, 0, vec.size() - 1, renderer, barWidth, comparisons);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // Print the number of comparisons and time
    std::cout << "Number of comparisons: " << comparisons << std::endl;
    std::cout << "Total time: " << duration << " ms" << std::endl;

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
