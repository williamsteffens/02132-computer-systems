/*
Cell counting program - Ass1
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

#include "cbmp.h"

// TODO: add morph enum for erode and dilation here:)
// TODO: add enum for drawing:)

unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char intermedia_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
int cellCount = 0; 



void create_binary(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH]) {
  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {
        // TODO: otsu metode???
        int avg = (input_image[x][y][0] + input_image[x][y][1] + input_image[x][y][2]) / 3;
        output_image[x][y] = avg > 90 ? 255 : 0;
    }
  }
}

void create_binary_image(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      for (int c = 0; c < BMP_CHANNELS; ++c) {
        int avg = (input_image[x][y][0] + input_image[x][y][1] + input_image[x][y][2]) / 3;
        output_image[x][y][c] = avg > 90 ? 255 : 0;
      }
    }
  }
}

// void erode(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH]) {
//   for (int x = 0; x < BMP_WIDTH; x++) {
//     for (int y = 0; y < BMP_HEIGTH; y++) {
//       // do stuff here to erode the array :)
//     }
//   }
// }

bool is_on_edge(int x, int y, int width, int height) {
  bool max = x >= width - 1 || y >= height - 1;
  bool min = x == 0 || y == 0;

  if (max || min) 
    return true;
  else 
    return false; 
}

bool erode_image(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  unsigned char structing_element[3][3] = {{0,1,0},{1,1,1},{0,1,0}};
  bool wasEroded = false;
  bool erodePixel;   

  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      if (is_on_edge(x, y, BMP_WIDTH, BMP_HEIGTH)) {
        if (input_image[x][y][0] == 255) {
          output_image[x][y][0] = 0;
          output_image[x][y][1] = 0;
          output_image[x][y][2] = 0;
          wasEroded = true;
        }
      } else {
        erodePixel = false; 
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            // no need to check all of the indexes, so break as needed
            if (structing_element[i][j] == 1 && input_image[x + i - 1][y + j - 1][0] == 0) {
              erodePixel = true; 
              break;
            }
          }
          if (erodePixel) {
            output_image[x][y][0] = 0;
            output_image[x][y][1] = 0;
            output_image[x][y][2] = 0; 
            break;
          }
        }

        if (!erodePixel) {
          output_image[x][y][0] = 255;
          output_image[x][y][1] = 255;
          output_image[x][y][2] = 255;
        }
      }
    }
  }

  return wasEroded; 
}

bool detection_frame_clear(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int totalWidth) {
  for (int i = 0; i < totalWidth; ++i)
    for (int j = 0; j < totalWidth; ++j)
      if (i == 0 || i == totalWidth - 1 || j == 0 || j == totalWidth - 1)
        if (image[x + i][y + j][0] == 255)
          return false;

  return true; 
}

bool cell_detected(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int capAreaWidth) {
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j)
      if (image[x + i][y + j][0] == 255)
        return true;

  return false; 
}

void draw_detection_indication(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int totalWidth) {
  int detection_indication[13][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,1,0,0,0,0,0,0,0},}; 
  
  for (int i = 0; i < totalWidth; ++i)
    for (int j = 0; j < totalWidth; ++j)
      if (detection_indication[i][j] == 1) {
        image[x + i][y + j][0] = 255;
        image[x + i][y + j][1] = 0;
        image[x + i][y + j][2] = 255;
      }

  // for (int i = 0; i < totalWidth; ++i)
  //   for (int j = 0; j < totalWidth; ++j)
  //     if (i == 0 || i == totalWidth - 1 || j == 0 || j == totalWidth - 1) {
  //       image[x + i][y + j][0] = 255;
  //       image[x + i][y + j][1] = 0;
  //       image[x + i][y + j][2] = 255;
  //     }
}

void remove_cell(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int capAreaWidth) {
  // TODO: maybe only color white parts of the image; there's no need to color black pixels black
  for (int i = 1; i < capAreaWidth; ++i)
    for (int j = 1; j < capAreaWidth; ++j) {
      image[x + i][y + j][0] = 0;
      image[x + i][y + j][1] = 0;
      image[x + i][y + j][2] = 0;
    }
}

void detect_cells(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char out_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int* cellCount, bool printCoords) {
  // TODO: we assume that the erosion erases the border pixels of the image
  int frameWidth = 1;
  int capAreaWidth = 12; 
  // TODO: Maybe change the capture area to be 2d array

  for (int x = 0; x < BMP_WIDTH - capAreaWidth; ++x)
    for (int y = 0; y < BMP_WIDTH - capAreaWidth; ++y)
      
      if (detection_frame_clear(in_image, x, y, capAreaWidth + frameWidth))
        if (cell_detected(in_image, x, y, capAreaWidth)) {
          draw_detection_indication(out_image, x, y, capAreaWidth + frameWidth);
          remove_cell(in_image, x, y, capAreaWidth);
          ++*cellCount;
          if (printCoords)
            // TODO: modify this to be the center
            printf("cell #%d: (%d, %d)\n", *cellCount, x, y);
        }
}



int main(int argc, char** argv) {
  if (argc != 3) {
      fprintf(stderr, "Usage: %s <input file path> <output file path>\n", argv[0]);
      exit(1);
  }

  printf("Cell detection program - 02132 - Ass1\n");

  // Step 1: Load input image
  read_bitmap(argv[1], input_image);
  
  // Step 2 and 3: Convert from RGB to GrayScale and apply the binary threshold to create a binary image
  create_binary_image(input_image, intermedia_image);

  // TODO: Why erode the image first? Shouldn't we detect the cells we can and then erode? or are we trying to get rid of noise? 
  // Step 4: Erode the binary image
  printf("Cell detection results:");

  int step = 0;
  while(erode(intermedia_image)) {
    // print steps for debugging
    write_bitmap(intermedia_image, "step_%d_%s", step++, argv[2]);

    // Step 5 and 6: Detect cells and print results
    detect_cells(intermedia_image, input_image, &cellCount, true);
  }

  printf("\tA total of %d %s detected", cellCount, cellCount > 1 ? "cells were" : "cell was");

  // Step 7: Save output image and print results
  write_bitmap(input_image, argv[2]);

  printf("cells detected: %d\n", cellCount);
  printf("Done!\n");
  return 0;
}

