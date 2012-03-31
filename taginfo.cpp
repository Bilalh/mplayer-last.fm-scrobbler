// Prints the tag of a audio file 
// mp3, m4a ogg and flac supported

// Bilal Hussain

// install:
//  g++ `taglib-config  --cflags --libs`  taginfo.cpp  -o taginfo
// or 
// g++ -ltag -I/usr/local/include/taglib -L/usr/local/lib  taginfo.cpp  -o taginfo
// if no taglib-config

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tag.h>
#include <fileref.h>
#include <string>

#include <mp4tag.h> 
#include <mp4file.h>

#include <mpegfile.h>
#include <id3v2tag.h> 
#include <id3v2frame.h>

void usage() {
	fprintf(stderr, "taginfo \n");
	fprintf(stderr, "Usage: taginfo <file(s)>\n");
	fprintf(stderr, "Usage: taginfo --short   <file>\n");
	fprintf(stderr, "Usage: taginfo --info    <file>\n");
	fprintf(stderr, "Usage: taginfo --pretty  <file> \n");
	fprintf(stderr, "Usage: taginfo --pretty  <file> <current_secs>\n");
	fprintf(stderr, "Usage: taginfo --details <file> <current_secs>\n");
	fprintf(stderr, "Usage: taginfo --details-colour <file> <current_secs>\n");	
	fprintf(stderr, "Usage: taginfo --short2  <mp3|m4a>\n");
}

// adds %s before and after
#define SSS(str) "%s" str "%s"
#define S3 "%s%s%s"
#define BLUE         "\033[34m"             // Blue 
#define RED          "\033[31m"             // Red 
#define GREEN        "\033[32m"             // Green 
#define RESET        "\033[0m"              // Needed before and after colours
#define COLOUR(string, colour)  RESET colour, string, RESET
#define COLOURN(string, colour) string


bool endsWith (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


int main(int argc, char *argv[]) {
	if(argc < 2) {
		usage();
		exit(1);
	}

	if (argc == 3  && strcmp("--short", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		if (f.isNull()) exit(1);
		printf("%s\n", f.tag()->title().toCString(true));
		printf("%s\n", f.tag()->album().toCString(true));
		printf("%s\n", f.tag()->artist().toCString(true));
		int time = f.audioProperties()->length();
		printf("%d:%d\n", (time%3600/60), (time%60) );
		exit(0);
	}

	// --short with disk number
	else if (argc == 3  && strcmp("--short2", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		if (f.isNull()) exit(1);
		printf("%s\n", f.tag()->title().toCString(true));
		printf("%s\n", f.tag()->album().toCString(true));
		printf("%s\n", f.tag()->artist().toCString(true));
		int time = f.audioProperties()->length();
		printf("%d:%d\n", (time%3600/60), (time%60) );
		printf("%d\n", f.tag()->track());
		
		int disc_number = -1;
		std::string path(argv[2]);
		if (endsWith(path,".m4a") || endsWith(path,".mp4")){
		    // MPEG::File m4a
			TagLib::MP4::File mp4(argv[2]);
			TagLib::MP4::Tag * const t = mp4.tag();
			const TagLib::MP4::ItemListMap &map =  t->itemListMap();
			if (!map.contains("disk")){
				fprintf(stderr, "%s has no disk number\n", argv[2]);	
				exit(1);
			}
			const TagLib::MP4::Item::IntPair discs  =  map["disk"].toIntPair();
			disc_number = discs.first;
		}else if (endsWith(path,".mp3")){
			TagLib::MPEG::File mp3(argv[2]);
			const TagLib::ID3v2::Tag *tag =mp3.ID3v2Tag();
			TagLib::ID3v2::FrameList l = tag->frameList("TPOS");
			TagLib::String temp = l.front()->toString();
			disc_number = temp.toInt();
			if (disc_number==0){
				fprintf(stderr, "%s has no disk number\n", argv[2]);	
				exit(1);
			}
		}else{
			fprintf(stderr, "%s is not mp3/m4a a file\n", argv[2]);	
			exit(1);
		}
		printf("%d\n", disc_number);
		exit(0);
	}

	else if (argc == 3  && strcmp("--info", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		if (f.isNull()) exit(1);
		printf("%s - %02d %s - %s\n", 
			f.tag()->artist().toCString(true),
			f.tag()->track(),
			f.tag()->title().toCString(true),
			f.tag()->album().toCString(true)
		);
		exit(0);
	}
	
	else if (argc == 4  && strcmp("--details", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		if (f.isNull()) exit(1);
		long start_time = strtol(argv[3],NULL,10);
		const int end_time = f.audioProperties()->length();
		
		printf("%s - %02d %s - %s -  %ld:%02ld/%d:%02d\n", 
			f.tag()->artist().toCString(true),
			f.tag()->track(),
			f.tag()->title().toCString(true),
			f.tag()->album().toCString(true),
			(start_time%3600/60), (start_time%60),
			(end_time%3600/60),   (end_time%60)
		);
		exit(0);
	}
	
	else if (argc == 4  && strcmp("--details-colour", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		if (f.isNull()) exit(1);
		long start_time = strtol(argv[3],NULL,10);
		const int end_time = f.audioProperties()->length();
				
		printf("%s - %02d " SSS("%s") " - %s -  %ld:%02ld/%d:%02d\n", 
			f.tag()->artist().toCString(true),
			f.tag()->track(),
			COLOUR(f.tag()->title().toCString(true),BLUE),
			f.tag()->album().toCString(true),
			(start_time%3600/60), (start_time%60),
			(end_time%3600/60),   (end_time%60)
		);
		exit(0);
	}
	
	else if (argc == 4  && strcmp("--pretty", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		if (f.isNull()) exit(1);
		long start_time = strtol(argv[3],NULL,10);
		const int end_time = f.audioProperties()->length();
		
		
	 // Track : Faraway ★★★★★
	 // Album : Album
	 // Artist: Artist
	 // Time  : 5:00/5:84
		printf(
			"Track  : %d - " S3 "\n"
			"Album  : %s\n"
			"Artist : %s\n"
			"Time   : %ld:%02ld/%d:%02d\n",
			
			f.tag()->track(), COLOUR(f.tag()->title().toCString(true),BLUE),
			f.tag()->artist().toCString(true),
			f.tag()->album().toCString(true),
			
			(start_time%3600/60), (start_time%60), (end_time%3600/60), (end_time%60)
		);
		
		exit(0);
	}

	else if (argc == 3  && strcmp("--pretty", argv[1]) == 0){
		TagLib::FileRef f(argv[2]);
		if (f.isNull()) exit(1);
		const int end_time = f.audioProperties()->length();
		
		
	 // Track : Faraway ★★★★★
	 // Album : Album
	 // Artist: Artist
	 // Time  : 5:00
		printf(
			"Track  : %d - " S3 "\n"
			"Album  : %s\n"
			"Artist : %s\n"
			"Time   : %d:%02d\n",
			
			f.tag()->track(), COLOUR(f.tag()->title().toCString(true),BLUE),
			f.tag()->artist().toCString(true),
			f.tag()->album().toCString(true),
			(end_time%3600/60), (end_time%60)
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
