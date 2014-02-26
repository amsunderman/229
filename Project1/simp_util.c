#include "simp_util.h"

/* Function used to read from file fp and store it in the simp_file structure 
 * simp_data. Function expects simp_data has already had memory allocated to 
 * store width, height, num_pixels and unsigned char ** pixels 
 * @param FILE *fp: pointer to .simp file to read data from
 * @param struct simp_file * simp_data: pointer to simp_file data structure to 
 * insert data into
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified: 02/05/2014 */
int read_simp_file(FILE * fp, struct simp_file * simp_data)
{
	/*integers to store width, height, and loop variables*/
	int width, height, i, j;

	/*used to read in raw binary data for width*/
	unsigned char width_data[4];
	
	/*used to read in raw binary data for height*/
	unsigned char height_data[4];

	/*General Error Checking*/
	if(!fp)
	{
		printf("error (read_simp_file): .simp file pointer is null\n");
		return -1;
	}

	if(!simp_data)
	{
		printf("error (read_simp_file): simp_data structure is null\n");
		return -1;
	}

	/*read width and height into unsigned char array*/
	fread(width_data, sizeof(unsigned char), 4, fp);
	fread(height_data, sizeof(unsigned char), 4, fp);

	/*convert width and height to 32 bit integer*/
	width = width_data[0] | width_data[1] << 8 | 
		width_data[2] << 16 | width_data[3] << 24;
	height = height_data[0] | height_data[1] << 8 | 
		height_data[2] << 16 | height_data[3] << 24;

	/*initialize simp_data and calculate num_pixels*/
	simp_data->width = width;
	simp_data->height = height;
	simp_data->num_pixels = width * height;
	simp_data->pixels = (struct simp_pixel **) malloc(
		simp_data->height*sizeof(struct simp_pixel *));

	for(i = 0; i < simp_data->height; i++)
	{
		simp_data->pixels[i] = (struct simp_pixel *) malloc(
			simp_data->width * sizeof(struct simp_pixel));
	}

	/*check if memory was successfully allocated for pixels*/
	if(!simp_data->pixels)
	{
		printf("error (read_simp_file): failed to allocate memory for \
			pixels\n");
		return -1;
	}
	
	/*loop through pixels and fill in date from binary file into simp_file 
 	* structure*/
	for(i = 0; i < simp_data->height; i++)
	{
		for(j = 0; j < simp_data->width; j++)
		{
			/*if we find eof pre-maturely than the .simp file is 
 			* invalid*/
			if(feof(fp))
			{
				printf("error (read_simp_file: file length did \
					not match number of pixels expected\n");
				return -1;
			}
			fread(&(simp_data->pixels[i][j].red_value), 
				sizeof(unsigned char), 1, fp);
			fread(&(simp_data->pixels[i][j].green_value), 
				sizeof(unsigned char), 1, fp);
			fread(&(simp_data->pixels[i][j].blue_value), 
				sizeof(unsigned char), 1, fp);
			fread(&(simp_data->pixels[i][j].alpha_value), 
				sizeof(unsigned char), 1, fp);
		}
	}

	/*read character (if file is valid it will be the 'eof' character)*/
	fgetc(fp);

	/*if we haven't found eof by this point than the .simp file is invalid*/
	if(!feof(fp))
	{
		printf("error (read_simp_file): file length did not match \
			number of pixels expected\n");
		return -1;
	}

	/*Return Successfully*/
	return 0;
}

