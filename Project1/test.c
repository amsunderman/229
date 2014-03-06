#include "meme_file_util.h"

int main(int argc, char ** argv)
{
	FILE * fp = fopen((argv[1]), "r+");
	meme_file * meme_data = malloc(sizeof(meme_file));

	read_mem_file(fp, meme_data);

	meme_id ret;
	ret = find_meme_id(meme_data, "KEANU");
	printf("Found it: %s\n", ret.name);

	fclose(fp);
	free(meme_data);
}
