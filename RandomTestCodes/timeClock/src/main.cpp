/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
using namespace std;

int main() {
  struct timeval packetSentTime;
  uint64_t packetSentTimestamp = 0;

  struct timespec ts;

  while (true) {
    // gettimeofday(&packetSentTime, NULL);
    // packetSentTimestamp = ((packetSentTime.tv_sec) * 1000 + (packetSentTime.tv_usec) / 1000);
    // packetSentTimestamp = (packetSentTime.tv_sec);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    packetSentTimestamp = (ts.tv_sec * 1000) + (ts.tv_nsec * 1e-6);
    cout << "\nTime : " << packetSentTimestamp << endl;
    usleep(1000000);
  }

  return 0;
}
