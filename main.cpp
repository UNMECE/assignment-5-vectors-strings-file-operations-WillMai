#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "pixel.h"

// Function to read pixel data from a file
void read_pixels(const std::string &file_name, std::vector<Pixel> &pixel_list) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        Pixel pixel;
        // Read x
        std::getline(ss, token, ',');
        pixel.x = std::stoi(token);

        // Read y
        std::getline(ss, token, ',');
        pixel.y = std::stoi(token);

        // Read r
        std::getline(ss, token, ',');
        pixel.r = std::stof(token);

        // Read g
        std::getline(ss, token, ',');
        pixel.g = std::stof(token);

        // Read b
        std::getline(ss, token, ',');
        pixel.b = std::stof(token);

        pixel_list.push_back(pixel);
    }

    file.close();
}

// Function to calculate average colors
void average_colors(std::vector<Pixel> &pixel_list) {
    float total_r = 0.0, total_g = 0.0, total_b = 0.0;
    int num_pixels = pixel_list.size();

    for (const auto &pixel : pixel_list) {
        total_r += pixel.r;
        total_g += pixel.g;
        total_b += pixel.b;
    }

    std::cout << "Average R: " << total_r / num_pixels << std::endl;
    std::cout << "Average G: " << total_g / num_pixels << std::endl;
    std::cout << "Average B: " << total_b / num_pixels << std::endl;
}

// Function to flip the image vertically
void flip_vertically(std::vector<Pixel> &pixel_list) {
    int max_y = 255; // y-length is 256, so the max y index is 255
    for (auto &pixel : pixel_list) {
        pixel.y = max_y - pixel.y;
    }
}

// Function to write pixel data to a file
void write_pixels(const std::string &file_name, const std::vector<Pixel> &pixel_list) {
    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    for (const auto &pixel : pixel_list) {
        file << pixel.x << "," << pixel.y << "," << pixel.r << "," << pixel.g << "," << pixel.b << "\n";
    }

    file.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string file_name = argv[1];
    std::vector<Pixel> pixel_list;

    // Step 3: Read pixels from file
    read_pixels(file_name, pixel_list);

    // Step 4: Calculate average colors
    average_colors(pixel_list);

    // Step 4: Flip the image vertically
    flip_vertically(pixel_list);

    // Step 5: Save the flipped pixel list to a new file
    write_pixels("flipped.dat", pixel_list);

    return 0;
}
