/*
Cell counting program - Ass1
*/
#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "cbmp.h"

// TODO: add morph enum for erode and dilation here:)
// TODO: add enum for drawing:)

unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

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

void draw_detection_indication(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int totalWidth) {
  int detection_indication[13][13] = {{0,0,1,0,0,0,0,0,0,0,0,0,0},
                                      {0,0,1,1,0,0,0,1,1,1,0,0,0},
                                      {0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,1,1,0,0,0,0,0,1,0,0,0},
                                      {0,0,1,0,0,0,0,0,0,1,0,0,0},
                                      {0,0,1,1,1,1,1,1,0,1,0,0,0},
                                      {0,0,1,0,0,0,0,1,0,1,0,0,0},
                                      {0,0,1,1,0,0,0,1,0,1,0,0,0},
                                      {0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,1,1,1,0,0,0,0,1,0,0,0},
                                      {0,0,1,1,0,0,0,1,1,1,0,0,0},
                                      {0,0,1,0,0,0,0,0,0,0,0,0,0},}; 
  
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


// preprocess
#if DEBUG


unsigned char intermedia_image0[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char intermedia_image1[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char (*image0_ptr)[BMP_HEIGTH][BMP_CHANNELS] = intermedia_image0;
unsigned char (*image1_ptr)[BMP_HEIGTH][BMP_CHANNELS] = intermedia_image1;
unsigned char (*tmp_ptr)[BMP_HEIGTH][BMP_CHANNELS];

void create_binary_image(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      int avg = (input_image[x][y][0] + input_image[x][y][1] + input_image[x][y][2]);
      for (int c = 0; c < BMP_CHANNELS; ++c) {
        output_image[x][y][c] = avg > 270 ? 255 : 0;
      }
    }
  }
}

bool erode_image(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char out_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
  unsigned char structing_element[3][3] = {{0,1,0},{1,1,1},{0,1,0}};
  bool wasEroded = false;
  bool erodePixel;

  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {

      // Should only erode if the pixel is white
      if (in_image[x][y][0] == 0) {
        out_image[x][y][0] = in_image[x][y][0];
        out_image[x][y][1] = in_image[x][y][1];
        out_image[x][y][2] = in_image[x][y][2];
        continue;
      }

      erodePixel = false;
      if (is_on_edge(x, y, BMP_WIDTH, BMP_HEIGTH)) {
        if (in_image[x][y][0] == 255)
          erodePixel = true;
      } else {
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j)
            if (structing_element[i][j] == 1 && in_image[x + i - 1][y + j - 1][0] == 0) {
              erodePixel = true;
              // TODO: consider using <goto> here so you don't need to break twice
              break;
            }
          if (erodePixel)
            break;
        }
      }

      if (erodePixel) {
        out_image[x][y][0] = 0;
        out_image[x][y][1] = 0;
        out_image[x][y][2] = 0;
        wasEroded = true;
      } else {
        out_image[x][y][0] = in_image[x][y][0];
        out_image[x][y][1] = in_image[x][y][1];
        out_image[x][y][2] = in_image[x][y][2];
      }
    }
  }

  return wasEroded; 
}

bool detection_frame_clear_image(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int totalWidth) {
  for (int i = 0; i < totalWidth; ++i)
    for (int j = 0; j < totalWidth; ++j)
      if (i == 0 || i == totalWidth - 1 || j == 0 || j == totalWidth - 1)
        if (image[x + i][y + j][0] == 255)
          return false;

  return true; 
}

bool cell_detected_image(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int capAreaWidth) {
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j)
      if (image[x + i][y + j][0] == 255)
        return true;

  return false; 
}

void remove_cell_image(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int capAreaWidth) {
  // TODO: maybe only color white parts of the image; there's no need to color black pixels black
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j) {
      image[x + i][y + j][0] = 0;
      image[x + i][y + j][1] = 0;
      image[x + i][y + j][2] = 0;
    }
}

void detect_cells(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char out_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int* cellCount, bool printCoords) {
  // TODO: we assume that the erosion erases the border pixels of the image
  int frameWidth = 1 * 2;
  int capAreaWidth = 12; 
  // TODO: Maybe change the capture area to be 2d array

  for (int x = 0; x < BMP_WIDTH - capAreaWidth; ++x)
    for (int y = 0; y < BMP_WIDTH - capAreaWidth; ++y)
      
      if (detection_frame_clear_image(in_image, x, y, capAreaWidth + frameWidth))
        if (cell_detected_image(in_image, x, y, capAreaWidth)) {
          draw_detection_indication(out_image, x, y, capAreaWidth + frameWidth);
          remove_cell_image(in_image, x, y, capAreaWidth);
          ++*cellCount;
          if (printCoords)
            // TODO: modify this to be the center
            printf("\tcell #%d: (%d, %d)\n", *cellCount, x, y);
        }
}


#else


unsigned char intermedia_image0[BMP_WIDTH][BMP_HEIGTH];
unsigned char intermedia_image1[BMP_WIDTH][BMP_HEIGTH];
unsigned char (*image0_ptr)[BMP_HEIGTH] = intermedia_image0;
unsigned char (*image1_ptr)[BMP_HEIGTH] = intermedia_image1;
unsigned char (*tmp_ptr)[BMP_HEIGTH];

void create_binary(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH]) {
  for (int x = 0; x < BMP_WIDTH; ++x) {
      for (int y = 0; y < BMP_HEIGTH; ++y) {
          // TODO: otsu metode???
          int avg = (input_image[x][y][0] + input_image[x][y][1] + input_image[x][y][2]);
          output_image[x][y] = avg > 270 ? 255 : 0;
      }
  } 
    
}


#endif



int main(int argc, char** argv) {

  if (argc != 3) {
      fprintf(stderr, "Usage: %s <input file path> <output file path>\n", argv[0]);
      exit(1);
  }

  printf("Cell detection program - 02132 - Ass1\n");

  // Step 1: Load input image
  read_bitmap(argv[1], input_image);
  
  // Step 2 and 3: Convert from RGB to GrayScale and apply the binary threshold to create a binary image
  create_binary_image(input_image, image0_ptr);

  // TODO: Why erode the image first? Shouldn't we detect the cells we can and then erode? or are we trying to get rid of noise? 
  // Step 4: Erode the binary image
  printf("Cell detection results:\n");


  // TODO: MAKE THE DETECITON FRAME TRUE 


  while(erode_image(image0_ptr, image1_ptr)) {
    // print steps for debugging
    if (DEBUG) {
      snprintf(buffer, sizeof buffer, "./debug/step_%d", step++);
      write_bitmap(image1_ptr, buffer);
    }

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

