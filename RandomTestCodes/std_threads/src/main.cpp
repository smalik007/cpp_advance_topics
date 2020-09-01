/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int main() {
//   cout << "Hello\n";
//   std::vector<int> num;
//   num.push_back(1);
//   num.push_back(2);
//   num.push_back(3);

//   std::cout << "Size :" << num.size() << endl;

//   num.clear();
//   std::cout << "Size :" << num.size() << endl;

//   double v0 = 0.57;
//   double v1 = 0.81;
//   double v2 = 0.2;

//   double max = std::max({v0, v1, v2}, [](const double a, const double b) { return a < b; });
//   cout << max << endl;

//   return 0;
// }

#include <math.h>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread() {
  // Wait until main() sends data
  std::unique_lock<std::mutex> lk(m);
  cv.wait(lk, [] { return ready; });

  // after the wait, we own the lock.
  std::cout << "Worker thread is processing data\n";
  data += " after processing";

  // Send data back to main()
  processed = true;
  std::cout << "Worker thread signals data processing completed\n";

  // Manual unlocking is done before notifying, to avoid waking up
  // the waiting thread only to block again (see notify_one for details)
  lk.unlock();
  cv.notify_one();
}

int main() {
  std::thread worker(worker_thread);

  double value = -5.9;
  int div = 2;
  std::cout << abs(value) << std::endl;
  std::cout << fabs(value) << std::endl;
  std::cout << fabs(value / div) << std::endl;
  data = "Example data";
  // send data to the worker thread
  {
    std::lock_guard<std::mutex> mlock(m);
    // std::lock_guard<std::mutex> lk(m);
    ready = true;
    std::cout << "main() signals data ready for processing\n";
  }
  cv.notify_one();

  // wait for the worker
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return processed; });
  }
  std::cout << "Back in main(), data = " << data << '\n';

  worker.join();
}
