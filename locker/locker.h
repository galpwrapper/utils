#ifndef _LOCKER_H
#define _LOCKER_H

#include <sys/file.h>
#include <stdio.h>
#include <string>

/*********************************************************************
This class is designed to lock a root file while one routine using it
*********************************************************************/
class locker {
public:
  FILE *file;
  int fd;
  bool available;

  locker(const std::string &filename, int lock_type);
  void unlock();
};

#endif // for #ifndef _LOCKER_H
