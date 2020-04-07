/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <map>
#include <vector>
using namespace std;

class ScoresData {
 private:
  string _name;
  vector<int> _scores;

 public:
  ScoresData() : _name(""), _scores(0) {}
  ScoresData(string name, vector<int> scores) : _name(name), _scores(scores) {}
  void print() {
    cout << _name << "-" << flush;
    for (uint i = 0; i < _scores.size(); i++) {
      cout << _scores[i] << "," << flush;
    }
    cout << endl;
  }
  ~ScoresData() {}
};

int main() {
  /* You can create a nested data structre like map of vectors, but it is higly recommended to create your own class and use that instead of nested structures, coz the nested structure could be quite
   * messy, we will see the example of both in this program */
  map<string, vector<int> > scores;

  /* Here we are trying to store multiple scores under same map key */
  scores["Mike"].push_back(10);
  scores["Mike"].push_back(20);
  scores["Raj"].push_back(50);

  map<string, vector<int> >::iterator it = scores.begin();

  for (; it != scores.end(); it++) {
    string name = it->first;             // get the key
    vector<int> scoreList = it->second;  // get vector storing all the scores
    cout << name << "-" << flush;
    for (uint i = 0; i < scoreList.size(); i++) {
      cout << scoreList[i] << "," << flush;
    }
    cout << endl;
  }

  /* Now lets do the same with a custom class */
  vector<ScoresData> scoreData;
  vector<int> mikeScore, rajScore;
  mikeScore.push_back(10);
  mikeScore.push_back(20);
  rajScore.push_back(50);

  scoreData.push_back(ScoresData("Mike", mikeScore));
  scoreData.push_back(ScoresData("Raj", rajScore));
  cout << endl;
  vector<ScoresData>::iterator scoreIt = scoreData.begin();
  for (; scoreIt != scoreData.end(); scoreIt++) {
    scoreIt->print();
  }

  return 0;
}
