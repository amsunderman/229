#include "meme_file_util.h"

#define NUM_ARGUMENTS 3
#define ARGUMENT_FORMAT "meme memefile.mem action.act"

int main(int argc, char ** argv)
{
	/*integer that stores error values*/
	int err, i, j;

	/*structure that stores MEM file data*/
	meme_file * meme_data = malloc(sizeof(meme_file));

	/*structure that stores ACT file data*/
	action_file * action_data = malloc(sizeof(action_file));

	/*file pointer to MEM file*/
	FILE * meme_file;

	/*file pointer to ACT file*/
	FILE * act_file;
	

	/*check for correct number of arguments*/
	if(argc != NUM_ARGUMENTS)
	{
		fprintf(stderr, "error (meme): incorrect # of command line " 
			"arguments\n");
		fprintf(stderr, "meme: expected format: ");
		fprintf(stderr, ARGUMENT_FORMAT);
		fprintf(stderr, "\nmeme: exiting program\n");
		return -1;
	}

	/*parse arguments*/
	meme_file = fopen(argv[1], "r+");
	act_file = fopen(argv[2], "r+");

	/*read MEM file*/
	err = read_mem_file(meme_file, meme_data);

	if(err)
	{
		fprintf(stderr, "error (meme): error encountered " 
			"(read_mem_file)\n");
		fprintf(stderr, "meme: exiting program\n");
		return -1;
	}

	/*read ACT file*/
	err = read_act_file(act_file, action_data);

	if(err)
	{
		fprintf(stderr, "error (meme): error encountered " 
			"(read_act_file)\n");
		fprintf(stderr, "meme: exiting program\n");
		return -1;
	}

	/*TESTING*/

	meme_id * ret;

	for(j = 0; j < meme_data->num_memes; j++)
	{

	ret = &(meme_data->memes[j]);

	printf("%s %s\n", ret->name, ret->image);

        for(i = 0; i < ret->num_locations; i++)
        {
                printf("%s %s:%d %d\n", ret->name, ret->locations[i].name,
                        ret->locations[i].x, ret->locations[i].y);
        }

	}

	printf("\n%s %s\n", meme_data->fonts[0].name, meme_data->fonts[0].image);

        for(i = 0; i < meme_data->fonts[0].num_characters; i++)
        {
                printf("%c %d %d %d %d\n", meme_data->fonts[0].characters[i].represented, 
                meme_data->fonts[0].characters[i].x, meme_data->fonts[0].characters[i].y, 
                meme_data->fonts[0].characters[i].w, meme_data->fonts[0].characters[i].h);
        }

	printf("\n");
	printf("%s %s %s\n", action_data->out, action_data->meme_id, 
		action_data->font_id);
	for(i = 0; i < action_data->num_actions; i++)
	{
		printf("%s %s\n", action_data->actions[i].text_id, 
			action_data->actions[i].message);
	}

	/*ENDTESTING*/

	/*TODO execute actions*/

	/*return successfully*/
	return 0;
}
