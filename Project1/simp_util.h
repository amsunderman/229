#ifndef SIMP_UTIL
#define SIMP_UTIL

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

/*Structure used to represent a simp file*/
struct simp_file {
	int width;
	int height;
	int num_pixels;
	struct simp_pixel ** pixels;
	};

/*structure used to represent an individual pixel inside a simp file*/
struct simp_pixel {
	unsigned char red_value;
	unsigned char green_value;
	unsigned char blue_value;
	unsigned char alpha_value;
	};

/* Function used to read from file fp and store it in the simp_file structure simp_data */
int read_simp_file(FILE * fp, struct simp_file * simp_data);

/* Function used to write to file fp using the simp data from the provided simp_file structure */
int write_simp_file(FILE * fp, struct simp_file * simp_data);

/* Function used to modify simp_file structure with crop coordinates and dimensions */
int crop(struct simp_file * simp_data,struct simp_file * cropped, 
	int x, int y, int width, int height);

/* Function used to modify simp_file structure converting it to black and white */
int bw(struct simp_file * simp_data);

/* Function used to modify simp_file structure by applying a color shift pattern */
int colorshift(struct simp_file * simp_data, char * pattern);

/* Function used to overlay an image on top of another image at coordinate x, y */
int overlay(struct simp_file * simp_data, struct simp_file * overlay_data, int x, int y);

/* Support function for overlay used to calculate RGB values with respect to their alpha values */
void overlay_calculation(unsigned char * color_value1, unsigned char * color_value2,
	unsigned char * alpha1, unsigned char * alpha2);

/* Function used to free memory associated with simp_file data structure */
int simp_data_clear(struct simp_file * simp_data);

#endif
