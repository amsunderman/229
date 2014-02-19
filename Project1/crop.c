#include "simp_util.h"

#define NUM_ARGUMENTS 7
#define ARGUMENT_FORMAT "crop picture.simp out.simp x y width height"

/* Program used to crop a .simp file with given x y coordinates
 * and width and height values and then save it to out.simp
 * @arg picture.simp: input simp file
 * @arg out.simp: simp file to write cropped image to
 * @arg int x: x coordinate
 * @arg int y: y coordinate
 * @arg int width: width of cropped image
 * @arg int height: height of cropped image
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/11/2014 */
int main(int argc, char** argv)
{
	/*integers to store loop and error values*/
	int i, err;

	/*file pointer that references original simp file*/
	FILE * in_fp;

	/*file pointer that references simp file to output cropped image to*/
	FILE * out_fp;

	/*integers to store the crop arguments*/
	int x, y, width, height;

	/*simp_file structure to hold simp data*/
	struct simp_file * simp_data = (struct simp_file *) malloc(
		sizeof(struct simp_file));

	/*simp_file structure to hold cropped data*/
	struct simp_file * cropped = (struct simp_file *) malloc(
		sizeof(struct simp_file));

	/*check for correct number of arguments*/
	if(argc != NUM_ARGUMENTS)
	{
		printf("error (crop): incorrect # of command line arguments\n");
		printf("crop: expected format: ");
		printf(ARGUMENT_FORMAT);
		printf("\ncrop: exiting program\n");
		return -1;
	}

	/*parse arguments with error detection for invalid arguments*/
	in_fp = fopen(argv[1], "r+b");
	out_fp = fopen(argv[2], "wb");
	x = atoi(argv[3]);
	y = atoi(argv[4]);
	width = atoi(argv[5]);
	height = atoi(argv[6]);

	/*use simp_util read_simp_file to read data from provided 
 	* .simp file into simp_data structure*/
	err = read_simp_file(in_fp, simp_data);

	if(err)
	{
		printf("error (crop): error encountered (read_simp_file)\n");
		printf("crop: exiting program\n");
		return -1;
	}

	/*use simp_util crop method to modify simp data structure*/
	err = crop(simp_data, cropped, x, y, width, height);

	if(err)
	{
		printf("error (crop): error encountered (simp_util crop)\n");
		printf("crop: exiting program\n");
		return -1;
	}

	/*use simp_util write simp_file to write data to provided
 	* .simp file from simp_data structure*/
	err = write_simp_file(out_fp, cropped);
	
	if(err)
	{
		printf("error (crop): error encountered (write_simp_file)\n");
		printf("crop: exiting program\n");
		return -1;
	}

	/*cleanup (free memory)*/
	fclose(in_fp);
	fclose(out_fp);

	/*if simp_data doesn't free successfully program will still complete 
 	* but report problem*/
	if(simp_data_clear(simp_data) == -1)
	{
		printf("error (crop): error encountered (simp_data_clear)\n");
		printf("crop: simp_data memory not successfully freed\n");
	}

	/*if cropped doesn't free successfully program will still complete but 
 	* report problem*/
	if(simp_data_clear(cropped) == -1)
	{
		printf("error (crop): error encountered (simp_data_clear)\n");
		printf("crop: cropped memory not successfully freed\n");
	}

	/*return successfully*/
	return 0;
}
