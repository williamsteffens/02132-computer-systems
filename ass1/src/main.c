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

typedef enum {
  erosion,
  dilation,
  opening,
  closing
} Morph_OP;


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


void create_binary(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char binary[BMP_WIDTH][BMP_HEIGTH]) {
  unsigned char grayVal;
  unsigned char threshold = 94;

  for (int x = 0; x < BMP_WIDTH; ++x)
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      grayVal = (unsigned char) (0.299 * in_image[x][y][0] + 0.587 * in_image[x][y][1] + 0.114 * in_image[x][y][2]);
      binary[x][y] = grayVal > threshold ? 1 : 0;
    }

}

void create_otsu_binary(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char binary[BMP_WIDTH][BMP_HEIGTH]) {
  unsigned histogram[256] = {0};
  unsigned char grayVal;
  unsigned char max_intensity = 255;
  unsigned char threshold = 0;
  int N = BMP_WIDTH * BMP_HEIGTH;
  int omega_b, omega_f = 0;
  float mu_b, mu_f, mu_diff, sum, sumB, inter_var, var_max = 0.0f;

  for (int x = 0; x <= BMP_WIDTH; ++x)
    for (int y = 0; y <= BMP_HEIGTH; ++y) {
      grayVal = (unsigned char) (0.2126 * in_image[x][y][0] + 0.7152 * in_image[x][y][1] + 0.0722 * in_image[x][y][2]);
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

  threshold -= 20;
  for (int x = 0; x <= BMP_WIDTH; ++x)
    for (int y = 0; y <= BMP_HEIGTH; ++y) {
      grayVal = (unsigned char) (0.2126 * in_image[x][y][0] + 0.7152 * in_image[x][y][1] + 0.0722 * in_image[x][y][2]);
      binary[x][y] = grayVal > threshold ? 1 : 0;
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
              break; 
            }

          if (kernelSize == 5)
            if (struct_elem5[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              break; 
            }

          if (kernelSize == 7)
            if (struct_elem7[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              break; 
            }

          if (kernelSize == 9)
            if (struct_elem9[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
              break; 
            }
          
          if (kernelSize == 11)
            if (struct_elem11[i][j] && !(in_binary[x + i - halfSize][y + j - halfSize])) {
              erodePixel = true;
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
              break; 
            }

          if (kernelSize == 5)
            if (struct_elem5[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              break; 
            }

          if (kernelSize == 7)
            if (struct_elem5[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              break; 
            }

          if (kernelSize == 9)
            if (struct_elem9[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
              break; 
            }

          if (kernelSize == 11)
            if (struct_elem11[i][j] && in_binary[x + i - halfSize][y + j - halfSize]) {
              dilatePixel = true;
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

bool morpher_I_barely_know_her(unsigned char binary_1[BMP_WIDTH][BMP_HEIGTH], unsigned char binary_2[BMP_WIDTH][BMP_HEIGTH], Morph_OP op, unsigned char kernelSize) {
  bool wasEroded;
  bool wasDilated;

  switch (op) {
    case erosion:
      return erode(binary_1, binary_2, kernelSize);
      break;

    case dilation: 
      return dilate(binary_1, binary_2, kernelSize);
      break; 

    case opening:
      wasEroded = erode(binary_1, binary_2, kernelSize);
      wasDilated = dilate(binary_2, binary_1, kernelSize);
      // Make the binary_2 point to the binary_1 image
      binary_2 = binary_1;
      return wasEroded || wasDilated;
      break;

    case closing:
      wasDilated = dilate(binary_1, binary_2, kernelSize);
      wasEroded = erode(binary_2, binary_1, kernelSize);
      // Make the binary_2 point to the binary_1 image
      binary_2 = binary_1;
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

bool cell_detected_and_removed(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], int x, int y, int capAreaWidth) {
  bool cellDetected = false;
  
  for (int i = 1; i <= capAreaWidth; ++i)
    for (int j = 1; j <= capAreaWidth; ++j)
      if (binary[x + i][y + j]) {
        cellDetected = true;
        binary[x + i][y + j] = 0;
      }

  return cellDetected;
}

void draw_detection_indication(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int offset) {
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

void detect_cells(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int* cellCount, bool printCoords) {
  int cap_width = 15;
  int frame_width = 1;

  int x_min = x_lower;
  int x_max = x_upper;
  bool x_clear_lower = true;
  bool x_clear_upper = true; 

  int y_min = y_upper;
  int y_max = y_lower;
  bool y_clear_lower = true;

  x_clear_lower = true;
  for (int x = x_lower; x < x_upper - (cap_width + 1); ++x) {
    x_clear_upper = true; 
    y_clear_lower = true;
    for (int y = y_lower; y < y_upper - (cap_width + 1); ++y) {
      if (detection_frame_clear(binary, x, y, cap_width + (frame_width << 1))) {
        if (cell_detected_and_removed(binary, x, y, cap_width)) {
          draw_detection_indication(out_image, x, y, cap_width >> 2);
          ++*cellCount;
          if (printCoords)  
            printf("\tcell #%d: (%d, %d)\n", *cellCount, x + (cap_width >> 1), y + (cap_width >> 1));
        }
      } else {
        x_clear_lower = false;
        x_clear_upper = false; 
        y_clear_lower = false;

        if (y > y_max && y > y_min) {
          y_max = y;
          #if DEBUG
            out_image[x][y][1] = 255;
            out_image[x][y][2] = 255;
          #endif    
        }
      }

      if (!y_clear_lower && y < y_min) {
        y_min = y;
        #if DEBUG
          out_image[x][y][0] = 255;
          out_image[x][y][2] = 255;
        #endif
      }
    }

    if (x_clear_lower) {
      ++x_min;
      #if DEBUG
        out_image[x_min][0][1] = 255; 
      #endif  
    }

    if (!x_clear_upper && x > x_min) {
      x_max = x;
    }
  }

  #if DEBUG
    out_image[x_max][0][2] = 255;
  #endif

  x_lower = x_min;
  x_upper = x_max + cap_width + 2;;

  y_lower = y_min;
  y_upper = y_max + cap_width + 2; 

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
  // create_otsu_binary(input_image, image0_ptr);
  create_binary(input_image, image0_ptr);

  printf("Cell detection results:\n");

  // Output binary step for debugging
  #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%db.bmp", step++);
      binary_to_BMP(image0_ptr, debug_image);
      write_bitmap(debug_image, buffer);
  #endif

  // OpStep: Use the morphology operation opening and closing
  morpher_I_barely_know_her(image0_ptr, image1_ptr, opening, 9);
  morpher_I_barely_know_her(image1_ptr, image0_ptr, closing, 9);

  // Output opening and closing step for debugging
  #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%docm.bmp", step++);
      binary_to_BMP(image0_ptr, debug_image);
      write_bitmap(debug_image, buffer);
  #endif

  detect_cells(image0_ptr, input_image, &cellCount, false);

  // Output first detection step for debugging
  #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%docCount.bmp", step++);
      binary_to_BMP(image0_ptr, debug_image);
      write_bitmap(debug_image, buffer);
  #endif

  unsigned char kernelSize = 9; 

  // Main steps of algo
  while(morpher_I_barely_know_her(image0_ptr, image1_ptr, opening, kernelSize)) {
    // Output morph steps for debugging
    #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug/step_%dom.bmp", step++);
      binary_to_BMP(image1_ptr, debug_image);
      write_bitmap(debug_image, buffer);
    #endif

    // Step 5 and 6: Detect cells and generate output image
    detect_cells(image1_ptr, input_image, &cellCount, false);

    // Output steps on the final image
    #if DEBUG
      snprintf(buffer, sizeof buffer, "./debug2/step_%dfinal.bmp", step);
      write_bitmap(input_image, buffer);
    #endif

    // Dec the kernel size for morph
    if (kernelSize == 5)
      kernelSize = 3;
    
    if (kernelSize == 9)
      kernelSize = 5;

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

