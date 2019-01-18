#include <stdio.h>
#include <stdlib.h>
#include "a4.h"

PPM_IMAGE *read_ppm(const char *file_name){
  /*reads a PPM image file, returns pointer to PPM_IMAGE struct containing pixels of image, width, height and max color*/
  char magicNum[3];
  int width, height, maxColor;
  FILE *tempFile;
  tempFile = fopen(file_name, "r");
  if (!tempFile) {
    fprintf(stderr, "Unable to open '%s'\n", file_name);
    exit (1);
  }
  fscanf(tempFile, "%s %d %d %d", magicNum, &width, &height, &maxColor);
  PPM_IMAGE *returnImage;
  returnImage = (PPM_IMAGE *)malloc(sizeof(PPM_IMAGE));
  if (!returnImage) {
    fprintf(stderr, "Unable to allocate memory.\n");
    exit(1);
  }
  //set data
  returnImage->width = width;
  returnImage->height = height;
  returnImage->max_color = maxColor;
  //create array for pixelData
  PIXEL *mainData;
  mainData = malloc(sizeof(PIXEL)*width*height);
  int range = width*height*3;
  /*scan through file for all pixel information and set relevant data*/
  int i;
  for (i = 0; i < range; i++) {
    fscanf(tempFile, "%hhu %hhu %hhu", &(mainData[i].r), &(mainData[i].g), &(mainData[i].b));
  }
  returnImage->data = mainData;
  fclose(tempFile);
  return returnImage;
}
void write_ppm(const char *file_name, const PPM_IMAGE *image)
{
  FILE *final;
  //open for output
  final = fopen(file_name, "wb");
  if (!final) {
    printf("Could not open '%s'\n", file_name);
    exit(1);
  }
  int width = image->width, height = image->height;
  int range = width*height;
  //write header info
  fprintf(final, "P3\n");
  fprintf(final, "%d %d\n", width, height);
  fprintf(final, "%d\n", image->max_color);
  int i;
  for (i = 0; i < range; i++) {
    if ((i+1) % width == 0) fprintf(final, "\n");
    fprintf(final, "%u %u %u ", image->data[i].r, image->data[i].g, image->data[i].b);
  }
  fclose(final);
}
