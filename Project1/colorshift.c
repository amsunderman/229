#include "simp_util.h"

#define NUM_ARGUMENTS 4
#define ARGUMENT_FORMAT "colorshift pic.simp out.simp pattern"

/* Program used to convert .simp image to a colorshifted .simp image based off 
 * a pattern
 * @arg pic.simp: input simp file
 * @arg out.simp: simp file to write colorshifted image to
 * @arg pattern: pattern to use for color shift "RB" implies red to blue, blue 
 * to red
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/07/2014 */
int main(int argc, char** argv)
{
	/*integers to store loop and error values*/
	int i, j, err;

	/*file pointer that references original simp file*/
	FILE * in_fp;

	/*file pointer that references file to output colorshifted image to*/
	FILE * out_fp;

	/*stores pattern in string format*/
	char * pattern;

	/*simp_file struct to hold simp data*/
	struct simp_file * simp_data = (struct simp_file *) malloc(
		sizeof(struct simp_file));

	/*check for correct number of arguments*/
	if(argc != NUM_ARGUMENTS)
	{
		fprintf(stderr, "error (colorshift): incorrect # of command " 
			"line arguments\n");
		fprintf(stderr, "colorshift: expected format: ");
		fprintf(stderr, ARGUMENT_FORMAT);
		fprintf(stderr, "\n");
		return -1;
	}

	/*parse arguments*/
	in_fp = fopen(argv[1], "r+b");
	out_fp = fopen(argv[2], "wb");
	pattern = argv[3];

	/*use simp_util read_simp_file to read data from provides
 	* .simp file into simp_data structure*/
	err = read_simp_file(in_fp, simp_data);

	if(err)
	{
		fprintf(stderr, "error (colorshift): error encountered " 
			"(read_simp_file)\n");
		fprintf(stderr, "colorshift: exiting program\n");
		return -1;
	}

	/*modify simp_data structure using simp_util function colorshift*/
	err = colorshift(simp_data, pattern);

	if(err)
	{
		fprintf(stderr, "error (colorshift): error encountered " 
			"(simp_util colorshift)\n");
		fprintf(stderr, "colorshift: exiting program\n");
		return -1;
	}

	/*use simp_util write_simp_file to write data to provided
 	* .simp file from simp_data structure*/
	err = write_simp_file(out_fp, simp_data);

	if(err)
	{
		fprintf(stderr, "error (colorshift): error encountered " 
		"(write_simp_file)\n");
		fprintf(stderr, "colorshift: exiting program\n");
		return -1;
	}

	/*cleanup (free memory)*/
	fclose(in_fp);
	fclose(out_fp);
	simp_data_clear(simp_data);

	/*return successfully*/
	return 0;
}
