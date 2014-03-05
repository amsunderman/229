#include "simp_util.h"

#define NUM_ARGUMENTS 3
#define ARGUMENT_FORMAT "bw pic.simp out.simp"

/* Program used to convert .simp image to a black white .simp image
 * @arg pic.simp: input simp file
 * @arg out.simp: simp file to write black/white image to
 * @ret int: 0 = opteration success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/07/2014 */
int main(int argc, char** argv)
{
	/*loop counters and error variables*/
	int i, j, err;

	/*file pointer for given .simp file*/
	FILE * in_fp;

	/*file pionter for .simp file to write bw image to*/
	FILE * out_fp;

	/*structure to hold simp data*/
	struct simp_file * simp_data = (struct simp_file *) malloc(
		sizeof(struct simp_file));

	/*check for correct number of arguments*/
	if(argc != NUM_ARGUMENTS)
	{
		fprintf(stderr, "error (bw): incorrect # of command line " 
			"arguments\n");
		fprintf(stderr, "bw: expected format: ");
		fprintf(stderr, ARGUMENT_FORMAT);
		fprintf(stderr, "\nbw: exiting program\n");
		return -1;
	}

	/*parse arguments*/
	in_fp = fopen((argv[1]), "r+b");
	out_fp = fopen((argv[2]), "wb");

	/*use simp_util read_simp_file to read data from provided
 	* .simp file into simp_data structure*/
	err = read_simp_file(in_fp, simp_data);

	if(err)
	{
		fprintf(stderr, "error (bw): error encountered " 
			"(read_simp_file)\n");
		fprintf(stderr, "bw: exiting program\n");
		return -1;
	}

	/*modify simp_data structure using simp_util bw*/
	err = bw(simp_data);

	if(err)
	{
		fprintf(stderr, "error (bw): error encountered " 
			"(simp_util bw)\n");
		fprintf(stderr, "bw: exiting program\n");
		return -1;
	}

	/*use simp_util write_simp_file to write data to provided
 	* .simp file from simp_data structure*/
	err = write_simp_file(out_fp, simp_data);

	if(err)
	{
		fprintf(stderr, "error (bw): error encountered " 
			"(write_simp_file)\n");
		fprintf(stderr, "bw: exiting program\n");
		return -1;
	}

	/*cleanup (free memory)*/
	fclose(in_fp);
	fclose(out_fp);
	simp_data_clear(simp_data);

	/*return successfully*/
	return 0;
}
