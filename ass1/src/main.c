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

typedef enum {
  erosion,
  dilation,
  opening,
  closing
} Morph_OP;

// TODO: add morph enum for erode and dilation, or opening / closing here:)
// TODO: add enum for drawing:)

unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
#if DEBUG
  unsigned char debug_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  char c;
#endif
unsigned char intermedia_image0[BMP_WIDTH][BMP_HEIGTH];
unsigned char intermedia_image1[BMP_WIDTH][BMP_HEIGTH];
unsigned char (*image0_ptr)[BMP_HEIGTH] = intermedia_image0;
unsigned char (*image1_ptr)[BMP_HEIGTH] = intermedia_image1;
unsigned char (*tmp_ptr)[BMP_HEIGTH];

int step = 0;
int cellCount = 0; 
char buffer[50];

int x_lower = 0;
int x_upper = BMP_WIDTH;
int y_lower = 0;
int y_upper = BMP_HEIGTH; 

unsigned char struct_elem3[3][3] = {{0,1,0},
                                    {1,1,1},
                                    {0,1,0}};
    
unsigned char struct_elem5[5][5] = {{0,1,1,1,0},
                                    {1,1,1,1,1},
                                    {1,1,1,1,1},
                                    {1,1,1,1,1},
                                    {0,1,1,1,0}};

unsigned char struct_elem7[7][7] = {{0,0,1,1,1,0,0},
                                    {0,1,1,1,1,1,0},
                                    {1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1},
                                    {0,1,1,1,1,1,0},
                                    {0,0,1,1,1,0,0}};

unsigned char struct_elem9[9][9] = {{0,0,0,1,1,1,0,0,0},
                                    {0,0,1,1,1,1,1,0,0},
                                    {0,1,1,1,1,1,1,1,0},
                                    {1,1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1,1},
                                    {0,1,1,1,1,1,1,1,0},
                                    {0,0,1,1,1,1,1,0,0},
                                    {0,0,0,1,1,1,0,0,0}};                                    

unsigned char struct_elem11[11][11] = {{0,0,0,0,1,1,1,0,0,0,0},
                                       {0,0,0,1,1,1,1,1,0,0,0},
                                       {0,0,1,1,1,1,1,1,1,0,0},
                                       {0,1,1,1,1,1,1,1,1,1,0},
                                       {1,1,1,1,1,1,1,1,1,1,1},
                                       {1,1,1,1,1,1,1,1,1,1,1},
                                       {1,1,1,1,1,1,1,1,1,1,1},
                                       {0,1,1,1,1,1,1,1,1,1,0},
                                       {0,0,1,1,1,1,1,1,1,0,0},
                                       {0,0,0,1,1,1,1,1,0,0,0},
                                       {0,0,0,0,1,1,1,0,0,0,0}}; 

