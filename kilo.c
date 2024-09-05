#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode(void){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(void){
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(IXON | ICRNL | INPCK | ISTRIP | BRKINT);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_lflag |= (CS8);
  raw.c_lflag &= ~(OPOST);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void){
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
    if (iscntrl(c)){
      printf("%d\r\n", c);
    }
    else{
      printf("%d ('%c')\r\n", c, c);
    }
  }

  return 0;
}
