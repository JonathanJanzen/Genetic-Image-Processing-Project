#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "a4.h"
#include <limits.h>

PIXEL *generate_random_image(int width, int height, int max_color)
{
  int len = width*height;
  PIXEL *dataArray = (PIXEL *)malloc(sizeof(PIXEL)*len);
  int i;
  for (i = 0; i < len; i++) {
    (dataArray + i)->r = rand() % (max_color + 1);
    (dataArray + i)->g = rand() % (max_color + 1);
    (dataArray + i)->b = rand() % (max_color + 1);
  }
  return dataArray;
}

Individual *generate_population(int population_size, int width, int height, int max_color)
{
  Individual *returnArray = (Individual *)malloc(sizeof(Individual)*population_size);
  int i;
  for (i = 0; i < population_size; i++) {
    Individual *tempIndivid;
    tempIndivid = (Individual *)malloc(sizeof(Individual));
    tempIndivid->image.data = generate_random_image(width, height, max_color);
    tempIndivid->image.width = width;
    tempIndivid->image.height = height;
    tempIndivid->image.max_color = max_color;
    tempIndivid->fitness = 0;
    *(returnArray + i) = *tempIndivid;
    free(tempIndivid);
  }
  return returnArray;
}
