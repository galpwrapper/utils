#include "locker.h"
#ifdef NO_ROOT
#include <fstream>
#else
#include "TFile.h"
#endif

#include <iostream>

using namespace std;

locker::locker(const string &filename, int lock_type, const string& filetype) : file(0), fd(0), available(true) {
  if (LOCK_SH == lock_type) {
    file = fopen(filename.c_str(), "r");

    if (!file) {
      cout << "File " << filename << " unexist, do nothing" << endl;
      available = false;
      return;
    }
  } else if (LOCK_EX == lock_type)
    file = fopen(filename.c_str(), "a+");

  fd = fileno(file);
  flock(fd, lock_type);

  if (LOCK_EX == lock_type) {
#ifndef NO_ROOT
    char ch;
    if (filetype == "ROOT" && fscanf(file, "%c", &ch) == EOF) {
      TFile fnew(filename.c_str(), "RECREATE");
      fnew.Close();
    }
#endif
  }
}

void locker::unlock() {
  if (!available) return;
  flock(fd, LOCK_UN);
  fclose(file);
  available = false;
}

locker::~locker() { unlock(); }
