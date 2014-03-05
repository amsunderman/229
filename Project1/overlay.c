#include "simp_util.h"

#define NUM_ARGUMENTS 6
#define ARGUMENT_FORMAT "overlay pic1.simp pic2.simp out.simp x y"

/* Program used to overlay pic2 over pic1 with transparency correlating to both
 * pictures alpha values and save it into out.simp
 * @param pic1.simp: base simp file
 * @param pic2.simp: overlaid simp file
 * @param out.simp: simp file to write overlaid image to
 * @param int x: x coordinate to start overlay
 * @param int y: y coordinate to start overlay
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/07/2014 */
int main(int argc, char** argv)
{
	/*integers to store loop and error values*/
	int i, j, err;

	/*file pointer that references base simp file*/
	FILE * base_fp;

	/*file pointer that references overlay simp file*/
	FILE * overlay_fp;

	/*file pointer that references simp file to output overlaid image to*/
	FILE * out_fp;

	/*integers to store overlay coordinates*/
	int x, y;

	/*simp_file structure to hold base simp data*/
	struct simp_file * base_simp_data = (struct simp_file *) malloc(
		sizeof(struct simp_file));

	/*simp_file structure to hold overlay simp data*/
	struct simp_file * overlay_simp_data = (struct simp_file *) malloc(
		sizeof(struct simp_file));

	/*check for correct number of arguments*/
	if(argc != NUM_ARGUMENTS)
	{
		fprintf(stderr, "error (overlay): incorrect # of command line " 
			"arguments\n");
		fprintf(stderr, "overlay: expected format: ");
		fprintf(stderr, ARGUMENT_FORMAT);
		fprintf(stderr, "\noverlay: exiting program\n");
		return -1;
	}

	/*parse arguments*/
	base_fp = fopen(argv[1], "r+b");
	overlay_fp = fopen(argv[2], "r+b");
	out_fp = fopen(argv[3], "wb");
	x = atoi(argv[4]);
	y = atoi(argv[5]);

	/*use simp_util read_simp_file to read data from base .simp file
 	* into base simp_file structure*/
	err = read_simp_file(base_fp, base_simp_data);

	if(err)
	{
		fprintf(stderr, "error (overlay): error encountered "
			"(read_simp_file)\n");
		fprintf(stderr, "overlay: exiting program\n");
		return -1;
	}

	/*use simp_util read_simp_file to read data from overlay .simp file
 	* into overlay simp_file structure*/
	err = read_simp_file(overlay_fp, overlay_simp_data);

	if(err)
	{
		fprintf(stderr, "error (overlay): error encountered "
			"(read_simp_file)\n");
		fprintf(stderr, "overlay: exiting program\n");
		return -1;
	}

	/*use simp_util overlay method to modify base simp_data structure*/
	err = overlay(base_simp_data, overlay_simp_data, x, y);

	if(err)
	{
		fprintf(stderr, "error (overlay): error encountered " 
			"(simp_util overlay)\n");
		fprintf(stderr, "overlay: exiting program\n");
		return -1;
	}

	/*use simp_util write simp_file to write data to provided
 	* .simp file from base_simp_file structure*/
	err = write_simp_file(out_fp, base_simp_data);

	if(err)
	{
		fprintf(stderr, "error (overlay): error encountered " 
			"(write_simp_file)\n");
		fprintf(stderr, "overlay: exiting program\n");
		return -1;
	}

	/*cleanup (free memory)*/
	fclose(base_fp);
	fclose(overlay_fp);
	fclose(out_fp);
	simp_data_clear(base_simp_data);
	simp_data_clear(overlay_simp_data);

	/*return successfully*/
	return 0;
}
