/*
 * Description - Basic Exception.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
  // Two dimensional vector with presize of 3 rows and 4 columns(you don't have to necessarrily give this), you can also initialize all the values to 7 like in below example.
  // impt thing here in the sintax is spaces in vector<vector<int> > , without the space it will give compile error.
  vector<vector<int> > grid(3, vector<int>(4, 7));

  // One important concept here is that you don't have to have a fix size of rows and cols, it can be any cols in a row and vice versa.
  grid[1].push_back(8);  // this will add one more column to second row

  for (uint rows = 0; rows < grid.size(); rows++) {
    for (uint cols = 0; cols < grid[rows].size(); cols++) {
      cout << grid[rows][cols];
    }
    cout << endl;
  }

  return 0;
}
