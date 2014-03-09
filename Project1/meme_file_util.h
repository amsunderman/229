#ifndef MEME_FILE_UTIL
#define MEME_FILE_UTIL

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef SIMP_UTIL
#define SIMP_UTIL
#include "simp_util.h"
#endif

/*typedef'd structure to store the information for a specific character in a FSF
 * file*/
typedef struct character_struct
{
	char represented;
	int x, y, w, h;
}character;

/*typedef'd structure to store the data collected from a FSF file*/
typedef struct font_struct
{
	char* name;
	char * image;
	character * characters; /*character typedef'd above*/
	int num_characters;
}font;

/*typedef'd structure to store the information for a specific test_id in a MEM
 *file*/
typedef struct text_id_struct
{
	char * name;
	int x, y;
}text_id;

/*typedef'd structure to store the information for a specific meme_id in a MEM
 * file*/
typedef struct meme_id_struct
{
	char * name;
	char * image;
	text_id * locations; /*text_id typedef'd above*/
	int num_locations;
}meme_id;

/*typedef'd structure to store the information collected from a MEM file*/
typedef struct meme_file_struct
{
	meme_id * memes; /*meme_id typedef'd above*/
	font * fonts;
	int num_memes;
	int num_fonts;
}meme_file;

/*typedef'd structure to store an action*/
typedef struct action_struct
{
	char* text_id;
	char* message;
}action;

/*typedef'd structure to store the information collected from a ACT file*/
typedef struct action_file_struct
{
	char* out;
	char* meme_id;
	char* font_id;
	action * actions; /*action typedef'd above*/
	int num_actions;
}action_file;

/*function used to read data stored in MEM file and store it in the meme_file
 * structure*/
int read_mem_file(FILE * fp, meme_file * meme_data);

/*function used to read data stored in a ACT file and store it in the
 * action_file structure*/
int read_act_file(FILE * fp, action_file * action_data);

/*function used to read data stored in a FSF file and store it in a font
 * structure*/
font read_fsf_file(char * fsf_file_name);

/*function used to parse an individual MEM file line and create necessary
 * structures and data and insert it into meme_file * meme_data*/
int mem_parse_line(char * left, char * right, meme_file * meme_data);

/*function used to parse an individual ACT file line and create necessary
 * structures and data and insert it into action_file * action_data*/
int act_parse_line(char * left, char * right, action_file * action_data);

/*function used to parse an individual FSF file line and create necessary
 * structures and data and insert it into font * font_data*/
int fsf_parse_line(char * left, char * right, font * font_data);

/*function used to tokenize arguments to the left and right of : in FSF,
 * MEM and ACT files*/
int tokenize_line(char * left, char * right, char ** left_tokens, 
	char ** right_tokens, int * left_num_tokens, 
	int * right_num_tokens);

/*function used to return a text_id structure with name equal to the provided 
 * string text_id*/
text_id find_text_id(meme_id * meme, char * text_id);

/*Function used to return a meme_id structure with name equal to the provided
 * string meme_id*/
meme_id * find_meme_id(meme_file * meme_data, char * meme_id);

/*Function used to execute ACT file actions*/
int execute_actions(meme_file * meme_data, action_file * action_data);

/*Function used to load font contained in the meme_data structure*/
struct simp_file * load_font();

/*Function used to load a simp_image into the simp_file structure defined in
 * simp_util.h from the meme_data structure*/
struct simp_file * load_meme();

#endif
