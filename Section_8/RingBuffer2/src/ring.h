/*
 * Description - RingBuffer.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-29 19:54:38
 *
 */

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>

using namespace std;

template <typename T>
class RingBuffer {
 private:
  int32_t _maxSize;
  std::unique_ptr<T[]> _pData;
  int32_t _front;
  int32_t _rear;

  std::mutex mutexLock;

 public:
  std::condition_variable dataCondition;
  typedef std::shared_ptr<RingBuffer<T>> RingBufferSPtrType;

  RingBuffer() = delete;
  explicit RingBuffer(uint32_t size) : _maxSize(size), _pData(nullptr), _front(-1), _rear(-1) { _pData = std::unique_ptr<T[]>(new T[size]); }
  ~RingBuffer() = default;

  int32_t size() { return _maxSize; }

  void write(T data) {
    std::unique_lock<std::mutex> lock(mutexLock);
    if (!isFull()) {
      if (empty()) {
        _front = _rear = 0;
        _pData[_rear] = data;
      } else {
        circInc(_rear);
        _pData[_rear] = data;
      }
    }
  }

  bool read(T& value) {
    std::unique_lock<std::mutex> lock(mutexLock);
    dataCondition.wait(lock, [this] { return (!empty()); });
    if (!empty()) {
      value = _pData[_front];
      if (_front == _rear) {
        _front = _rear = -1;
      } else {
        circInc(_front);
      }

      return true;
    } else {
      return false;
    }
  }

  bool isFull() {
    if ((_front == 0 && _rear == _maxSize - 1) || (_rear == (_front - 1))) {
      cout << "Queue is full" << endl;
      return true;
    } else {
      return false;
    }
  }

  bool empty() {
    if (_front == -1) {
      cout << "Queue is empty" << endl;
      return true;
    } else {
      return false;
    }
  }

  void circInc(int32_t& idx) { idx = (++idx == _maxSize) ? 0 : idx; }
};

#endif