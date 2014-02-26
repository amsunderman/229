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
	
	/*TODO*/

	/*return successfully*/
	return 0;
}

int read_act_file(FILE * fp, action_file * action_data)
{
	/*general error checking*/

	/*TODO*/

	/*return successfully*/
	return 0;
}

text_id * find_text_id(meme_id * meme, char * text_id)
{
	/*counter*/
	int i;

	/*general error checking*/
	if(!meme)
	{
		printf("find_text_id: meme_id is null\n");
		return NULL;
	}

	if(!text_id)
	{
		printf("text_id string is null\n");
		return NULL;
	}

	/*look through locations within meme_id structure to find correct
 	* text_id structure and return it*/
	for(i = 0; i < meme->num_locations; i++)
	{
		if(strcmp(text_id, meme->locations[i].name) == 0)
		{
			return &(meme->locations[i]);
		}
	}

	/*if we didn't find it then it doesn't exist: return NULL*/
	return NULL;
}

meme_id * find_meme_id(meme_file * meme_data, char * meme_id)
{
	/*counter*/
	int i;

	/*general error checking*/
	if(!meme_data)
	{
		printf("find_meme_id: meme_file structure is null\n");
		return NULL;
	}

	if(!meme_id)
	{
		printf("meme_id string is null\n");
		return NULL;
	}

	/*look through meme_id's within meme_file structure to find correct
 	* meme_id structure and return it*/
	for(i = 0; i < meme_data->num_memes; i++)
	{
		if(strcmp(meme_id, meme_data->memes[i].name) == 0)
		{
			return &(meme_data->memes[i]);
		}
	}

	/*if we didn't find it then it doesn't exist: return NULL*/
	return NULL;
}

struct simp_file * load_font()
{
	/*TODO*/
	return NULL;
}

struct simp_file * load_meme()
{
	/*TODO*/
	return NULL;
}
