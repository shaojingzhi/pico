#include "types.h"
#include "stat.h"
#include "user.h"

#define WIDTH 80
#define HEIGHT 25
#define TOTAL_CHARS 1920
#define C(x)  ((x)-'@')  // Control-x

#define UI_COLOR 0xc0
#define TEXT_COLOR 0x07

char buf[TOTAL_CHARS];
// static int lastChar;

void
printfile(int fd)
{
	int n;

	while((n = read(fd, buf, TOTAL_CHARS)) > 0) {
		// if (write(1, buf, n) != n) {
		// 	printf(1, "Write error\n");
		// 	return;
		// }
		updatesc(0, 1, buf, TEXT_COLOR);
	}
	if(n < 0){
		printf(1, "Read error\n");
		return;
	}
	close(fd);
}

void
drawHeader() {
	updatesc(0, 0, "                              ", UI_COLOR);
	updatesc(30, 0, "        PICO        ", UI_COLOR);
	updatesc(50, 0, "                         v0.1 ", UI_COLOR);
}

void
drawFooter() {
	updatesc(0, 24, " PRESS ENTER TO CLOSE                                                           ", UI_COLOR);
}

void
handleInput() {
	updatesc(0, 1, "new input!", TEXT_COLOR);
	// printf(1, "new input");
}

int
main(int argc, char *argv[]) {
	printf(1, "%p", handleInput);
	captsc(handleInput);
	drawHeader();
	drawFooter();

	int fd;

	if (argc == 2) {
		if((fd = open(argv[1], 0)) < 0){
			printf(1, "Cannot open %s\n", argv[1]);
		} else {
			printfile(fd);
		}
	} else {
		printf(1, "No file selected");
	}
	read(0, 0, 100);
	freesc();

	exit();
}