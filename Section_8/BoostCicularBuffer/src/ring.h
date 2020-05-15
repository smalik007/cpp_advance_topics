/*
 * Description - ring.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-16 23:39:52
 *
 */
#include <boost/bind/bind.hpp>
#include <boost/call_traits.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/timer/timer.hpp>
#include <mutex>

template <class T>
class RingBuffer {
 public:
  typedef boost::circular_buffer<T> container_type;
  typedef typename container_type::size_type size_type;
  typedef typename container_type::value_type value_type;
  typedef typename boost::call_traits<value_type>::param_type param_type;
  typedef std::shared_ptr<RingBuffer<T>> RingBufferSPtrType;

 public:
  RingBuffer() = delete;
  RingBuffer(const RingBuffer&) = delete;
  RingBuffer& operator=(const RingBuffer&) = delete;
  explicit RingBuffer(size_type capacity) : _container(capacity) {}

  void pushFront(param_type item) {
    std::unique_lock<std::mutex> lock(_mutex);
    _container.push_front(item);
    _mutex.unlock();
    _notEmpty.notify_one();
  }

  bool popBack(value_type& pItem) {
    std::unique_lock<std::mutex> lock(_mutex);
    _notEmpty.wait(lock, [this] { return (isNotEmpty()); });
    pItem = _container.back();
    _container.pop_back();
    return true;
  }

  bool isNotEmpty() const { return (!_container.empty()); }

  void clear() { _container.clear(); }

 private:
  container_type _container;
  std::mutex _mutex;
  boost::condition _notEmpty;
};