#include "locker.h"
#ifdef NO_ROOT
#include <fstream>
#else
#include "TFile.h"
#endif

#include <iostream>

using namespace std;

locker::locker(const string &filename, int lock_type) : file(0), fd(0), available(true) {
  file = fopen(filename.c_str(), "r");
  if (!file) {
    if (LOCK_EX == lock_type) {
#ifdef NO_ROOT
      ofstream(filename.c_str());
#else
      TFile fnew(filename.c_str(), "UPDATE");
      fnew.Close();
#endif
      file = fopen(filename.c_str(), "r");
    } else {
      cout << "File " << filename << " unexist, do nothing" << endl;
      available = false;
      return;
    }
  }

  fd = fileno(file);
  flock(fd, lock_type);
}

void locker::unlock() {
  if (!available) return;
  flock(fd, LOCK_UN);
  fclose(file);
  available = false;
}

locker::~locker() { unlock(); }
