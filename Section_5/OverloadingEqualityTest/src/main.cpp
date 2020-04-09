/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;
class Complex {
 private:
  double _real;
  double _img;

 public:
  Complex() : _real(0), _img(0) {}
  Complex(double real, double img) : _real(real), _img(img) {}
  ~Complex() {}
  /* copy constructor */
  Complex(const Complex& other) {
    cout << "Copy constructor is running" << endl;
    _real = other._real;
    _img = other._img;
  }
  void print() { cout << _real << " + i" << _img << endl; }

  /* Overloading assignment operator */
  const Complex& operator=(const Complex& other) {
    cout << "Assignment operator is running" << endl;
    _real = other._real;
    _img = other._img;

    return *this;
  }

  inline double getReal() const { return _real; }
  inline double getImg() const { return _img; }
};

ostream& operator<<(ostream& c, const Complex& other) {
  c << other.getReal() << " + i" << other.getImg() << flush;
  return c;
}

bool operator==(Complex& other1, Complex& other2) {
  bool return_status = false;

  if (other1.getReal() == other2.getReal()) {
    if (other1.getImg() == other2.getImg()) {
      return_status = true;
    }
  }
  return return_status;
}

bool operator!=(Complex& other1, Complex& other2) {
  bool return_status = true;

  if (other1.getReal() == other2.getReal()) {
    if (other1.getImg() == other2.getImg()) {
      return_status = false;
    }
  }
  return return_status;
}

int main() {
  Complex c1(2, 3);
  Complex c2(2, 3);

  if (c1 == c2) {
    cout << "Two objects are equal" << endl;
  } else {
    cout << "Two objects are not equal" << endl;
  }

  if (c1 != c2) {
    cout << "Not equal" << endl;
  } else {
    cout << "Equal" << endl;
  }

  return 0;
}
