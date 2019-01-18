#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "a4.h"

void mutate(Individual *individual, double rate)
{
  int n = individual->image.width * individual->image.height;
  //run loop rate/100*n times and choose random PIXELs
  int endBound = (int)(rate/100*n);
  int i;
  for (i = 0; i < endBound; i++) {
    //generate a random number between 0 and n
    int pixelNum = rand();
    pixelNum = rand() % n;
    // generate random colour data
	int j;
    for (j = 0; j < 3; j++) {
      int randColour = rand();
      randColour = rand() % (individual->image.max_color + 1);
      if (j == 0) individual->image.data[pixelNum].r = randColour;
      if (j == 1) individual->image.data[pixelNum].g = randColour;
      if (j == 2) individual->image.data[pixelNum].b = randColour;
    }
  }
}

void mutate_population(Individual *individual, int population_size, double rate)
{
  int index = population_size/4;
  int i;
  for (i = index; i < population_size; i++) {
    mutate((individual+i), rate);
  }
}
