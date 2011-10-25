#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define FIFO_NAME   "/Users/bilalh/.mplayer/pipe"
#define FIFO_OUTPUT "~/.mplayer/output"
#define SCRIPT      "lastfm_from_mplayer_output.rb"
#define INFO        "audio_info_display.rb"
static const char *command  = "get_percent_pos\n";


int main (int argc, char const *argv[]) {
	const int command_length = strlen(command);
	
	int fd = open(FIFO_NAME, O_WRONLY);
	FILE *fp;
	char buff[27], *c;
	long pos =0;
	bool current_done = false;
	
	while(true){
		// write to the pipe.
		write(fd, command, command_length);
		usleep(300000);
		
		// get result of tail.
		fp = popen("tail -n1 " FIFO_OUTPUT , "r");
		fgets(buff, sizeof(buff)-1, fp);
		pclose(fp);
		// get the postion as a %.
		c = buff;
		while(c){
			if (*c=='='){
				pos = strtol(c+1, NULL, 10);
				// printf("%ld\n", pos);
				break;
			}
			c++;
		}
		
		if (pos < 3){
			system(INFO);
		}
		
		// scrobble to lastfm.
		if (!current_done && pos >= 50) {
			system(SCRIPT);
			current_done = true;
		}
		// we are on the next track.
		else if (current_done  && pos <50) {
			current_done = false;
		}
		
		
		sleep(5);
	}
	return 0;
}