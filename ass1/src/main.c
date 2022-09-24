/*
Cell counting program - Ass1
*/

#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "cbmp.h"


// start = clock();
// /* The code that has to be measured. */
// end = clock();
// cpu_time_used = end - start;
// printf("Total time: %f ms\n", cpu_time_used * 1000.0 /
// CLOCKS_PER_SEC);

// TODO: add the above as needed, and look into macros in C



// TODO: add morph enum for erode and dilation here:)
// TODO: add enum for drawing:)

unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
#if DEBUG
  unsigned char debug_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
#endif
unsigned char intermedia_image0[BMP_WIDTH][BMP_HEIGTH];
unsigned char intermedia_image1[BMP_WIDTH][BMP_HEIGTH];
unsigned char (*image0_ptr)[BMP_HEIGTH] = intermedia_image0;
unsigned char (*image1_ptr)[BMP_HEIGTH] = intermedia_image1;
unsigned char (*tmp_ptr)[BMP_HEIGTH];

int step = 0;
int cellCount = 0; 
char buffer[50];


bool is_on_edge(int x, int y, int width, int height) {
  bool max = x >= width - 1 || y >= height - 1;
  bool min = x == 0 || y == 0;

  if (max || min) 
    return true;
  else 
    return false; 
}

void create_binary(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char binary[BMP_WIDTH][BMP_HEIGTH]) {
  int th = 90;
  
  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      int avg = (in_image[x][y][0] + in_image[x][y][1] + in_image[x][y][2]);
      binary[x][y] = avg > th * 3 ? 1 : 0;
    }
  }
}

bool erode(unsigned char in_binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_binary[BMP_WIDTH][BMP_HEIGTH]) {
  unsigned char structing_element[3][3] = {{0,1,0},{1,1,1},{0,1,0}};
  bool wasEroded = false;
  bool erodePixel;

  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {

      // TODO: Should only erode if the pixel is white, change to center for other structing elements
      if (in_binary[x][y] == 0) {
        out_binary[x][y] = in_binary[x][y];
        continue;
      }

      erodePixel = false;
      if (is_on_edge(x, y, BMP_WIDTH, BMP_HEIGTH)) {
          erodePixel = true;
      } else {
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j)
            if (structing_element[i][j] == 1 && in_binary[x + i - 1][y + j - 1] == 0) {
              erodePixel = true;
              // TODO: consider using <goto> here so you don't need to break twice
              break;
            }
          if (erodePixel)
            break;
        }
      }

      if (erodePixel) {
        out_binary[x][y] = 0;
        wasEroded = true;
      } else {
        out_binary[x][y] = in_binary[x][y];
      }
    }
  }

  return wasEroded; 
}

bool detection_frame_clear(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], int x, int y, int totalWidth) {
  for (int i = 0; i < totalWidth; ++i) {
    if (binary[x + i][y] == 1)
      return false;
    if (binary[x + i][y + totalWidth - 1] == 1)
      return false; 
    if (i == 0 || i == totalWidth - 1)
      for (int j = 0; j < totalWidth; ++j)
        if (binary[x + i][y + j] == 1)
          return false; 
  }
  
  // inefficient square frame
  //
  // for (int i = 0; i < totalWidth; ++i)
  //   for (int j = 0; j < totalWidth; ++j)
  //     if (i == 0 || i == totalWidth - 1 || j == 0 || j == totalWidth - 1)
  //       if (binary[x + i][y + j] == 1)
  //         return false;

  return true; 
}

bool cell_detected(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], int x, int y, int capAreaWidth) {
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j)
      if (binary[x + i][y + j] == 1)
        return true;

  return false; 
}

