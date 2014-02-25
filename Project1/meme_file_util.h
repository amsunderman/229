#ifndef MEME_FILE_UTIL
#define MEME_FILE_UTIL

#ifndef STDIO
#define STDIO
#include <stdio.h>
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
	struct simp_file * image; /*struct defined in simp_util.h*/
	character * characters; /*character typedef'd above*/
}font;

/*typedef'd structure to store the information for a specific test_id in a MEM
 *  * file*/
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
	struct simp_file * image; /*struct defined in simp_util.h*/
	text_id * locations; /*text_id typedef'd above*/
}meme_id;

/*typedef'd structure to store the information collected from a MEM file*/
typedef struct meme_file_struct
{
	meme_id * memes; /*meme_id typedef'd above*/
	font * fonts;
}meme_file;

/*typedef'd structure to store the information collected from a ACT file*/
typedef struct action_file_struct
{
	struct simp_file * out; /*struct defined in simp_util.h*/
	char* meme_id;
	char* font_id;
	char* text_id;
}action_file;

/*function used to read data stored in MEM file and store it in the meme_file
 * structure*/
int read_mem_file(FILE * fp, meme_file * meme_data);

/*function used to read data stored in a ACT file and store it in the
 * action_file structure*/
int read_act_file(FILE * fp, action_file * action_data);

/*function used to return a text_id structure with name equal to the provided 
 * string text_id*/
text_id find_text_id(meme_id * meme, char * text_id);

/*Function used to return a meme_id structure with name equal to the provided
 * string meme_id*/
meme_id find_meme_id(meme_file * meme_data, char * meme_id);

/*Function used to load font contained in the meme_data structure*/
struct simp_file load_font();

/*Function used to load a simp_image into the simp_file structure defined in
 * simp_util.h from the meme_data structure*/
struct simp_file load_meme();

#endif
