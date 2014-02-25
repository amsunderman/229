#include "meme_file_util.h"

#define NUM_ARGUMENTS 3
#define ARGUMENT_FORMAT "meme memefile.mem action.act"

int main(int argc, char ** argv)
{
	/*integer that stores error values*/
	int err;

	/*structure that stores MEM file data*/
	meme_file * meme_data;

	/*structure that stores ACT file data*/
	action_file * action_data;

	/*file pointer to MEM file*/
	FILE * meme_file;

	/*file pointer to ACT file*/
	FILE * act_file;
	

	/*check for correct number of arguments*/
	if(argc != NUM_ARGUMENTS)
	{
		printf("error (meme): incorrect # of command line arguments\n");
		printf("meme: expected format: ");
		printf(ARGUMENT_FORMAT);
		printf("\nmeme: exiting program\n");
		return -1;
	}

	/*parse arguments*/
	meme_file = fopen(argv[1], "r+");
	act_file = fopen(argv[2], "r+");

	/*read MEM file*/
	err = read_mem_file(meme_file, meme_data);

	if(err)
	{
		printf("error (meme): error encountered (read_mem_file)\n");
		printf("meme: exiting program\n");
		return -1;
	}

	/*read ACT file*/
	err = read_act_file(act_file, action_data);

	if(err)
	{
		printf("error (meme): error encountered (read_act_file)\n");
		printf("meme: exiting program\n");
		return -1;
	}

	/*TODO execute actions*/

	/*return successfully*/
	return 0;
}
