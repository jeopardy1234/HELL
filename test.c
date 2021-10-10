// #include <ctype.h>
// #include <errno.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <termios.h>
// #include <unistd.h>
// #include <time.h>
// struct termios orig_termios;
// void die(const char *s) {}
// void disableRawMode() {
//   if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
//     die("tcsetattr");
// }
// void enableRawMode() {
//   if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
//   atexit(disableRawMode);
//   struct termios raw = orig_termios;
//   raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
//   raw.c_oflag &= ~(OPOST);
//   raw.c_cflag |= (CS8);
//   raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
//   raw.c_cc[VMIN] = 0;
//   raw.c_cc[VTIME] = 1;
//   if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
// }
// int main() {
//   enableRawMode();
//   int t_before = time(NULL);
//   while (1) {
//     int t_after = time(NULL);
//     if(t_after - t_before >= 0)
//     {
//         char c = '\0';
//         if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
//         if (iscntrl(c)) {
//             printf("%d\r\n", c);
//         } else {
//             printf("%d ('%c')\r\n", c, c);
//         }
//         if (c == 'q') break;
//         if (c == 'a')disableRawMode();
//         t_before = t_after;
//     }
//   }
//   return 0;
// }