/* Function used to write the data contained in the simp_data structure 
 * into FILE fp in .simp format
 * @param FILE * fp: file pointer that points to .simp file to write to
 * @param struct simp_file * simp_data: structer that contains simp data to 
 * write
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/05/2014 */
int write_simp_file(FILE * fp, struct simp_file * simp_data)
{
	/*integer to store loop variables*/
	int i, j;

	/*used to read in raw binary data for width*/
	unsigned char width_data[4];

	/*used to read in raw binary data for height*/
	unsigned char height_data[4];

	/*General Error Checking*/
	if(!fp)
	{
		printf("error (write_simp_file): .simp file pointer is null\n");
		return -1;
	}

	if(!simp_data)
	{
		printf("error (write_simp_file): simp_data structure is \
			null\n");
		return -1;
	}

	if(simp_data->num_pixels != simp_data->height * simp_data->width)
	{
		printf("error (write_simp_file): simp_data structure contains \
			a number of pixels that doesn't correlate to the width \
			and height\n");
		return -1;
	}

	/*prepare width data to be entered into binary file*/
	width_data[0] = simp_data->width;
	width_data[1] = simp_data->width >> 8;
	width_data[2] = simp_data->width >> 16;
	width_data[3] = simp_data->width >> 24;

	/*prepare height data to be entered into binary file*/
	height_data[0] = simp_data->height;
	height_data[1] = simp_data->height >> 8;
	height_data[2] = simp_data->height >> 16;
	height_data[3] = simp_data->height >> 24;

	/*write width and height int .simp file*/
	fwrite(width_data, sizeof(unsigned char), 4, fp);
	fwrite(height_data, sizeof(unsigned char), 4, fp);

	/*loop through pixels and write rgba values into .simp file*/
	for(i = 0; i < simp_data->height; i++)
	{
		for(j = 0; j < simp_data->width; j++)
		{
 			fwrite(&(simp_data->pixels[i][j].red_value), 
				sizeof(unsigned char), 4, fp);
		}
	}
	/*return successfully*/
	return 0;
}

/* Function that modifies simp_data structure with new x,y coordinates and
 * width and height resulting in a cropped version of the structure saved in 
 * provided cropped simp_file structure
 * @param struct simp_file * simp_data: structure to be manipulated
 * @param struct simp_file * cropped: structure to store cropped image
 * @param int x: x coordinate to be left most column of pixels
 * @param int y: y coordinate to be upper most row of pixels
 * @param int width: width of cropped image
 * @param int height: height of cropped image
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/11/2014 */
int crop(struct simp_file * simp_data, struct simp_file * cropped, 
	int x, int y, int width, int height)
{
	/*loop variables*/
	int i, j;

	/*general error checking*/
	if(!simp_data)
	{
		printf("error (crop): simp_data structure is null\n");
		return -1;
	}

	/*boundary error checking*/
	if(x < 0 || y < 0)
	{
		printf("error (crop): x and y coordinates must be \
			non-negative\n");
		return -1;
	}

	if(width < 1 || height < 1)
	{
		printf("error (crop): width and height must be positive\n");
		return -1;
	}

	if(x + width > simp_data->width ||
		y + height > simp_data->height)
	{
		printf("error (crop): cropping goes outside of image \
			boundaries\n");
		return -1;
	}

	/*initialize cropped width, height, num_pixels, and memory allocation*/
	cropped->width = width;
	cropped->height = height;
	cropped->num_pixels = width * height;

	cropped->pixels = (struct simp_pixel **) malloc(
		height * sizeof(struct simp_pixel *));

	for(i = 0; i < height; i++)
	{
		cropped->pixels[i] = (struct simp_pixel *) malloc(
			width * sizeof(struct simp_pixel));
	}

	/*fill cropped image*/
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			cropped->pixels[i][j] = simp_data->pixels[y+i][x+j];
		}
	}

	/*return successfully*/
	return 0;
}

/* Function that modifies simp_data structure to contain all b/w pixels
 * @param struct simp_file * simp_data: structure to be manipulated
 * @ret int: 0 = operation success, 1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/07/2014 */
int bw(struct simp_file * simp_data)
{
	/*loop variables and variable that stores the average RGB value per 
 	* pixel*/
	int i, j, average_rgb;

	/*general error checking*/
	if(!simp_data)
	{
		printf("error (bw): simp data structure is null\n");
		return -1;
	}

	/*loop through pixels and apply average_rgb to RGB values resulting in 
 	* b/w pixels*/
	for(i = 0; i < simp_data->height; i++)
	{
		for(j = 0; j < simp_data->width; j++)
		{
			average_rgb = (simp_data->pixels[i][j].red_value + 
				simp_data->pixels[i][j].green_value + 
				simp_data->pixels[i][j].blue_value) / 3;
			simp_data->pixels[i][j].red_value = average_rgb;
			simp_data->pixels[i][j].green_value = average_rgb;
			simp_data->pixels[i][j].blue_value = average_rgb;
		}
	}

	/*return successfully*/
	return 0;
}