unsigned char struct_elem13[13][13] = {{0,0,0,0,1,1,1,1,1,0,0,0,0},
                                       {0,0,0,1,1,1,1,1,1,1,0,0,0},
                                       {0,0,1,1,1,1,1,1,1,1,1,0,0},
                                       {0,1,1,1,1,1,1,1,1,1,1,1,0},
                                       {1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       {1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       {1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       {1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       {1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       {0,1,1,1,1,1,1,1,1,1,1,1,0},
                                       {0,0,1,1,1,1,1,1,1,1,1,0,0},
                                       {0,0,0,1,1,1,1,1,1,1,0,0,0},
                                       {0,0,0,0,1,1,1,1,1,0,0,0,0}};  

#define KERSIZE 9


void create_otsu_binary(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char binary[BMP_WIDTH][BMP_HEIGTH]) {
  unsigned histogram[256] = {0};
  unsigned char grayVal;
  int max_intensity = 256;
  int threshold = 0;
  int N = BMP_WIDTH * BMP_HEIGTH;
  int omega_b, omega_f = 0;
  float mu_b, mu_f, mu_diff, sum, sumB, inter_var, var_max = 0.0f;

  for (int x = 0; x < BMP_WIDTH; ++x)
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      grayVal = (unsigned char) (0.299 * in_image[x][y][0] + 0.587 * in_image[x][y][1] + 0.114 * in_image[x][y][2]);
      //grayVal = (in_image[x][y][0] + in_image[x][y][1] + in_image[x][y][2]) / 3;
      ++histogram[grayVal];
    }

  for (int i = 0; i < max_intensity; ++i)
    sum += i * ((int)histogram[i]);

  for (int t = 0; t < max_intensity; ++t) {
    // update omega values
    omega_b += histogram[t];
    if (omega_b == 0)
      continue;

    omega_f = N - omega_b;
    if (omega_f == 0)
      break;

    // update mu values
    sumB += (float) (t * ((int)histogram[t]));
    mu_b = sumB / omega_b;
    mu_f = (sum - sumB) / omega_f;

    // update inter-class var
    mu_diff = mu_b - mu_f;
    inter_var = (float) omega_b * (float) omega_f * (mu_diff * mu_diff);

    // update threshold
    if (inter_var > var_max) {
      threshold = t;
      var_max = inter_var;
    }
  }

  for (int x = 0; x < BMP_WIDTH; ++x)
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      grayVal = (unsigned char) (0.299 * in_image[x][y][0] + 0.587 * in_image[x][y][1] + 0.114 * in_image[x][y][2]);
      //grayVal = (in_image[x][y][0] + in_image[x][y][1] + in_image[x][y][2]) / 3;
      binary[x][y] = grayVal > threshold - 7.5 ? 1 : 0;
    }

  #if DEBUG
    printf("t: %d\n", threshold);
  #endif

}

bool erode(unsigned char in_binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_binary[BMP_WIDTH][BMP_HEIGTH], unsigned char kernelSize) {
  unsigned char halfSize = kernelSize >> 1;
  

  bool wasEroded = false;
  bool erodePixel = false;


  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {

      // Should only erode if the pixel is white; skip black
      if (in_binary[x][y] == 0) {
        out_binary[x][y] = 0;
        continue;
      }

      // Erode edge pixels
      if (x == 0 || y == 0 || x == BMP_WIDTH - 1 || y == BMP_HEIGTH - 1) {
        out_binary[x][y] = 0;
        continue;
      }

      // Iterate over the struct_elem
      erodePixel = false; 
      for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
          // Should the structing be out of bounds, assume 1 by skipping (continue) for the part that overflows
          if (x + i - halfSize < 0 || x + i - halfSize >= BMP_WIDTH || y + j - halfSize < 0 || y + j - halfSize >= BMP_HEIGTH)
            continue;

          if (kernelSize == 3)
            if (struct_elem3[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }

          if (kernelSize == 5)
            if (struct_elem5[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }

          if (kernelSize == 7)
            if (struct_elem7[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }

          if (kernelSize == 9)
            if (struct_elem9[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }
          
          if (kernelSize == 11)
            if (struct_elem11[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }
        }
        if (erodePixel)
          break;
      }

      if (erodePixel) {
        out_binary[x][y] = 0;
        wasEroded = true;
      } else {
        out_binary[x][y] = 1;
      }
    }
  }

  return wasEroded; 
}

bool dilate(unsigned char in_binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_binary[BMP_WIDTH][BMP_HEIGTH], int kernelSize) {
  unsigned char halfSize = kernelSize >> 1;
  
  
  bool dilatePixel = false;
  bool wasDilated = false; 
  
  
  
  for (int x = 0; x < BMP_WIDTH; ++x) {
    for (int y = 0; y < BMP_HEIGTH; ++y) {

      // Should only dialte if the pixel is black; skip white
      if (in_binary[x][y] == 1) {
        out_binary[x][y] = 1;
        continue;
      }

      // Erode edge pixels for the detection frame to work; yes even in dilation
      if (x == 0 || y == 0 || x == BMP_WIDTH - 1 || y == BMP_HEIGTH - 1) {
        out_binary[x][y] = 0;
        continue;
      }

      // Iterate over the struct_elem
      dilatePixel = false; 
      for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
          // Should the structing be out of bounds, assume 0 by skipping (continue) for the part that overflows
          if (x + i - halfSize < 0 || x + i - halfSize >= BMP_WIDTH || y + j - halfSize < 0 || y + j - halfSize >= BMP_HEIGTH)
            continue;

          if (kernelSize == 3)
            if (struct_elem3[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }

          if (kernelSize == 5)
            if (struct_elem5[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }

          if (kernelSize == 7)
            if (struct_elem5[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }

          if (kernelSize == 9)
            if (struct_elem9[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }

          if (kernelSize == 11)
            if (struct_elem11[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              // TODO: consider using goto here, instead of dbl break
              break; 
            }
        }
        if (dilatePixel)
          break;
      }

      if (dilatePixel) {
        out_binary[x][y] = 1;
        wasDilated = true;
      } else {
        out_binary[x][y] = 0;
      }
    }
  }

  return wasDilated;
}

bool morpher_I_barely_know_her(unsigned char in_binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_binary[BMP_WIDTH][BMP_HEIGTH], Morph_OP op, unsigned char kernelSize) {
  bool wasEroded;
  bool wasDilated;

  switch (op) {
    case erosion:
      return erode(in_binary, out_binary, kernelSize);
      break;

    case dilation: 
      return dilate(in_binary, out_binary, kernelSize);
      break; 

    case opening:
      wasEroded = erode(in_binary, out_binary, kernelSize);
      wasDilated = dilate(out_binary, in_binary, kernelSize);
      // Make the out_binary point to the in_binary image
      out_binary = in_binary;
      return wasEroded || wasDilated;
      break;

    case closing:
      wasDilated = dilate(in_binary, out_binary, kernelSize);
      wasEroded = erode(out_binary, in_binary, kernelSize);
      // Make the out_binary point to the in_binary image
      out_binary = in_binary;
      return wasDilated || wasEroded;
      break; 

    default:
      fprintf(stderr, "Unknown morph operation!");
      exit(1);
      break;
  }
};

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

  return true; 
}

bool cell_detected(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], int x, int y, int capAreaWidth) {
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j)
      if (binary[x + i][y + j] == 1)
        return true;

  return false;
}

void draw_detection_indication(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int offset) {
  // TODO: Fix all the offset bs
  // COULDVE: Do option for getting the silhoutte of the binary cell 

  int detection_indication[13][10] = {{0,1,0,0,0,0,0,0,0,0},
                                      {0,1,1,0,0,0,1,1,1,0},
                                      {0,1,1,1,0,0,0,0,1,0},
                                      {0,1,1,1,0,0,0,0,1,0},
                                      {0,1,1,0,0,0,0,0,1,0},
                                      {0,1,0,0,0,0,0,0,1,0},
                                      {0,1,1,1,1,1,1,0,1,0},
                                      {0,1,0,0,0,0,1,0,1,0},
                                      {0,1,1,0,0,0,1,0,1,0},
                                      {0,1,1,1,0,0,0,0,1,0},
                                      {0,1,1,1,0,0,0,0,1,0},
                                      {0,1,1,0,0,0,1,1,1,0},
                                      {0,1,0,0,0,0,0,0,0,0}}; 
  
  for (int i = 0; i < 13; ++i)
    for (int j = 0; j < 10; ++j)
      if (detection_indication[i][j] == 1) {
        image[x + offset + i][y + offset + 3 + j][0] = 255;
        image[x + offset + i][y + offset + 3 + j][1] = 0;
        image[x + offset + i][y + offset + 3 + j][2] = 0;
      }

}

void remove_cell(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], int x, int y, int capAreaWidth) {
  // TODO: Merge this with detect thing
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j)
      // Only color black if white
      //if (binary[x + i][y + j] == 1)
        binary[x + i][y + j] = 0;

}

void detect_cells(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int* cellCount, bool printCoords) {
  int capWidth = 15;
  int frameWidth = 1;
  /*unsigned char kernel[21][21] = {{2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
                                  {2,2,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,2,2},
                                  {2,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,2},
                                  {2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                                  {2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2},
                                  {2,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,2},
                                  {2,2,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,2,2},
                                  {2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},};
  */

  // TODO: Is extracting conditions faster than having them present in the loop?
  for (int x = 0; x < BMP_WIDTH - (capWidth + frameWidth); ++x)
    for (int y = 0; y < BMP_WIDTH - (capWidth + frameWidth); ++y)
      if (detection_frame_clear(binary, x, y, capWidth + (frameWidth << 1)))
        if (cell_detected(binary, x, y, capWidth)) {
          draw_detection_indication(out_image, x, y, capWidth >> 2);
          remove_cell(binary, x, y, capWidth);
          ++*cellCount;
          if (printCoords)
            printf("\tcell #%d: (%d, %d)\n", *cellCount, x + capWidth >> 1, y + capWidth >> 1);
        }

}

#if DEBUG
  void binary_to_BMP(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char BMP[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
    for (int x = 0; x < BMP_WIDTH; ++x)
      for (int y = 0; y < BMP_HEIGTH; ++y)
        //if (binary[x][y] != 2) {
          for (int c = 0; c < BMP_CHANNELS; ++c)
            if (binary[x][y] == 1)
              BMP[x][y][c] = 255;
            else 
              BMP[x][y][c] = 0;
        //}
        //else {
          //BMP[x][y][0] = 255;
          //BMP[x][y][1] = 0;
          //BMP[x][y][2] = 0;
        //}

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
  // OpStep: Calculate threshold using Otsu's method.
  create_otsu_binary(input_image, image0_ptr);

  printf("Cell detection results:\n");

  // Output binary step for debugging
  #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%db.bmp", step++);
      binary_to_BMP(image0_ptr, debug_image);
      write_bitmap(debug_image, buffer);
  #endif

  // OpStep: Use the morphology operation opening and closing
  morpher_I_barely_know_her(image0_ptr, image1_ptr, opening, KERSIZE);
  morpher_I_barely_know_her(image1_ptr, image0_ptr, closing, KERSIZE);

  // Output opening step for debugging
  #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%docm.bmp", step++);
      binary_to_BMP(image0_ptr, debug_image);
      write_bitmap(debug_image, buffer);
  #endif

  return 0; 

  // Main steps of algo
  while(morpher_I_barely_know_her(image1_ptr, image0_ptr, opening, KERSIZE)) {
    // Output morph steps for debugging
    #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%dom.bmp", step++);
      binary_to_BMP(image0_ptr, debug_image);
      write_bitmap(debug_image, buffer);
    #endif

    // Step 5 and 6: Detect cells and generate output image
    detect_cells(image0_ptr, input_image, &cellCount, false);

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

