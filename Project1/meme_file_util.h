#ifndef MEME_FILE_UTIL_H
#define MEME_FILE_UTIL_H

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

/*typedef'd structure to store the data collected from a FSF file*/
typedef struct font_struct
{
	char* name;
	struct simp_file * image; /*struct defined in simp_util.h*/
	character * characters; /*character typedef'd below*/
}font;

/*typedef'd structure to store the information for a specific character in a FSF
 * file*/
typedef struct character_struct
{
	char represented;
	int x, y, w, h;
}character;

/*typedef'd structure to store the information collected from a MEM file*/
typedef struct meme_file_struct
{
	meme_id * memes; /*meme_id typedef'd below*/
	font * fonts;
}meme_file;

/*typedef'd structure to store the information for a specific meme_id in a MEM
 * file*/
typedef struct meme_id_struct
{
	char * name;
	struct simp_file * image; /*struct defined in simp_util.h*/
	text_id * locations; /*text_id typedef'd below*/
}meme_id

/*typedef'd structure to store the information for a specific test_id in a MEM
 * file*/
typedef struct text_id_struct
{
	char * name;
	int x, y;
}text_id

typedef struct action_file_struct
{
	/*TODO*/
}action_file;

#endif