/* Function that applies color shift to simp_data structure according to
 * provided pattern
 * @param struct simp_file * simp_data: structure to be manipulated
 * @param char * pattern: string that contains the pattern to apply to each 
 * pixel
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/07/2014 */
int colorshift(struct simp_file * simp_data, char * pattern)
{
	/*loop variables*/
	int i, j;

	/*temporary value to hold a color during swap process*/
	unsigned char temp_color;

	/*general error checking*/
	if(!simp_data)
	{
		printf("error (colorshift): simp_data structure is null\n");
		return -1;
	}

	/*loop through pixels and apply color shift pattern
 	* if pattern is unsupported report error*/
	for(i = 0; i < simp_data->height; i++)
	{
		for(j = 0; j < simp_data->width; j++)
		{
			if(strcmp(pattern, "RGB") == 0 || strcmp(pattern, "GBR")
				== 0 || strcmp(pattern, "BRG") == 0)
			{
				temp_color = simp_data->pixels[i][j].red_value;
				simp_data->pixels[i][j].red_value = 
					simp_data->pixels[i][j].blue_value;
				simp_data->pixels[i][j].blue_value = 
					simp_data->pixels[i][j].green_value;
				simp_data->pixels[i][j].green_value = 
					temp_color;
			}
			else if(strcmp(pattern, "GRB") == 0 || strcmp(pattern, 
				"RBG") == 0 || strcmp(pattern, "BGR") == 0)
			{
				temp_color = 
					simp_data->pixels[i][j].green_value;
				simp_data->pixels[i][j].green_value =
					simp_data->pixels[i][j].blue_value;
				simp_data->pixels[i][j].blue_value =
					simp_data->pixels[i][j].red_value;
				simp_data->pixels[i][j].red_value = temp_color;
			}
			else if(strcmp(pattern, "RG") == 0 || strcmp(pattern, 
				"GR") == 0)
			{
				temp_color = simp_data->pixels[i][j].red_value;
				simp_data->pixels[i][j].red_value = 
					simp_data->pixels[i][j].green_value;
				simp_data->pixels[i][j].green_value = 
					temp_color;
			}
			else if(strcmp(pattern, "RB") == 0 || strcmp(pattern, 
				"BR") == 0)
			{
				temp_color = simp_data->pixels[i][j].red_value;
				simp_data->pixels[i][j].red_value = 
					simp_data->pixels[i][j].blue_value;
				simp_data->pixels[i][j].blue_value = temp_color;
			}
			else if(strcmp(pattern, "GB") == 0 || strcmp(pattern, 
				"BG") == 0)
			{
				temp_color = 
					simp_data->pixels[i][j].green_value;
				simp_data->pixels[i][j].green_value =
					simp_data->pixels[i][j].blue_value;
				simp_data->pixels[i][j].blue_value = temp_color;
			}
			else
			{
				printf("error (colorshift): unsupported \
					pattern\n");
				return -1;
			}
		}
	}

	/*return successfully*/
	return 0;
}

/* Function used to overlay simp_data (overlay_data) over another simp_data
 * structure (simp_data) based off of the respective alpha values per pixel
 * @param struct simp_file * simp_data: simp_data to be base image
 * @param struct simp_file * overlay_data: simp_data to be overlaid on base 
 * image
 * @param int x: x coordinate to be leftmost corner of overlaid image
 * @param int y: y coordinate to be uppermost corner of overlaid image
 * @ret int: 0 = operation success, 1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/12/2014 */
