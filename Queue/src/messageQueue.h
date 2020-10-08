#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <queue>

template <typename T>
class MessageQueue {
 private:
  std::queue<T> queue;
  std::mutex mutexLock;

 public:
  /*!
   * \brief empty
   * Check if queue is empty
   * \return
   * True if queue is empty else false
   */
  std::condition_variable dataCondition;
  typedef std::shared_ptr<MessageQueue<T>> MessageQueueSPtrType;
  typedef std::shared_ptr<MessageQueue<std::string>> MessageQueueStdStringSPtrType;

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool empty() { return queue.empty(); }

  /*!
   * \brief push
   * Pushes the value in the queue
   * \param value
   * value to be pushed in the queue with type T
   */
  void push(T value) {
    queue.push(value);
    dataCondition.notify_one();
  }

  /*!
   * \brief pop
   * Do not use this function. Will take lot of cpu
   * cycles when called in while 1
   * \return
   */
  T pop() {
    T value = queue.front();
    queue.pop();
    return value;
  }

  /*!
   * \brief waitAndPop
   * \param value
   */
  void waitAndPop(T& value) {
    std::unique_lock<std::mutex> lock(mutexLock);
    dataCondition.wait(lock, [this] { return (!queue.empty()); });
    if (!queue.empty()) value = pop();
  }

  /**
   * @brief
   *
   * @param value
   * @param timeout_ms
   * @return true
   * @return false
   */
  bool waitAndPop(T& value, uint32_t timeout_ms) {
    std::unique_lock<std::mutex> lock(mutexLock);
    using namespace std;
    using namespace std::chrono;

    if (timeout_ms) {
      auto wait_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);
      if (true == dataCondition.wait_until(lock, wait_time, [this] { return (!queue.empty()); })) {
        if (!queue.empty()) {
          value = pop();
          return true;
        }
      }
    } else {
      dataCondition.wait(lock);
      if (!queue.empty()) {
        value = pop();
        return true;
      }
    }
    return false;
  }

  /**
   * @brief
   *
   */
  void emptyQueue() {
    while (!queue.empty()) {
      break;
    }
  }

  /**
   * \brief breaks the wait of condition variable
   *
   */
  void breakWait() { dataCondition.notify_one(); }
};

#endif  // MESSAGE_QUEUE
