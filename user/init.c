// init: The initial user-level program

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"
// why not use some other hash function: MD5, SHA-1, SHA-256, etc?
// bcrypt is slow and resource intensive
// work factor
#include "bcrypt.h"

// We are handling only a single user case
// Case 1: password is already set
// Case 2: password needs to be set
// write(fd, buf, n) Write n bytes to an open file

void getPassword(char* buf) {
// read(fd, buf, n) : Reads at most n bytes from a file descriptor into buffer
  printf(0, "Here's your password: %s", buf);
}

// int strcmp(const char *p, const char *q)
void comparePassword(const char *p, const char *q) {}

// uchar * bcrypt(const char *pass, const uchar *salt);

// int bcrypt_checkpass(const char *pass, const uchar *salt, const uchar *goodhash);


char *argv[] = {"sh", 0};

int main(void) {
  int pid, wpid;
  printf(1, "init: HERE\n");

  // that seems to be a good place to type our password in...
  if (open("console", O_RDWR) < 0) {
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }

  dup(0); // stdout
  dup(0); // stderr

  // how do we know if the password has already been created

  // open(filename, flags)

  // Open a file; the flags indicate read/write

  // O_RDONLY: opens the file in read only mode

  // O_CREATE: flag creates a new data file

  // from xv6 book fd = open("/dir/file", O_CREATE|O_WRONLY);

  // the size of int is 4 bytes or 32 bits
  // look at sys_random() in sysproc.c

  int randomSaltVal[4];

  uchar saltBuf[BCRYPT_SALTLEN];

  uchar hashBuf[BCRYPT_HASHLEN];

  /* Case 1: the password is not set
   * enter the password
   * reenter the password
   * looks good?
   * generate salt (what's the point ?) - same passwords & dictionary attacks
   * Hint on using bcrypt: uchar *hashpasswd = bcrypt(password, (uchar *)salt_array);
   * write hash and salt to the file
   */

  /* Case 2: the password is set
   * it seems like the user already has a password
   * what is it?
   * what do we have on file?
   * is it the correct password?
   * should we allow the user to proceed?
   */

  // this code seems to be starting the shell, we should make sure that
  // unauthorized user doesn't get here
  for (;;) {
    printf(1, "init: starting sh\n");
    pid = fork();
    if (pid < 0) {
      printf(1, "init: fork failed\n");
      exit();
    }
    if (pid == 0) {
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while ((wpid = wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