int overlay(struct simp_file * simp_data, struct simp_file * overlay_data, 
	int x, int y)
{
	/*loop variables*/
	int i, j;

	/*general error checking*/
	if(!simp_data)
	{
		printf("error (overlay): simp_data structure is null\n");
		return -1;
	}

	if(!overlay_data)
	{
		printf("error (overlay): overlay_data structure is null\n");
		return -1;
	}

	/*boundary error checking*/
	if(x < 0 || y < 0)
	{
		printf("error (overlay): x and y coordinates must be \
			non-negative\n");
		return -1;
	}

	if((x + overlay_data->width) > simp_data->width || 
		(y + overlay_data->height) > simp_data->height)
	{
		printf("error (overlay): overlay image goes outside of base \
			image boundaries\n");
		return -1;
	}

	/*loop through pixels and overlay image*/
	for(i = y; i < overlay_data->height + y; i++)
	{
		for(j = x; j < overlay_data->width + x; j++)
		{
			overlay_calculation(&(simp_data->pixels[i][j].
				red_value), &(overlay_data->pixels[i-y][j-x].
				red_value), &(simp_data->pixels[i][j].
				alpha_value), &(overlay_data->pixels[i-y][j-x].
				alpha_value));
			overlay_calculation(&(simp_data->pixels[i][j].
				green_value), &(overlay_data->pixels[i-y][j-x].
				green_value), &(simp_data->pixels[i][j].
				alpha_value), &(overlay_data->pixels[i-y][j-x].
				alpha_value));
			overlay_calculation(&(simp_data->pixels[i][j].
				blue_value), &(overlay_data->pixels[i-y][j-x].
				blue_value), &(simp_data->pixels[i][j].
				alpha_value), &(overlay_data->pixels[i-y][j-x].
				alpha_value));
			overlay_calculation(NULL, NULL, 
				&(simp_data->pixels[i][j].alpha_value),
				&(overlay_data->pixels[i-y][j-x].alpha_value));
		}
	}

	/*return successfully*/
	return 0;
}

/* support function for overlay to perform a calculation on a specific color.
 * leave color_value1 and color_value2 null to perform alpha calculation
 * @param unsigned char * color_value1: color to be manipulated
 * @param unsigned char * color_value2: color from overlay image
 * @param unsigned char * alpha1: alpha from base image
 * @param unsigned char * alpha2: alpha from overlay image
 * @ret void
 * @author Adam Sunderman
 * @modified 02/07/2014 */
void overlay_calculation(unsigned char * color_value1, 
	unsigned char * color_value2, unsigned char * alpha1, 
	unsigned char * alpha2)
{
	/*store color and alpha values in double variables for calculation*/
	double color_value1_d, color_value2_d, alpha1_d = (int) *alpha1, 
		alpha2_d = (int) *alpha2;

	/*temp variables to stor left and right half of equations*/
	double left_temp, right_temp;

	if(color_value1 && color_value2)
	{
		color_value1_d = (int) *color_value1;
		color_value2_d = (int) *color_value2;
		left_temp = (alpha2_d/255) * color_value2_d;
		right_temp = ((alpha1_d * (255 - alpha2_d))/(255 * 255)) * 
			color_value1_d;
		*color_value1 = 0x000000FF & (int) (left_temp + right_temp);
	}
	else if(!color_value1 && !color_value2)
	{
		left_temp = alpha2_d / 255;
		right_temp = (alpha1_d * (255 - alpha2_d))/(255 * 255);
		*alpha1 = 0x000000FF & 255 * (int) (left_temp + right_temp);
	}
	else
	{
		/*not defined, however, function is only called internally from 
 		* simp_util.c so arguments are tightly controlled */
	}
	return;
}

/* Function used to free memory associated with a simp_data structure
 * @param struct simp_file * simp_data: structure with memory to be cleared
 * @ret int: 0 = operation success; 1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/11/2014 */
int simp_data_clear(struct simp_file * simp_data)
{
	/*loop variable to clear pointers for each row of pixels*/
	int i;

	/*if simp_data is null we cannot free it*/
	if(!simp_data)
	{
		printf("simp_data_clear: simp_data is null\n");
		return -1;
	}

	/*loop through and free pixel rows*/
	for(i = 0; i < simp_data->height; i++)
	{
		/*if a row is null we cannot free*/
		if(!simp_data->pixels[i])
		{
			printf("simp_data_clear: simp_data pixels are null\n");
			return -1;
		}
		free(simp_data->pixels[i]);
	}

	free(simp_data->pixels);
	free(simp_data);

	/*return successfully*/
	return 0;
}