void draw_detection_indication(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int totalWidth) {
  int detection_indication[14][14] = {{0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                                      {0,0,0,1,1,0,0,0,1,1,1,0,0,0},
                                      {0,0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,0,1,1,0,0,0,0,0,1,0,0,0},
                                      {0,0,0,1,0,0,0,0,0,0,1,0,0,0},
                                      {0,0,0,1,1,1,1,1,1,0,1,0,0,0},
                                      {0,0,0,1,0,0,0,0,1,0,1,0,0,0},
                                      {0,0,0,1,1,0,0,0,1,0,1,0,0,0},
                                      {0,0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,0,1,1,0,0,0,1,1,1,0,0,0},
                                      {0,0,0,1,0,0,0,0,0,0,0,0,0,0},}; 
  
  for (int i = 0; i < totalWidth; ++i)
    for (int j = 0; j < totalWidth; ++j)
      if (detection_indication[i][j] == 1) {
        image[x + i][y + j][0] = 255;
        image[x + i][y + j][1] = 0;
        image[x + i][y + j][2] = 0;
      }

  // do option for getting the silhoutte of the cell 
  // curly brackets
  // washing machine symbol 
  // Lorem Ipsum 
  // [] or only corners

  // square
  // for (int i = 0; i < totalWidth; ++i)
  //   for (int j = 0; j < totalWidth; ++j)
  //     if (i == 0 || i == totalWidth - 1 || j == 0 || j == totalWidth - 1) {
  //       image[x + i][y + j][0] = 255;
  //       image[x + i][y + j][1] = 0;
  //       image[x + i][y + j][2] = 0;
  //     }
}

void remove_cell(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], int x, int y, int capAreaWidth) {
  // TODO: maybe only color white parts of the binary; there's no need to color black pixels black
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j)
      binary[x + i][y + j] = 0;
}

void detect_cells(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int* cellCount, bool printCoords) {
  // TODO: we assume that the erosion erases the border pixels of the image
  int frameWidth = 1;
  int capAreaWidth = 12; 
  // TODO: Maybe change the capture area to be 2d array

  // TODO: Is it better to pull out the conditions of the for loop? 
  for (int x = 0; x < BMP_WIDTH - (capAreaWidth + frameWidth); ++x)
    for (int y = 0; y < BMP_WIDTH - (capAreaWidth + frameWidth); ++y)
      
      if (detection_frame_clear(binary, x, y, capAreaWidth + frameWidth * 2))
        if (cell_detected(binary, x, y, capAreaWidth)) {
          draw_detection_indication(out_image, x, y, capAreaWidth + frameWidth * 2);
          remove_cell(binary, x, y, capAreaWidth);
          ++*cellCount;
          if (printCoords)
            printf("\tcell #%d: (%d, %d)\n", *cellCount, x + capAreaWidth / 2, y + capAreaWidth / 2);
        }
}

void binary_to_BMP(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char BMP[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      for (int c = 0; c < BMP_CHANNELS; ++c) {
        if (binary[x][y] == 1)
          BMP[x][y][c] = 255;
        else 
          BMP[x][y][c] = 0;
      }
    }
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
  create_binary(input_image, image0_ptr);

  // TODO: Why erode the image first? Shouldn't we detect the cells we can and then erode? or are we trying to get rid of noise? 
  // Step 4: Erode the binary image
  printf("Cell detection results:\n");


  // TODO: MAKE THE DETECITON FRAME TRUE 


  while(erode(image0_ptr, image1_ptr)) {
    // print morph steps for debugging
    #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%d.bmp", step++);
      binary_to_BMP(image1_ptr, debug_image);
      write_bitmap(debug_image, buffer);
    #endif

    // Step 5 and 6: Detect cells and generate output image
    detect_cells(image1_ptr, input_image, &cellCount, false);

    // Swap ptr for the intermedia images
    tmp_ptr = image0_ptr;
    image0_ptr = image1_ptr;
    image1_ptr= tmp_ptr;
  }

  printf("\tA total of %d %s detected.\n", cellCount, cellCount == 1 ? "cell was" : "cells were");

  // Step 7: Save output image and print results
  write_bitmap(input_image, argv[2]);

  printf("Done!\n");
  return 0;
}

