// Prints the tag of a audio file 
// mp3 m4a ogg and flac supported

// Bilal Hussain

// install:
//  g++ `taglib-config  --cflags --libs`  taginfo.cpp  -o taginfo
// or 
// g++ -ltag -I/usr/local/include/taglib -L/usr/local/lib  taginfo.cpp  -o taginfo
// if no taglib-config

#include <stdio.h>

#include <tag.h>
#include <fileref.h>
#include <string.h>

using namespace std;

void usage() {
	fprintf(stderr, "taginfo \n");
	fprintf(stderr, "Usage: taginfo <file(s)>\n");
	fprintf(stderr, "Usage: taginfo --short <file>\n");
	fprintf(stderr, "Usage: taginfo --info <file>\n");
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		usage();
		exit(1);
	}

	if (argc == 3  && strcmp("--short", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		
		printf("%s\n", f.tag()->title().toCString(true));
		printf("%s\n", f.tag()->album().toCString(true));
		printf("%s\n", f.tag()->artist().toCString(true));
		int time = f.audioProperties()->length();
		printf("%d:%d\n", (time%3600/60), (time%60) );
		exit(0);
	}

	if (argc == 3  && strcmp("--info", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		
		printf("%s - %02d %s - %s\n", 
			f.tag()->artist().toCString(true),
			f.tag()->track(),
			f.tag()->title().toCString(true),
			f.tag()->album().toCString(true)
		);
		exit(0);
	}

	for(int i = 1; i < argc; i++) {
		TagLib::FileRef f(argv[i]);
		if(!f.isNull() && f.tag()) {
			printf("FILE=\"%s\"\n", argv[i]);
			printf("ALBUM=\"%s\"\n", f.tag()->album().toCString(true));
			printf("TRACK=\"%d\"\n", f.tag()->track());
			printf("ARTIST=\"%s\"\n", f.tag()->artist().toCString(true));
			printf("TITLE=\"%s\"\n", f.tag()->title().toCString(true));
			printf("GENRE=\"%s\"\n", f.tag()->genre().toCString(true));
			printf("YEAR=\"%d\"\n", f.tag()->year());
			printf("COMMENT=\"%s\"\n", f.tag()->comment().toCString(true));
			printf("LENGTH=\"%d\"\n", f.audioProperties()->length());
			printf("BITRATE=\"%d\"\n", f.audioProperties()->bitrate());
			printf("SAMPLERATE=\"%d\"\n", f.audioProperties()->sampleRate());
			printf("CHANNELS=\"%d\"\n\n", f.audioProperties()->channels());
		} else {
			fprintf(stderr, "Error opening file: %s\n", argv[i]);
		}
	}

	return 0;
}
