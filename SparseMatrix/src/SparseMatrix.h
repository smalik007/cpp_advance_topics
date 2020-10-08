#pragma once
#include <iostream>
using namespace std;

/* Sparse Matrix : Large 2-D data set can be stored in compressed form where most elements are zeros to reduce the space and computation time
   M = | 0 0 0 0 0 0 0 9 |
       | 5 0 0 0 0 0 0 0 |
       | 0 0 4 0 0 0 0 0 |
       | 0 0 0 0 0 0 0 0 |
       | 0 0 0 0 0 3 0 0 |
       | 0 0 0 0 0 0 0 0 |
       | 6 0 0 0 0 0 0 0 | (7x8)

    Above large matrix can be re-written in the sparse matrix form as below

    row    | i    | m    |  1 | 2 | 3 | 5 | 7 |
    coulum | j    | n    | 8 | 1 | 3 | 6 |  1 |
    data  | data | num  |  9 | 5 | 4 | 3 |  6 |
*/

class Elements {
 public:
  int i;    /* row */
  int j;    /* column */
  int data; /* element */
};

class SparseMatrix {
 private:
  int m_;   /* original matrix rows */
  int n_;   /* original matrix columns */
  int num_; /* num of non-zero elements */
  Elements* sp;
  int idx;

 public:
  SparseMatrix() = delete;
  explicit SparseMatrix(int m, int n, int num) : m_(m), n_(n), num_(num) {
    sp = new Elements[num]; /* Array of num of non-zero element created in heap */
    idx = 0;
  }
  ~SparseMatrix() { delete[] sp; }
  void fillElement(int r, int c, int x);

  friend ostream& operator<<(ostream& os, SparseMatrix& s);
  SparseMatrix operator+(SparseMatrix& s);
};

void SparseMatrix::fillElement(int r, int c, int x) {
  if (idx == num_) {
    std::cout << "array full\n";
    return;
  }

  sp[idx].i = r;
  sp[idx].j = c;
  sp[idx].data = x;
  idx++;
}

ostream& operator<<(ostream& os, SparseMatrix& s) {
  int idx_l = 0;
  cout << std::endl;
  for (int a = 1; a <= s.m_; a++) {
    for (int b = 1; b <= s.n_; b++) {
      if (a == s.sp[idx_l].i && b == s.sp[idx_l].j) {
        cout << s.sp[idx_l++].data << " ";
      } else {
        cout << "0 ";
      }
    }
    cout << endl;
  }
  cout << endl;
  return os;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix& s) {
  int i = 0, j = 0, k = 0;
  if (this->m_ != s.m_ || this->n_ != s.n_) {
    return SparseMatrix(0, 0, 0);
  }

  SparseMatrix* sum = new SparseMatrix(this->m_, this->n_, (this->num_ + s.num_));
  while (i < this->num_ && j < s.num_) {
    if (this->sp[i].i < s.sp[j].i) {
      sum->sp[k++] = this->sp[i++];
    } else if (this->sp[i].i > s.sp[j].i) {
      sum->sp[k++] = s.sp[j++];
    } else {
      if (this->sp[i].j < s.sp[j].j) {
        sum->sp[k++] = this->sp[i++];
      } else if (this->sp[i].j > s.sp[j].j) {
        sum->sp[k++] = s.sp[j++];
      } else {
        sum->sp[k] = this->sp[i];
        sum->sp[k++].data = this->sp[i++].data + s.sp[j++].data;
      }
    }
  } /* while */

  /* copy remaining elements */
  for (; i < this->num_; i++) {
    sum->sp[k++] = this->sp[i];
  }

  for (; j < s.num_; j++) {
    sum->sp[k++] = s.sp[j];
  }
  return *sum;
}