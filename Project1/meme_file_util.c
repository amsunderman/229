#include "meme_file_util.h"

#define START_TOKENS 5
#define TOKEN_INCREASE_RATE 5

/**Function used to read data stored in MEM file and store it in the meme_file
 * structure
 * @precondition meme_file * meme_data has already had memory allocated
 * @postcondition meme_data will be filled with data from fp FILE pointer
 * @param FILE * fp: pointer to .mem file to read data from
 * @param meme_file * meme_data: pointer to meme_file structure to insert data
 * into
 * @ret int: 0 = operation success, -1 = error (accompanied by print statement)
 * @author Adam Sunderman
 * @modified: 02/28/2014 */
int read_mem_file(FILE * fp, meme_file * meme_data)
{
	/*error value and counter*/
	int err, i = 0;

	/*string to store current line*/
	char * current_line = NULL;

	/*int to store the number of the current line*/
	int line_count = 0;

	/*strings for each half of the line (before and after colon)*/
	char * left;
	char * right;

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

	/*get first line*/
	current_length = getline(&current_line, &n, fp);
	line_count++;

	/*loop through all lines and tokenize them based off of the colon*/
	while((int) current_length > -1)
	{
		/*NULL terminate the current line w/o new line character*/
		current_line[current_length - 1] = '\0';

		/*store sub string of current line (before colon)*/
		left = strtok(current_line, ":");

		/*if left is NULL then something went wrong*/
		if(!left)
		{
			printf("read_mem_file: incorrect .mem file format in " 
				"line %d\n", line_count);
			return -1;
		}

		/*store sub string of current line (after colon)*/
		right = strtok(NULL, ":");

		/*if right is NULL then something went wrong*/
		if(!right)
		{
			printf("read_mem_file: incorrect .mem file format in " 
				"line %d\n", line_count);
			return -1;
		}

		/*if there are any more tokens then the current line isn't
 		* valid formatting*/
		if(strtok(NULL, ":"))
		{
			printf("read_mem_file: incorrect .mem file format in " 
				"line %d\n", line_count);
			return -1;
		}

		/*fill in MEM data into provided mem_data structure*/
		err = mem_parse_line(left, right, meme_data);

		if(err)
		{
			printf("read_mem_file: incorrect .mem file format in "
				"line %d\n", line_count);
		}

		/*move onto next line*/
		current_length = getline(&current_line, &n, fp);
		line_count++;
	}

	/*free current_line that was allocated with getline()*/
	free(current_line);

	/*return successfully*/
	return 0;
}

/**Function used to read data stored in a ACT file and store it in the
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

/**Function used to parse an individual MEM file line and create necessary
 * structures and data to insert it into meme_file * meme_data
 * @param char * left: left part of MEM file line (before colon)
 * @param char * right: right part of MEM file line (after colon)
 * @param meme_file * meme_data: meme_file structure to insert data into
 * @ret int: 0 = operation success, -1 = error(accompanied by print statement)
 * @author Adam Sunderman
 * @modified 02/28/2014 */
int mem_parse_line(char * left, char * right, meme_file * meme_data)
{
	/*strings used to tokenize left and right strings using " " as the
 	* delimiter*/
	char** left_tokens = malloc(START_TOKENS * sizeof(char*));
	char** right_tokens = malloc(START_TOKENS * sizeof(char*));

	/*temp pointer for realloc*/
	char** temp;

	/*ints to store number of tokens in each input string*/
	int left_num_tokens = 0;
	int right_num_tokens = 0;

	/*ints to store max number of tokens*/
	int left_max_tokens = START_TOKENS;
	int right_max_tokens = START_TOKENS;

	/*counters*/
	int i = 0, j = 0;

	/*store initial left token*/
	left_tokens[i] = strtok(left, " ");

	/*tokenize left*/
	while(left_tokens[i])
	{
		/*increment counters*/
		i++;
		left_num_tokens++;

		/*if left_num_tokens is greater than our allocated memory we
 		* must re-allocate*/
		if(left_num_tokens == left_max_tokens)
		{
			left_max_tokens += TOKEN_INCREASE_RATE;
			temp = realloc(left_tokens, left_max_tokens * 
				sizeof(char*));
			if(!temp)
			{
				printf("mem_parse_line: failed to allocate " 
					"memory\n");
				return -1;
			}
			left_tokens = temp;
		}

		/*move onto next token (will be NULL if no more exist)*/
		left_tokens[i] = strtok(NULL, " ");
	}

	/*store initial right token*/
	right_tokens[j] = strtok(right, " ");

	/*tokenize right*/
	while(right_tokens[j])
	{
		/*increment counters*/
		j++;
		right_num_tokens++;

		/*if right_num_tokens is greater than our allocated memory we
 		* must re-allocate*/
		if(right_num_tokens == right_max_tokens)
		{
			right_max_tokens += TOKEN_INCREASE_RATE;
			temp = realloc(right_tokens, right_max_tokens * 
				sizeof(char*));
			if(!temp)
			{
				printf("mem_parse_line: failed to allocate " 
				"memory\n");
				return -1;
			}
			right_tokens = temp;
		}

		/*move onto next token (will be NULL if no more exist)*/
		right_tokens[j] = strtok(NULL, " ");
	}

	for(i = 0; i < left_num_tokens; i++)
	{
		printf("%s/", left_tokens[i]);
	}
	printf("\n");
	for(j = 0; j < right_num_tokens; j++)
	{
		printf("%s/", right_tokens[j]);
	}
	printf("\n\n");

	/*use left tokens to determine line type*/

	/*TODO some other stuff*/

	/*free memory*/
	free(right_tokens);
	free(left_tokens);

	/*return successfully*/
	return 0;
}

/**Function used to return a text_id structure with name equal to the provided
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

/**Function used to return a meme_id structure with name equal to the provided
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
