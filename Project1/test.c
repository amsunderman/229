#include "meme_file_util.h"

int main(int argc, char ** argv)
{
	FILE * fp = fopen((argv[1]), "r+");
	meme_file * meme_data = malloc(sizeof(meme_file));

	read_mem_file(fp, meme_data);

	fclose(fp);
	free(meme_data);
}
