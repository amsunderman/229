#include "meme_file_util.h"

/** Function used to read data stored in MEM file and store it in the meme_file
 * structure
 * @precondition meme_file * meme_data has already had memory allocated
 * @postcondition meme_data will be filled with data from fp FILE pointer
 * @param FILE * fp: pointer to .mem file to read data from
 * @param meme_file * meme_data: pointer to meme_file structure to insert data
 * into
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified: 02/26/2014 */
int read_mem_file(FILE * fp, meme_file * meme_data)
{
	/*error value*/
	int err;	

	/*string to store current line*/
	char * current_line;

	/*size of current_line for getline function*/
	size_t n = 0, current_length = 0;

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

	current_length = getline(&current_line, &n, fp);	

	while((int) current_length > -1)
	{
		/*TODO parse current line*/
		current_length = getline(&current_line, &n, fp);
	}

	/*return successfully*/
	return 0;
}

/** Function used to read data stored in a ACT file and store it in the
 * action_file structure
 * @precondition action_file * action_data already has memory allocated
 * @postcondition action_data will be filled with data from fp FILE pointer
 * @param FILE * fp: pointer to .act file to read data from
 * @param action_file * action_data: pointer to action_file structure to insert
 * data into
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified: 02/26/2014 */
int read_act_file(FILE * fp, action_file * action_data)
{
	/*general error checking*/

	/*TODO*/

	/*return successfully*/
	return 0;
}

/** Function used to return a text_id structure with name equal to the provided
 * string text_id
 * @param meme_id * meme: meme_id structure to look for text_id structure in
 * @param char * text_id: string that contains the name of a text_id structure
 * @ret text_id *: returns a pointer to a text_id object with name = to the
 * provided string. will return NULL if the text_id was not found or if an error
 * was encountered
 * @author: Adam Sunderman
 * @modified: 02/26/2014 */
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

/** Function used to return a meme_id structure with name equal to the provided
 * string meme_id
 * @param meme_file * meme_data: meme_file structure to look for meme_id
 * structure
 * @param char * meme_id: string that contains the name of a meme_id structure
 * @ret meme_id *: returns a pointer to a meme_id object with name = to the
 * provided string. will return NULL if the meme_id was not found or if an error
 * was encountered
 * @author: Adam Sunderman
 * @modified 02/26/2014 */
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

/**TODO*/
struct simp_file * load_font()
{
	/*TODO*/
	return NULL;
}

/**TODO*/
struct simp_file * load_meme()
{
	/*TODO*/
	return NULL;
}
