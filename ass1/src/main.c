/*
Cell counting program - Ass1
*/

#define DEBUG 0

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "cbmp.h"



// Morphological operations
typedef enum {
  erosion,
  dilation,
  opening,
  closing
} Morph_OP;



// Initializing variables
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
#if DEBUG
  unsigned char debug_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  char c;
#endif
// TODO: compress? :)
unsigned char intermedia_image0[BMP_WIDTH][BMP_HEIGTH];
unsigned char intermedia_image1[BMP_WIDTH][BMP_HEIGTH];
unsigned char (*image0_ptr)[BMP_HEIGTH] = intermedia_image0;
unsigned char (*image1_ptr)[BMP_HEIGTH] = intermedia_image1;
unsigned char (*tmp_ptr)[BMP_HEIGTH];

clock_t startAll, endAll, startBi, endBi, startErode, endErode, startDilation, endDilation,
  startOpening, endOpening, startClosing, endClosing, startDetectCells, endDetectCells;
double cpu_time_used, cpu_time_usedErode, cpu_time_usedDilation, cpu_time_usedOpening, cpu_time_usedClosing, cpu_time_usedDetection;

int step = 0;
int cellCount = 0; 
char buffer[50];
int x_lower = 0;
int x_upper = BMP_WIDTH;
int y_lower = 0;
int y_upper = BMP_HEIGTH; 



// Predefined structuring elements/kernels
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



// Converting 3D rgb to 2D binary image
void create_binary(unsigned char in_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char binary[BMP_WIDTH][BMP_HEIGTH]) {
  unsigned char grayVal;
  unsigned short threshold = 94;

  for (int x = 0; x < BMP_WIDTH; ++x)
    for (int y = 0; y < BMP_HEIGTH; ++y) {
      //grayVal = (in_image[x][y][0] + in_image[x][y][1] + in_image[x][y][2]) / 3;
      grayVal = (0.299 * in_image[x][y][0] + 0.587 * in_image[x][y][1] + 0.114 * in_image[x][y][2]);
      binary[x][y] = grayVal > threshold ? 1 : 0;
    }

}

// Implementation of Otsu (not used)
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

// Loops through matrices and checks wether pixels are 1 or 0, if 1 --> overlay the structuring element and decide if the pixel should be eroded
// Returns true if a pixel was eroded
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

// Opposite of erosion, if pixel of interest is black, and the surrounding pixel match the structuring elements, pixelvalue changes from 0 to 1
// Returns true if a dilation occurs
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

// Storing the new eroded and dilated image as a binary image
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
      startOpening = clock();
      startErode = clock();

      wasEroded = erode(binary_1, binary_2, kernelSize);
      
      endErode = clock();
      startDilation = clock();

      wasDilated = dilate(binary_2, binary_1, kernelSize);
      
      endDilation = clock();
      endOpening = clock();

      cpu_time_usedErode += endErode - startErode;
      cpu_time_usedDilation += endDilation - startDilation;
      cpu_time_usedOpening += endOpening - startOpening;  

      // Make the binary_2 point to the binary_1 image
      binary_2 = binary_1;
      return wasEroded || wasDilated;
      break;

    case closing:
      startClosing = clock();

      startDilation = clock();
      wasDilated = dilate(binary_1, binary_2, kernelSize);
      endDilation = clock();

      startErode = clock();
      wasEroded = erode(binary_2, binary_1, kernelSize);
      endErode = clock();

      endClosing = clock();

      cpu_time_usedErode += endErode - startErode;
      cpu_time_usedDilation += endDilation - startDilation;
      cpu_time_usedClosing += endClosing - startClosing; 

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

// Checks if the frame surrounding the caption area is clear of white pixels, and returns true if none is found 
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

// Looks for white pixels in caption area
// Return true if cell is detected
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

// Draw indicator over a detected cell in the output image
void draw_detection_indication(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, int offset) {
  unsigned char detection_indication[13][10] = {{0,1,0,0,0,0,0,0,0,0},
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

// Runs through the image, and calls the functions detection_frame_clear, cell_detected_and_removed and draw_detection_indication
// Printing cell location coordinates
// And shrinks the image to fit the remaining cells 
void detect_cells(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char out_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int* cellCount, bool printCoords) {
  int cap_width = 15;
  int frame_width = 1;

  for (int x = 0; x < BMP_WIDTH - (cap_width + 1); ++x)
    for (int y = 0; y < BMP_HEIGTH - (cap_width + 1); ++y)
      if (detection_frame_clear(binary, x, y, cap_width + (frame_width << 1))) 
        if (cell_detected_and_removed(binary, x, y, cap_width)) {
          draw_detection_indication(out_image, x, y, cap_width >> 2);
          ++*cellCount;
          if (printCoords)  
            printf("\tcell #%d: (%d, %d)\n", *cellCount, x + (cap_width >> 1), y + (cap_width >> 1));
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

  void RGB_to_GRAYSCALE(unsigned char BMP[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char grayscale[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
    unsigned char grayVal;
  
    for (int x = 0; x < BMP_WIDTH; ++x)
      for (int y = 0; y < BMP_HEIGTH; ++y) {
        //grayVal = (unsigned char) (0.299 * BMP[x][y][0] + 0.587 * BMP[x][y][1] + 0.114 * BMP[x][y][2]);
        grayVal = (unsigned char) (BMP[x][y][0] + BMP[x][y][1] + BMP[x][y][2]) / 3;
        for (int c = 0; c < BMP_CHANNELS; ++c)
          grayscale[x][y][c] = grayVal;
      }

  }
#endif



int main(int argc, char** argv) {

  if (argc != 3) {
      fprintf(stderr, "Usage: %s <input file path> <output file path>\n", argv[0]);
      exit(1);
  }

  printf("Cell detection program - 02132 - Ass1\n");

  startAll = clock();
  // Step 1: Load input image
  read_bitmap(argv[1], input_image);
  
  #if DEBUG
    RGB_to_GRAYSCALE(input_image, debug_image);
    write_bitmap(debug_image, argv[2]);
  #endif

  // Step 2 and 3: Convert from RGB to GrayScale and apply the binary threshold to create a binary image
  // OpStep: Calculate threshold using Otsu's method.
  // create_otsu_binary(input_image, image0_ptr);
  startBi = clock();
  //create_otsu_binary(input_image, image0_ptr);
  create_binary(input_image, image0_ptr);
  endBi = clock();

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

  startDetectCells = clock();
  detect_cells(image0_ptr, input_image, &cellCount, false);
  endDetectCells = clock();
  
  cpu_time_usedDetection += endDetectCells - startDetectCells;

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
    startDetectCells = clock();
    detect_cells(image1_ptr, input_image, &cellCount, false);
    endDetectCells = clock();

    cpu_time_usedDetection += endDetectCells - startDetectCells;

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



  endAll = clock();
  cpu_time_used = endBi - startBi;
  printf("Binary time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);
  printf("Erosion time: %f ms\n", cpu_time_usedErode * 1000.0 / CLOCKS_PER_SEC);
  printf("Dilation time: %f ms\n", cpu_time_usedDilation * 1000.0 / CLOCKS_PER_SEC);
  printf("Opening time: %f ms\n", cpu_time_usedOpening * 1000.0 / CLOCKS_PER_SEC);
  printf("Closing time: %f ms\n", cpu_time_usedClosing * 1000.0 / CLOCKS_PER_SEC);
  printf("Detection time: %f ms\n", cpu_time_usedDetection * 1000.0 / CLOCKS_PER_SEC);
  cpu_time_used = endAll - startAll;
  printf("Total time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);



  printf("Done!\n");

  return 0;
}

