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

/* Overload + operator to add two class object values */
Complex operator+(const Complex& other1, const Complex& other2) { return Complex(other1.getReal() + other2.getReal(), other1.getImg() + other2.getImg()); }
/* Overloaded + operator to able to allow adding normal double value to real part of the object with sequence as obj + double value */
Complex operator+(const Complex& other1, double d) { return Complex(other1.getReal() + d, other1.getImg()); }
/* Overloaded + operator to able to allow adding normal double value to real part of the object with sequence as double value + obj */
Complex operator+(double d, const Complex& other1) { return Complex(other1.getReal() + d, other1.getImg()); }

int main() {
  Complex c1(2, 3);
  c1.print();
  Complex c2(5, 6);
  cout << c2 << endl;
  cout << c1 + c2 << endl;

  /* copy constructor will not be running here instead the overloaded method is running */
  Complex c3 = c1 + c2;

  cout << c3 << endl;

  cout << endl;

  Complex c4(5, 10);
  Complex c5 = c4 + 2.1;

  cout << c4 << endl << c5 << endl;
  cout << 2.5 + c4 << endl;
  cout << (3 + c4 + c5 + 2.1) << endl;

  return 0;
}
