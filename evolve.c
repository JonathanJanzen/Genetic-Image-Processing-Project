#include <stdio.h>
#include <stdlib.h>
#include "a4.h"
#include <time.h>

static int cmpfunc(const void *a, const void *b)
{
  return (int) (((Individual *)a)->fitness - ((Individual *)b)->fitness);
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate)
{
  srand(time(0));
  Individual *population;
  population = generate_population(population_size, image->width, image->height, image->max_color);
  PIXEL *sample = image->data;
  comp_fitness_population(sample, population, population_size);
  qsort(population, population_size, sizeof(Individual), cmpfunc);
  int i;
  for (i = 0; i < num_generations; i++) {
    crossover(population, population_size);
    mutate_population(population, population_size, rate);
    comp_fitness_population(sample, population, population_size);
    qsort(population, population_size, sizeof(Individual), cmpfunc);
    /*below code was used to create images for video and display current iteration to console*/
    /*printf("%d Fitness: %lf\n", i, population[0].fitness);
    if (i % 50 == 0) {
      int num = i/50;
      char name[6];
      sprintf(name, "%d", num);
      write_ppm(name, &population[0].image);
    }*/
  }
  //create return pointer
  PPM_IMAGE *returnImage;
  returnImage = malloc(sizeof(PPM_IMAGE));
  returnImage = &population[0].image;
  /*free generated population data*/
  int j;
  for (j = 1; j < population_size; j++) {
    free((population+j)->image.data);
  }
  return returnImage;
}

void free_image(PPM_IMAGE *p)
{
  free(p->data);
  free(p);
}
