#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "a4.h"

double square(double num)
{
  return num*num;
}

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size)
{
  double sumDistance = 0;
  int i;
  for (i = 0; i < image_size; i++) {
    double distance = square(A[i].r - B[i].r) + square(A[i].g - B[i].g) + square(A[i].b - B[i].b);
    sumDistance += distance;
  }
  return sqrt(sumDistance);
}

void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size){
  int i;
  for (i = 0; i < population_size; i++) {
    individual[i].fitness = comp_distance(image, individual[i].image.data, individual[i].image.width * individual[i].image.height);
  }
}
