/*
Cell counting program - Ass1
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

#include "cbmp.h"

// TODO: add morph enum for erode and dilation here:)

unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char binary_image[BMP_WIDTH][BMP_HEIGTH];
unsigned char intermedia_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char test_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

void create_binary(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH]);
void create_binary_image(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);
bool is_on_edge(int x, int y, int width, int height);
void morph();
bool erode(); 
bool erode_image(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);
bool dilation();
void draw_x(int x, int y);
void count_cells();



int main(int argc, char** argv) {
  //argc counts how may arguments are passed
  //argv[0] is a string with the name of the program
  //argv[1] is the first command line argument (input image)
  //argv[2] is the second command line argument (output image)

  //Checking that 2 arguments are passed
  if (argc != 3) {
      fprintf(stderr, "Usage: %s <input file path> <output file path>\n", argv[0]);
      exit(1);
  }

  printf("Cell detection program - 02132 - Ass1\n");

  read_bitmap(argv[1], input_image);

  create_binary_image(input_image, intermedia_image);

  //write_bitmap(intermedia_image, argv[2]);



  //erode(binary_image, output_image);

  // create_binary_image(input_image, intermedia_image);

  //erode_image(binary_image, intermedia_image);

  // while(1) {
  //   if (!erode())
  //     break;
  //
  //   detect cells
  // }


  erode_image(intermedia_image, output_image);

  erode_image(output_image, intermedia_image);
  erode_image(intermedia_image, output_image);
  erode_image(output_image, intermedia_image);
  //erode_image(intermedia_image, output_image);
  //erode_image(intermedia_image, output_image);
  

  write_bitmap(intermedia_image, argv[2]);

  printf("Done!\n");
  return 0;
}



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
          output_image[x][y][0] = 255;
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

void draw_x(int x, int y) {

}

void count_cells() {

}