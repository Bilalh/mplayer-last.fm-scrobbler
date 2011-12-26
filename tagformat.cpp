// Prints the tags of a audio file
// mp3, m4a ogg and flac supported

// Bilal Hussain

// install:
//  g++ `taglib-config  --cflags --libs`  tagformat.cpp  -o tagformat
// or
// g++ -ltag -I/usr/local/include/taglib -L/usr/local/lib  tagformat.cpp  -o tagformat
// if no taglib-config

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tag.h>
#include <fileref.h>

void usage() {
	fprintf(stderr, "tagformat [--notime] <files> \n");
}

int main(int argc, char *argv[]) {
	if(argc <= 1) {
		usage();
		exit(1);
	}
	int start = 1; bool showTimes = true;
	if (strcmp(argv[1], "--notime" ) == 0 || strcmp(argv[1], "-n" ) ==0 ){
		showTimes = false;
	}
	
	for(int i = start; i < argc; i++) {
		TagLib::FileRef f(argv[i]);
		if (f.isNull()){
			fprintf(stderr, "Error opening file: %s\n", argv[i]);
			continue;
		}
		
		const int end_time = f.audioProperties()->length();
		printf("%02d %s",
				f.tag()->track(),
				f.tag()->title().toCString(true)
			  );
			
		if (showTimes) printf(" %d:%02d\n", (end_time % 3600 / 60), (end_time % 60));
		else           puts("");
	 }
	return 0;
}
