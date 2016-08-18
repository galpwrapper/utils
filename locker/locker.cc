#include "locker.h"
#include "TFile.h"

#include <iostream>

using namespace std;

locker::locker(const string &filename, int lock_type) : file(0), fd(0), available(true) {
  file = fopen(filename.c_str(), "r");
  if (!file) {
    if (LOCK_EX == lock_type) {
      TFile fnew(filename.c_str(), "UPDATE");
      fnew.Close();
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
