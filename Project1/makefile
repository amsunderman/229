#makefile to ensure Project1(A) is up to date
#usage: simply type "make" to compile files that need
#recompiled; use make clean to remove .o and executable
#files.

#compiler to use
CC=gcc

#options to pass to compiler
CFLAGS=-ansi -pedantic -g

#all executables
ALL=crop bw colorshift overlay meme

all: $(ALL)

#executables
crop: crop.o simp_util.o
	$(CC) $(CFLAGS) -o crop crop.o simp_util.o
bw: bw.o simp_util.o
	$(CC) $(CFLAGS) -o bw bw.o simp_util.o
colorshift: colorshift.o simp_util.o
	$(CC) $(CFLAGS) -o colorshift colorshift.o simp_util.o
overlay: overlay.o simp_util.o
	$(CC) $(CFLAGS) -o overlay overlay.o simp_util.o
meme: meme.o meme_file_util.o simp_util.o
	$(CC) $(CFLAGS) -o meme meme.o meme_file_util.o simp_util.o

#object files
meme_file_util.o: meme_file_util.c meme_file_util.h
	$(CC) $(CFLAGS) -c meme_file_util.c
simp_util.o: simp_util.c simp_util.h
	$(CC) $(CFLAGS) -c simp_util.c
crop.o: crop.c
	$(CC) $(CFLAGS) -c crop.c
bw.o: bw.c
	$(CC) $(CFLAGS) -c bw.c
colorshift.o: colorshift.c
	$(CC) $(CFLAGS) -c colorshift.c
overlay.o: overlay.c
	$(CC) $(CFLAGS) -c overlay.c
meme.o: meme.c
	$(CC) $(CFLAGS) -c meme.c

#cleanup files
#clean removes all execs as well as object files
#while clean objects leaves execs
cleanobjects:
	rm -f *.o
clean:
	rm -f $(ALL) *.o
