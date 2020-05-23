

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <vector>

using namespace std;

struct ErrorMapping_s {
  std::string mainErrorName;
  bool flag;
  int bits;
  std::vector<uint8_t> subClassValues;
};

class NavErrorMap {
  std::string _fileName;
  int _readFlag;
  bool _mapCreated;

  cv::FileNode _mainErrorNode;
  cv::FileNode _subErrrorNode;
  std::vector<ErrorMapping_s> _errorMap;

 public:
  NavErrorMap() = delete;
  explicit NavErrorMap(std::string file, int flag);
  void mapErrors();
  bool getSubClassErrorValues(std::vector<uint8_t>& values, uint8_t idxMainError);
  bool checkFlagEnable(uint8_t idxMainError);
  void printErrorMap();
};

NavErrorMap::NavErrorMap(std::string file, int flag) : _fileName(file), _readFlag(flag) {
  cv::FileStorage fs(_fileName, _readFlag);
  if (!fs.isOpened()) {
    cout << "Can't Open file ";
    _mapCreated = false;
  } else {
    _mainErrorNode = fs["MainClassError"];
    _subErrrorNode = fs["SubclassErrors"];
    mapErrors();
    _mapCreated = true;
  }
  fs.release();
}

void NavErrorMap::mapErrors() {
  if (_mainErrorNode.type() != cv::FileNode::SEQ) {
    cout << "not a sequence!! ";
    _mapCreated = false;
  } else {
    cv::FileNodeIterator it = _mainErrorNode.begin(), it_end = _mainErrorNode.end();
    for (; it != it_end; ++it) {
      ErrorMapping_s temp;
      temp.mainErrorName = static_cast<string>((*it)["errorFlagName"]);
      temp.flag = static_cast<int>((*it)["status"]);  // Don't support bool casting
      temp.bits = static_cast<int>((*it)["bits"]);

      if (temp.flag) {
        std::stringstream subClassKey;

        subClassKey << temp.mainErrorName << "."
                    << "subClass";
        if (!_subErrrorNode[subClassKey.str()].isNone()) {
          _subErrrorNode[subClassKey.str()] >> temp.subClassValues;
        }
      }
      /* reserved bytes */
      if (temp.bits > 1) {
        for (int i = 0; i < temp.bits; i++) {
          ErrorMapping_s temp2;
          temp2.mainErrorName = temp.mainErrorName;
          temp2.flag = temp.flag;
          temp2.bits = 1;
          _errorMap.push_back(temp2);
        }
      } else {
        _errorMap.push_back(temp);
      }
    } /* for Node itr */
  }
}

bool NavErrorMap::getSubClassErrorValues(std::vector<uint8_t>& values, uint8_t idxMainError) {
  if (_errorMap[idxMainError].flag && _errorMap[idxMainError].subClassValues.size() > 0) {
    values = _errorMap[idxMainError].subClassValues;
    return true;
  }
  return false;
}

bool NavErrorMap::checkFlagEnable(uint8_t idxMainError) {
  cout << _errorMap[idxMainError].mainErrorName << " , " << _errorMap[idxMainError].flag << " , " << _errorMap[idxMainError].bits << endl;

  return _errorMap[idxMainError].flag;
}

void NavErrorMap::printErrorMap() {
  if (_mapCreated && _errorMap.size() > 0) {
    cout << "Total Mapped Errors : " << _errorMap.size() << endl;
    for (auto x : _errorMap) {
      cout << "Main error : " << x.mainErrorName << " status : " << x.flag << " bits : " << x.bits;
      if (x.subClassValues.size() > 0) {
        cout << " Sub Class : ";
        for (auto y : x.subClassValues) {
          cout << (int)y << " ";
        }
      } else
        cout << " Sub Class : None";
      cout << endl;
    }
  }
}

int main() {
  NavErrorMap mapObj("ImagesPollSaveError.yaml", cv::FileStorage::READ);
  std::vector<uint8_t> subclass;
  // mapObj.getSubClassErrorValues(subclass, 0);
  mapObj.printErrorMap();
  return 0;
}