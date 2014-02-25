#include "meme_file_util.h"

int read_mem_file(FILE * fp, meme_file * meme_data)
{
	/*general error checking*/
	if(!fp)
	{
		printf("read_mem_file: file pointer is null\n");
		return -1;
	}

	if(!meme_data)
	{
		printf("read_mem_file: meme_data is null\n");
		return -1;
	}

	

	/*return successfully*/
	return 0;
}

int read_act_file(FILE * fp, action_file * action_data)
{
	/*general error checking*/

	/*return successfully*/
	return 0;
}
