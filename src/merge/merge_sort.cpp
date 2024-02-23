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

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, int start, int end, int mid, int barWidth) {
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    for (int i = 0; i < v.size(); ++i) {
        int x = i * barWidth;
        if (i >= start && i <= end) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for elements being merged
        } else if (i == mid) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for the midpoint
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for other elements
        }
        SDL_RenderDrawLine(renderer, x, height, x, height - v[i]);
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right, SDL_Renderer* renderer, int barWidth, int& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++; // Increment comparisons counter
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw state
        draw_state(arr, renderer, left, right, mid, barWidth);

        // Render
        SDL_RenderPresent(renderer);

        // Delay for visualization
        SDL_Delay(10);
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw state
        draw_state(arr, renderer, left, right, mid, barWidth);

        // Render
        SDL_RenderPresent(renderer);

        // Delay for visualization
        SDL_Delay(100);
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw state
        draw_state(arr, renderer, left, right, mid, barWidth);

        // Render
        SDL_RenderPresent(renderer);

        // Delay for visualization
        SDL_Delay(1);
    }
}

void mergeSort(std::vector<int>& arr, int left, int right, SDL_Renderer* renderer, int barWidth, int& comparisons) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, renderer, barWidth, comparisons);
    mergeSort(arr, mid + 1, right, renderer, barWidth, comparisons);
    merge(arr, left, mid, right, renderer, barWidth, comparisons);
}

int main(int argc, char *argv[]) {
    // Create window
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(WindowWidth, WindowHeight, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    // Create vector with numbers from 1 to 640
    std::vector<int> vec(640);
    std::iota(vec.begin(), vec.end(), 1); // Fill vector with numbers from 1 to 640

    // Shuffle the vector randomly
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    // Calculate bar width
    int barWidth = WindowWidth / vec.size();

    // Initialize comparisons counter
    int comparisons = 0;

    // Start mergesort
    auto startTime = std::chrono::high_resolution_clock::now();
    mergeSort(vec, 0, vec.size() - 1, renderer, barWidth, comparisons);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // Print the number of comparisons and time
    std::cout << "Number of comparisons: " << comparisons << std::endl;
    std::cout << "Total time: " << duration << " ms" << std::endl;

    // Main loop flag
    bool quit = false;

    // Main loop
    while (!quit) {
        // Event handling
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
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
