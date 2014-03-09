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
 * @modified: 03/06/2014 */
int read_mem_file(FILE * fp, meme_file * meme_data)
{
	/*error value and counter*/
	int err, i = 0;

	/*string to store current line*/
	char * current_line = NULL;

	/*strings for each half of the line (before and after colon)*/
	char * left;
	char * right;

	/*size of current_line for getline function*/
	size_t n = 0, current_length = 0;

	/*general error checking*/
	if(!fp)
	{
		fprintf(stderr, "read_mem_file: file pointer is null\n");
		return -1;
	}

	if(!meme_data)
	{
		fprintf(stderr, "read_mem_file: meme_data is null\n");
		return -1;
	}

	/*initial memory allocation for meme_file*/
	meme_data->memes = NULL;
	meme_data->fonts = NULL;
	meme_data->num_memes = 0;
	meme_data->num_fonts = 0;

	/*get first line*/
	current_length = getline(&current_line, &n, fp);

	/*loop through all lines and tokenize them based off of the colon*/
	while((int) current_length > -1)
	{
		/*NULL terminate the current line w/o new line character*/
		current_line[current_length - 1] = '\0';

		/*are we on a blank line? if so skip (else statement)*/
		if(strlen(current_line) != 0)
		{
			/*store sub string of current line (before colon)*/
			left = strtok(current_line, ":");

			/*if left is NULL then something went wrong*/
			if(!left)
			{
				fprintf(stderr, "read_mem_file: " 
					"incorrect .mem file format line " 
					"%s\n", current_line);
				return -1;
			}

			/*store sub string of current line (after colon)*/
			right = strtok(NULL, ":");

			/*if right is NULL then something went wrong*/
			if(!right)
			{
				fprintf(stderr, "read_mem_file: " 
					"incorrect .mem file format line " 
					"%s\n", current_line);
				return -1;
			}

			/*if there are any more tokens then the current line 
			* isn't valid formatting*/
			if(strtok(NULL, ":"))
			{
				fprintf(stderr, "read_mem_file: " 
					"incorrect .mem file format line " 
					"%s\n", current_line);
				return -1;
			}

			/*fill in MEM data into provided mem_data structure*/
			err = mem_parse_line(left, right, meme_data);

			if(err)
			{
				fprintf(stderr, "error (read_mem_file): error "
					"encountered (mem_parse_line)\n");
				return -1;
			}

			/*move onto next line*/
			current_length = getline(&current_line, &n, fp);
		}
		else
		{
			/*move onto next line*/
			current_length = getline(&current_line, &n, fp);
		}
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
	/*error value and counter*/
	int err, i = 0;

	/*string to store current line*/
	char * current_line = NULL;

	/*strings for each half of the line (before and after colon)*/
	char * left;
	char * right;

	/*size of current_line for getline function*/
	size_t n = 0, current_length = 0;

	/*general error checking*/
	if(!fp)
	{
		fprintf(stderr, "read_act_file: file pointer is null\n");
		return -1;
	}

	if(!action_data)
	{
		fprintf(stderr, "read_act_file: action_data is null\n");
		return -1;
	}

	/*initial memory allocation for act file*/
	action_data->out = NULL;
	action_data->meme_id = NULL;
	action_data->font_id = NULL;
	action_data->actions = malloc(START_TOKENS * sizeof(action));

	/*get first line*/
	current_length = getline(&current_line, &n, fp);

	/*loop through all lines and tokenize them based off of the colon*/
	while((int) current_length > -1)
	{
		/*NULL terminate the current line w/o new line character*/
		current_line[current_length - 1] = '\0';

		/*are we on a blank line? if so skip (else statement)*/
		if(strlen(current_line) != 0)
		{
			/*store sub string of current line (before colon)*/
			left = strtok(current_line, ":");

			/*if left is NULL then something went wrong*/
			if(!left)
			{
				fprintf(stderr, "read_act_file: incorrect" 
					".act file format line %s\n", 
					current_line);
				return -1;
			}

			/*store sub string of current line (after colon)*/
			right = strtok(NULL, ":");

			/*if right is NULL then something went wrong*/
			if(!right)
			{
				fprintf(stderr, "read_act_file: incorrect" 
					".act file format line %s\n", 
					current_line);
				return -1;
			}

			/*fill in ACt data into provided action_data structure*/
			err = act_parse_line(left, right, action_data);

			if(err)
			{
				fprintf(stderr, "error (read_act_file): error " 
					"encountered (act_parse_line)\n");
				return -1;
			}

			/*move onto next line*/
			current_length = getline(&current_line, &n, fp);
		}
		else
		{
			/*move onto next line*/
			current_length = getline(&current_line, &n, fp);
		}
	}

	/*free current_line that was allocated with getline()*/
	free(current_line);

	/*return successfully*/
	return 0;
}

/**Function used to read data stored in a FSF file and store it in a font
 * structure
 * @param char * fsf_file_name: name of fsf file to read from
 * @ret font: font structure with all important info from fsf file will be
 * a default return (name = NULL) if operation failure
 * @author Adam Sunderman
 * @modified 03/06/2014*/
font read_fsf_file(char * fsf_file_name)
{
	/*File pointer to fsf file*/
	FILE * fp;

	/*error value and counter*/
	int err, i = 0;

	/*string to store current line*/
	char * current_line = NULL;

	/*strings for each half of the line (before and after colon)*/
	char * left;
	char * right;

	/*size of current_line for getline function*/
	size_t n = 0, current_length = 0;

	/*default return value (represents failure)*/
	font default_return;

	/*return font*/
	font ret;

	/*NULL name represents failure*/
	default_return.name = NULL;

	/*open fsf file*/
	fp = fopen(fsf_file_name, "r+");

	/*did file open correctly*/
	if(!fp)
	{
		fprintf(stderr, "read_fsf_file: failed to open fsf " 
			"file\n");
		return default_return;
	}

	/*initial memory allocation for font members*/
	ret.name = NULL;
	ret.image = NULL;
	ret.characters = malloc(START_TOKENS * sizeof(character));
	ret.num_characters = 0;

	/*get first line*/
	current_length = getline(&current_line, &n, fp);

	/*loop through all lines and tokenize them based off of the colon*/
	while((int) current_length > -1)
	{
		/*NULL terminate the current line w/o new line character*/
		current_line[current_length - 1] = '\0';

		/*are we on a blank line if so skip it (else statement)*/
		if(strlen(current_line) != 0)
		{
			/*store sub string of current line (before colon)*/
			left = strtok(current_line, ":");

			/*if left is NULL then something went wrong*/
			if(!left)
			{
				fprintf(stderr, "read_fsf_file: " 
					"incorrect .fsf file format line " 
					"%s\n", current_line);
				return default_return;
			}

			/*store sub string of current line (after colon)*/
			right = strtok(NULL, ":");

			/*if right is NULL then something went wrong*/
			if(!right)
			{
				fprintf(stderr, "read_fsf_file: " 
					"incorrect .fsf file format line " 
					"%s\n", current_line);
				return default_return;
			}

			/*if there are any more tokens then the current line 
			* isn't valid formatting*/
			if(strtok(NULL, ":"))
			{
				fprintf(stderr, "read_fsf_file: " 
					"incorrect .fsf file format line " 
					"%s\n", current_line);
				return default_return;
			}

			/*fill in FSF data into provided font data structure*/
			err = fsf_parse_line(left, right, &ret);

			if(err)
			{
				fprintf(stderr, "error (read_fsf_file): error " 
					"encountered (fsf_parse_line)\n");
				return default_return;
			}

			/*move onto next line*/
			current_length = getline(&current_line, &n, fp);
		}
		else
		{
			/*move onto next line*/
			current_length = getline(&current_line, &n, fp);
		}
	}

	/*close fsf file*/
	fclose(fp);

	/*return successfully*/
	return ret;
}

/**Function used to parse an individual MEM file line and create necessary
 * structures and data to insert it into meme_file * meme_data
 * @param char * left: left part of MEM file line (before colon)
 * @param char * right: right part of MEM file line (after colon)
 * @param meme_file * meme_data: meme_file structure to insert data into
 * @ret int: 0 = operation success, -1 = error(accompanied by print statement)
 * @author Adam Sunderman
 * @modified 03/06/2014 */
int mem_parse_line(char * left, char * right, meme_file * meme_data)
{
	/*strings used to tokenize left and right strings using " " as the
 	* delimiter*/
	char** left_tokens = malloc(START_TOKENS * sizeof(char*));
	char** right_tokens = malloc(START_TOKENS * sizeof(char*));

	/*store number of right and left tokens*/
	int left_num_tokens, right_num_tokens;

	/*counters*/
	int i = 0, j = 0;
	int l_index;

	/*max number of locations for currently allocated memory*/
	int max_locations = START_TOKENS;

	/*temp meme_id for realloc of locations*/
	text_id * temp;

	/*pointer to store meme_id to modify for certain .mem lines*/
	meme_id * current_meme_id;

	/*tokenize line*/
	tokenize_line(left, right, left_tokens, right_tokens, &left_num_tokens, 
		&right_num_tokens);

	/*is this line MEMES?*/
	if((strcmp(left_tokens[0], "MEMES") == 0) && left_num_tokens == 1)
	{
		/*allocate memory for meme id's*/
		meme_data->memes = malloc(right_num_tokens * sizeof(meme_id));

		/*update num_memes for meme_file structure*/
		meme_data->num_memes = right_num_tokens;

		/*loop through right tokens and make meme_id's for them*/
		for(i = 0; i < right_num_tokens; i++)
		{
			/*set name*/
			meme_data->memes[i].name = malloc(
				strlen((right_tokens[i]) + 1) * sizeof(char));
			strcpy(meme_data->memes[i].name, right_tokens[i]);

			/*initialize image and location data*/
			meme_data->memes[i].image = NULL;
			meme_data->memes[i].locations = malloc(START_TOKENS * 
				sizeof(text_id));
			meme_data->memes[i].num_locations = 0;
		}
	}

	/*is this line FONTS?*/
	else if((strcmp(left_tokens[0], "FONTS") == 0) && left_num_tokens == 1)
	{
		/*allocate memory for fonts*/
		meme_data->fonts = malloc(right_num_tokens * sizeof(font));

		/*update num_fonts for meme file structure*/
		meme_data->num_fonts = right_num_tokens;

		/*loop through right tokens and make fonts for them*/
		for(i = 0; i < right_num_tokens; i++)
		{
			meme_data->fonts[i] = read_fsf_file(right_tokens[i]);

			/*did read_fsf_file succeed*/
			if(meme_data->fonts[i].name == NULL)
			{
				fprintf(stderr, "error (meme_parse_line): " 
				"error encountered read_fsf_file\n");
				return -1;
			}
		}
	}

	/*is this a FILE identifier*/
	else if((strcmp(left_tokens[1], "FILE") == 0) && left_num_tokens == 2)
	{
		/*there should be 1 right token*/
		if(right_num_tokens != 1)
		{
			fprintf(stderr, "meme_parse_line: invalid line " 
				"%s:%s\n", left, right);
			return -1;
		}
		/*try to find meme_id to store file name in*/
		else
		{
			current_meme_id = find_meme_id(meme_data, 
				left_tokens[0]);
			/*did we find the meme_id*/
			if(!current_meme_id)
			{
				fprintf(stderr, "meme_parse_line: invalid " 
					"line %s:%s\n", left, right);
				return -1;
			}
			/*assign image to meme_id*/
			current_meme_id->image = malloc((
				strlen(right_tokens[0]) + 1) * sizeof(char));
			strcpy(current_meme_id->image, right_tokens[0]);
		}
	}

	/*is this a text_id*/
	else if(right_num_tokens == 2 && left_num_tokens == 2)
	{
		/*find meme_id to add location to*/
		current_meme_id = find_meme_id(meme_data, 
			left_tokens[0]);
		/*did we find it*/
		if(!current_meme_id)
		{
			fprintf(stderr, "meme_parse_line: invalid line " 
				"%s:%s\n", left, right);
			return -1;
		}
		
		/*store current index*/
		l_index = current_meme_id->num_locations;
		/*increment num_locations*/
		current_meme_id->num_locations = current_meme_id->num_locations 
			+ 1;

		/*check num_locations vs max_locations*/
		if(current_meme_id->num_locations == max_locations)
		{
			max_locations += TOKEN_INCREASE_RATE;
			temp = realloc(current_meme_id->locations, 
				max_locations * sizeof(text_id));
			if(!temp)
			{
				fprintf(stderr, "mem_parse_line: failed to "
					"allocate memory\n");
				return -1;
			}
			current_meme_id->locations = temp;
		}

		/*store location data*/
		current_meme_id->locations[l_index].name = malloc(
			strlen(left_tokens[1] + 1) * sizeof(char));
		strcpy(current_meme_id->locations[l_index].name, 
			left_tokens[1]);
		current_meme_id->locations[l_index].x = atoi(right_tokens[0]);
		current_meme_id->locations[l_index].y = atoi(right_tokens[1]);
	}

	/*invalid line*/
	else
	{
		fprintf(stderr, "mem_parse_line: invalid line %s:%s\n", left, 
			right);
	}

	/*free memory*/
	free(right_tokens);
	free(left_tokens);

	/*return successfully*/
	return 0;
}

/**function used to parse an individual ACT file line and create necessary
 * structures and data and insert it into action_file * action_data
 * @param char * left: left part of ACT file line (before colon)
 * @param char * right: right part of ACT file line (after colon)
 * @param action_file * action_data: action_file structure to insert data into
 * @ret int: 0 = operation success, -1 = error(accompanied by print statement)
 * @author Adam Sunderman
 * @modified 03/05/2014 */
int act_parse_line(char * left, char * right, action_file * action_data)
{
	/*strings used to tokenize left and right strings using " " as the
 	* delimiter*/
	char** left_tokens = malloc(START_TOKENS * sizeof(char*));
	char** right_tokens = malloc(START_TOKENS * sizeof(char*));

	/*store number of right and left tokens*/
	int left_num_tokens, right_num_tokens;

	/*counters*/
	int i = 0, j = 0;

	/*tokenize line*/
	tokenize_line(left, right, left_tokens, right_tokens, &left_num_tokens, 
		&right_num_tokens);

	/*TODO some other stuff*/

	/*return successfully*/
	return 0;
}

/**function used to parse an individual FSF file line and create necessary
 * structures and data and insert it into font * font_data
 * @param char * left: left part of FSF file line (before colon)
 * @param char * right: right part of FSF file line (after colon)
 * @param font * font_data: font structure to insert data into
 * @ret int: 0 = operation success, -1 = error(accompanied by print statement)
 * @author Adam Sunderman
 * @modified 03/06/2014 */
int fsf_parse_line(char * left, char * right, font * font_data)
{
	/*strings used to tokenize left and right strings using " " as the
 	* delimiter*/
	char** left_tokens = malloc(START_TOKENS * sizeof(char*));
	char** right_tokens = malloc(START_TOKENS * sizeof(char*));

	/*temp string and character used to store substring and character of 
 	* CHARACTERc identifier*/
	char* character_temp;
	char c;

	/*store number of right and left tokens*/
	int left_num_tokens, right_num_tokens;

	/*int 0 = !CHARACTER'space' 1 = CHARACTER'space'*/
	int space = 0;

	/*counters*/
	int i = 0, j = 0;
	int c_index;

	/*max number of characters for currently allocated memory*/
	int max_characters = START_TOKENS;

	/*temp character * for reallocation*/
	character * temp;

	/*catch "Character'space'" condition pre_tokenize*/
	if(strcmp(left, "CHARACTER ") == 0)
	{
		space = 1;
	}

	/*tokenize line*/
	tokenize_line(left, right, left_tokens, right_tokens, &left_num_tokens, 
		&right_num_tokens);

	/*catch "Character'space'" condition post_tokenize*/
	if(space == 1)
	{
		left_num_tokens = 1;
		left_tokens[0] = "CHARACTER ";
	}

	/*temp string to store everyting but last character in left_tokens[0]
	* (to test for the word CHARACTER)*/
	character_temp = malloc(strlen(left_tokens[0]));
	strncpy(character_temp, left_tokens[0], (strlen(left_tokens[0])-1));
	c = left_tokens[0][strlen(left_tokens[0]) - 1];

	/*is it NAME?*/
	if(strcmp(left_tokens[0], "NAME") == 0 && left_num_tokens == 1)
	{
		/*There should only be one right_token*/
		if(right_num_tokens != 1)
		{
			fprintf(stderr, "fsf_parse_line: incorrect " 
				"format for line %s:%s\n", left, right);
			return -1;
		}
		/*else save font name*/
		else
		{
			font_data->name = malloc((strlen(right_tokens[0]) + 1) 
				* sizeof(char));
			strcpy(font_data->name, right_tokens[0]);
		}
	}

	/*is it IMAGE*/
	else if(strcmp(left_tokens[0], "IMAGE") == 0 && left_num_tokens == 1)
	{
		/*There should only be one right_token*/
		if(right_num_tokens != 1)
		{
			fprintf(stderr, "fsf_parse_line: incorrect " 
				"format for line %s:%s\n", left, right);
			return -1;
		}
		/*else save font image*/
		else
		{
			font_data->image = malloc((strlen(right_tokens[0] + 1)) 
				* sizeof(char));
			strcpy(font_data->image, right_tokens[0]);
		}
	}

	/*is it CHARACTER*/
	else if(strcmp(character_temp, "CHARACTER") == 0 && 
		left_num_tokens == 1)
	{
		/*there should be 4 right tokens (x y w h)*/
		if(right_num_tokens != 4)
		{
			fprintf(stderr, "error (fsf_parse_line): incorrect "
				"format for CHARACTER%c\n", c);
			return -1;
		}
		/*else save character structure*/
		else
		{
			/*store current index*/
			c_index = font_data->num_characters;

			/*increment num_characters*/
			font_data->num_characters = font_data->num_characters 
				+ 1;

			/*check num_characters vs max_characters*/
			if(font_data->num_characters == max_characters)
			{
				max_characters += TOKEN_INCREASE_RATE;
				temp = realloc(font_data->characters, 
					max_characters * sizeof(character));
				if(!temp)
				{
					fprintf(stderr, "fsf_parse_line: " 
						"failed to allocate memory\n");
					return -1;
				}
				font_data->characters = temp;
			}

			/*store character data*/
			font_data->characters[c_index].represented = c;
			font_data->characters[c_index].x = 
				atoi(right_tokens[0]);
			font_data->characters[c_index].y = 
				atoi(right_tokens[1]);
			font_data->characters[c_index].w = 
				atoi(right_tokens[2]);
			font_data->characters[c_index].h = 
				atoi(right_tokens[3]);
		}
	}

	/*invalid line*/
	else
	{
		fprintf(stderr, "fsf_parse_line: invalid line %s:%s\n", 
			left, right);
		return -1;
	}

	/*free memory*/
	free(left_tokens);
	free(right_tokens);

	/*return successfully*/
	return 0;
}

/**function used to tokenize arguments to the left and right of : in FSF,
 * MEM and ACT files
 * @param char * left: left string to tokenize
 * @param char * right: right string to tokenize
 * @param char ** left_tokens: pointer to strings containing tokenized left
 * line
 * @param char ** right_tokens: pointer to strings containting tokenized
 * right line
 * @param int * num_left_tokens: int to store number of left tokens
 * @param int * num_right_tokens: int to store number of right tokens
 * @ret int: 0 = operation success -1 = operation failure
 * @author Adam Sunderman
 * @modified 03/05/2014*/
int tokenize_line(char * left, char * right, char ** left_tokens, 
	char ** right_tokens, int * left_num_tokens, 
	int * right_num_tokens)
{
	/*temp pointer for realloc*/
	char** temp;

	/*ints to store max number of tokens*/
	int left_max_tokens = START_TOKENS;
	int right_max_tokens = START_TOKENS;

	/*counters*/
	int i = 0, j = 0;

	/*ints to store number of tokens in each input string*/
	*left_num_tokens = 0;
	*right_num_tokens = 0;

	/*store initial left token*/
	left_tokens[i] = strtok(left, " ");

	/*tokenize left*/
	while(left_tokens[i])
	{
		/*increment counters*/
		i++;
		(*left_num_tokens)++;

		/*if left_num_tokens is greater than our allocated memory we
 		* must re-allocate*/
		if(*left_num_tokens == left_max_tokens)
		{
			left_max_tokens += TOKEN_INCREASE_RATE;
			temp = realloc(left_tokens, left_max_tokens * 
				sizeof(char*));
			if(!temp)
			{
				fprintf(stderr, "mem_parse_line: failed to " 
					"allocate memory\n");
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
		(*right_num_tokens)++;

		/*if right_num_tokens is greater than our allocated memory we
 		* must re-allocate*/
		if(*right_num_tokens == right_max_tokens)
		{
			right_max_tokens += TOKEN_INCREASE_RATE;
			temp = realloc(right_tokens, right_max_tokens * 
				sizeof(char*));
			if(!temp)
			{
				fprintf(stderr, "mem_parse_line: failed to " 
					"allocate memory\n");
				return -1;
			}
			right_tokens = temp;
		}

		/*move onto next token (will be NULL if no more exist)*/
		right_tokens[j] = strtok(NULL, " ");
	}

	/*return successfully*/
	return 0;
}

/**Function used to return a text_id structure with name equal to the provided
 * string text_id
 * @param meme_id * meme: meme_id structure to look for text_id structure in
 * @param char * text_id: string that contains the name of a text_id structure
 * @ret text_id: returns a text_id object with name = to the provided string. 
 * will return default_return (name = NULL)  if the text_id was not found or if 
 * an error was encountered
 * @author: Adam Sunderman
 * @modified: 03/05/2014 */
text_id find_text_id(meme_id * meme, char * text_id_name)
{
	/*counter*/
	int i;

	/*default return text_id (represents failure)*/
	text_id default_return;
	default_return.name = "NULL";

	/*general error checking*/
	if(!meme)
	{
		fprintf(stderr, "find_text_id: meme_id is null\n");
		return default_return;
	}

	if(!text_id_name)
	{
		fprintf(stderr, "text_id string is null\n");
		return default_return;
	}

	/*look through locations within meme_id structure to find correct
 	* text_id structure and return it*/
	for(i = 0; i < meme->num_locations; i++)
	{
		if(strcmp(text_id_name, meme->locations[i].name) == 0)
		{
			return meme->locations[i];
		}
	}

	/*if we didn't find it then it doesn't exist: return NULL*/
	return default_return;
}

/**Function used to return a meme_id structure with name equal to the provided
 * string meme_id
 * @param meme_file * meme_data: meme_file structure to look for meme_id
 * structure
 * @param char * meme_id: string that contains the name of a meme_id structure
 * @ret meme_id *: returns a pointer to meme_id object with name = to the 
 * provided string. will return NULL if the meme_id was not found or if 
 * an error was encountered
 * @author: Adam Sunderman
 * @modified 03/05/2014 */
meme_id * find_meme_id(meme_file * meme_data, char * meme_id_name)
{
	/*counter*/
	int i;

	/*general error checking*/
	if(!meme_data)
	{
		fprintf(stderr, "find_meme_id: meme_file structure is null\n");
		return NULL;
	}

	if(!meme_id_name)
	{
		fprintf(stderr, "meme_id string is null\n");
		return NULL;
	}

	/*look through meme_id's within meme_file structure to find correct
 	* meme_id structure and return it*/
	for(i = 0; i < meme_data->num_memes; i++)
	{
		if(strcmp(meme_id_name, meme_data->memes[i].name) == 0)
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
