/* This is needed to allow parser-125k and zip-test to be compiled with CLANG */
#include <stdint.h>
#include <sys/types.h>

size_t write (int fd, void* buf, size_t cnt)
{
  return -1; /* error */
}

size_t read(int fd, void *buf, size_t cnt)
{
  return -1; /* error */
}
 
int close(int fd)
{
  return -1; /* error */
}

int open(const char* Path, int flags)
{
  return -1; /* error */
}

int lseek(int fd, off_t n, int whence)
{
  return -1; /* error */
}
