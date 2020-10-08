#include <iostream>

#include "SparseMatrix.h"

using namespace std;
int main() {
  int row = 7;
  int column = 8;
  int nonZeroElement = 5;
  SparseMatrix compM(row, column, nonZeroElement);
  SparseMatrix compM2(row, column, nonZeroElement);

  int r, c, data;
  cout << "Enter elemenet (row, coulumn, data)\n";

  /* Input sample compM
    1 8 9
    2 1 5
    3 3 4
    5 6 3
    7 1 6
  */

  for (int i = 0; i < nonZeroElement; i++) {
    cin >> r >> c >> data;
    compM.fillElement(r, c, data);
  }

  cout << "\nEnter elemenet (row, coulumn, data)\n";
  for (int i = 0; i < nonZeroElement; i++) {
    cin >> r >> c >> data;
    compM2.fillElement(r, c, data);
  }

  /* Defined << operator so direct cout would work */
  cout << compM;
  cout << compM2;
  SparseMatrix sum = (compM + compM2);
  cout << sum;

  return 0;
}