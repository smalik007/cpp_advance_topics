

// #include <boost/algorithm/string.hpp>
// #include <boost/filesystem.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <vector>

using namespace std;
#define MASK_SUB_CLASS_ERROR (0x00FFFFFFFFFFFFFF)
#define MASK_MAIN_CLASS_ERROR (0xFF00000000000000)

struct ErrorMapping_s {
  std::string mainErrorName;
  bool flag;
  int bits;
  std::vector<uint8_t> subClassValuesBottom;
  std::vector<uint8_t> subClassValuesTop;
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
  bool getSubClassBottom(std::vector<uint8_t>& values, uint8_t idxMainError);
  bool getSubClassTop(std::vector<uint8_t>& values, uint8_t idxMainError);
  bool checkFlagEnable(uint8_t idxMainError);
  void printErrorMap();
  void printSpecificError(uint8_t indxMainError);
};

NavErrorMap::NavErrorMap(std::string file, int flag) : _fileName(file), _readFlag(flag) {
  try {
    cv::FileStorage fs(_fileName, _readFlag);
    if (!fs.isOpened()) {
      cout << "Can't Open file ";
      _mapCreated = false;
    } else {
      _mainErrorNode = fs["MainClassError"];
      //_subErrrorNode = fs["SubclassErrors"];
      mapErrors();
      _mapCreated = true;
    }
    fs.release();
  } catch (const cv::Exception& err) {
    cout << "Exception :" << err.what() << endl;
  }
}

void NavErrorMap::mapErrors() {
  try {
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
          if (!(((*it)["subClass.bottom"]).isNone())) {
            ((*it)["subClass.bottom"]) >> temp.subClassValuesBottom;
          }
          if (!(((*it)["subClass.top"]).isNone())) {
            ((*it)["subClass.top"]) >> temp.subClassValuesTop;
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
  } catch (const cv::Exception& err) {
    cout << "Exception :" << err.what() << endl;
  }
}

bool NavErrorMap::getSubClassBottom(std::vector<uint8_t>& values, uint8_t idxMainError) {
  if (_mapCreated && _errorMap.size() > 0) {
    if (_errorMap[idxMainError].flag) {  // Check Main Flag is set
      // check subClassBottom size has some error flags stored
      if (_errorMap[idxMainError].subClassValuesBottom.size() > 0) {
        values = _errorMap[idxMainError].subClassValuesBottom;
        return true;
      }
    }
  }
  return false;
}

bool NavErrorMap::getSubClassTop(std::vector<uint8_t>& values, uint8_t idxMainError) {
  if (_mapCreated && _errorMap.size() > 0) {
    if (_errorMap[idxMainError].flag) {  // Check Main Flag is set
      // check subClassTop size has some error flags stored
      if (_errorMap[idxMainError].subClassValuesTop.size() > 0) {
        values = _errorMap[idxMainError].subClassValuesTop;
        return true;
      }
    }
  }
  return false;
}

bool NavErrorMap::checkFlagEnable(uint8_t idxMainError) {
  if (_mapCreated && _errorMap.size() > 0) {
    cout << _errorMap[idxMainError].mainErrorName << " , " << _errorMap[idxMainError].flag << " , " << _errorMap[idxMainError].bits << endl;

    return _errorMap[idxMainError].flag;
  }
  return false;
}

void NavErrorMap::printSpecificError(uint8_t indxMainError) {
  if (_mapCreated && _errorMap.size() > 0) {
    cout << "Main error : " << _errorMap[indxMainError].mainErrorName << " status : " << _errorMap[indxMainError].flag << " bits : " << _errorMap[indxMainError].bits;
    if (_errorMap[indxMainError].subClassValuesBottom.size() > 0) {
      cout << " Sub Class Bottom : ";
      for (auto y : _errorMap[indxMainError].subClassValuesBottom) {
        cout << (int)y << " ";
      }
    } else
      cout << " Sub Class : None";
    cout << endl;

    if (_errorMap[indxMainError].subClassValuesTop.size() > 0) {
      cout << " Sub Class Top : ";
      for (auto y : _errorMap[indxMainError].subClassValuesTop) {
        cout << (int)y << " ";
      }
    } else
      cout << " Sub Class : None";
    cout << endl;
  } else {
    cout << "Map can't be created" << endl;
  }
}

void NavErrorMap::printErrorMap() {
  if (_mapCreated && _errorMap.size() > 0) {
    cout << "Total Mapped Errors : " << _errorMap.size() << endl;
    for (auto x : _errorMap) {
      cout << "Main error : " << x.mainErrorName << " status : " << x.flag << " bits : " << x.bits;
      if (x.subClassValuesBottom.size() > 0) {
        cout << " Sub Class : ";
        for (auto y : x.subClassValuesBottom) {
          cout << (int)y << " ";
        }
      } else
        cout << " Sub Class : None";
      cout << endl;

      if (x.subClassValuesTop.size() > 0) {
        cout << " Sub Class : ";
        for (auto y : x.subClassValuesTop) {
          cout << (int)y << " ";
        }
      } else
        cout << " Sub Class : None";
      cout << endl;
    }
  } else {
    cout << "Map can't be created" << endl;
  }
}

int findIndexPosition(uint64_t error) {
  uint64_t temp = (error & MASK_SUB_CLASS_ERROR);
  if (!(temp && (!(temp & (temp - 1))))) {
    return -1;
  }
  uint64_t i = 1, pos = 1;

  while (!(i & temp)) {
    // Unset current bit and set the next bit in 'i'
    i = i << 1;

    // increment position
    ++pos;
  }
  return pos;
}

static void processErrorFlag(uint64_t errorFlag) {
  uint64_t mainError = (errorFlag & MASK_SUB_CLASS_ERROR);
  uint8_t subClassError = (uint8_t)((uint64_t)((errorFlag & MASK_MAIN_CLASS_ERROR) >> 56));
  printf("0x%016llX\n", errorFlag);
  printf("0x%016llX\n", mainError);
  printf("0x%0x\n", subClassError);
}

int main() {
  NavErrorMap mapObj("ImagesPollSaveError.yaml", cv::FileStorage::READ);
  std::vector<uint8_t> subclass;

  // mapObj.getSubClassErrorValues(subclass, 0);
  // mapObj.printErrorMap();
  uint64_t error_flag = 0x8600000002000000;
  processErrorFlag(error_flag);
  int bitPos = findIndexPosition(error_flag);
  if (bitPos != -1) {
    cout << "Bit pos : " << bitPos << endl;
    mapObj.printSpecificError(bitPos - 1);
  } else
    cout << "Not power of two" << endl;
  return 0;
}
