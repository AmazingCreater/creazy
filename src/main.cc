#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

inline bool is_int(float n) {
  int t = n;
  return t == n;
}

class Line {
 public:
  Line(int k, int b) : k_(k), b_(b) {}
  Line(int k, int x, int y) : k_(k) {
    b_ = y - k_ * x;
  }  
  inline int y(int x) const {
    return k_ * x + b_;
  }
  inline int k() const {
    return k_;
  }
  inline int b() const {
    return b_;
  }
  inline bool on(int x, int y) const {
    return this->y(x) == y;
  }
 private:
  int k_;
  int b_;
}; // class Line

inline float cal_ins_x(const Line& l1, const Line& l2) {
  return 1.0f * (l2.b() - l1.b()) / (l1.k() - l2.k());
}

class Matrix {
 public:
  friend istream& operator>>(istream& os, Matrix& mat);
  friend ostream& operator<<(ostream& os, const Matrix& mat);
  Matrix() {
    data_.clear();
  }
  void zero() {
    const int m = data_.size();
    vector<Line> lines = {{1, 0}, {1, -1}, {-1, m - 1}, {-1, m}};
    vector<bool> zero_for_lines(4, false);
    // make sure zero for lines
    for (int i = 0; i < 4; ++i) {
      for (int x = 0; x < m; ++x) {
        if (0 == data_[x][lines[i].y(x)]) {
          zero_for_lines[i] = true;
          break;
        }
      }
    }
    
    // setting zero on lines
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < m; ++y) {
        if (1 == data_[x][y]) continue;
        if (lines[0].on(x, y) || lines[1].on(x, y) || lines[2].on(x, y) || lines[3].on(x, y)) continue;
        Line l0(1, x, y), l1(-1, x, y);
        float ins_x = cal_ins_x(l1, lines[0]);
        if (is_int(ins_x)) {
          data_[ins_x][lines[0].y(ins_x)] = 0;
        } else {
          ins_x = cal_ins_x(l1, lines[1]);
          assert(is_int(ins_x));
          data_[ins_x][lines[1].y(ins_x)] = 0;
        }
        ins_x = cal_ins_x(l0, lines[2]);
        if (is_int(ins_x)) {
          data_[ins_x][lines[2].y(ins_x)] = 0;
        } else {
          ins_x = cal_ins_x(l0, lines[3]);
          assert(is_int(ins_x));
          data_[ins_x][lines[3].y(ins_x)] = 0;
        }
      }
    }
cout << *this << endl;
    // check zero for point not on lines
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < m; ++y) {
        Line l0(1, x, y), l1(-1, x, y);
        float ins_x = cal_ins_x(l1, lines[0]);
        if (is_int(ins_x)) {
          if (0 == data_[ins_x][lines[0].y(ins_x)]) {
            data_[x][y] = 0;
          }
        } else {
          ins_x = cal_ins_x(l1, lines[1]);
          assert(is_int(ins_x));
          if (0 == data_[ins_x][lines[1].y(ins_x)]) {
            data_[x][y] = 0;
          }
        }
        ins_x = cal_ins_x(l0, lines[2]);
        if (is_int(ins_x)) {
          if (0 == data_[ins_x][lines[2].y(ins_x)]) {
            data_[x][y] = 0;
          }
        } else {
          ins_x = cal_ins_x(l0, lines[3]);
          assert(is_int(ins_x));
          if (0 == data_[ins_x][lines[3].y(ins_x)]) {
            data_[x][y] = 0;
          }
        }
      }
    }
cout << *this << endl;
    // check zero on lines
    for (int i = 0; i < 4; ++i) {
      if (zero_for_lines[i]) {
        for (auto x = 0; x < m; ++x) {
          auto y = lines[i].y(x);
          if (y >= 0 && y < m) data_[x][y] = 0;
        }
      }
    }
cout << *this << endl;
  }
  void zero_test() {
    auto tmp = data_;
    int m = data_.size();
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < m; ++y) {
        if (0 == tmp[x][y]) {
          Line l1(1, x, y), l2(-1, x, y);
          for (int xt = 0; xt < m; ++xt) {
            int yt = l1.y(xt);
            if (yt >= 0 && yt < m) data_[xt][yt] = 0;
            yt = l2.y(xt);
            if (yt >= 0 && yt < m) data_[xt][yt] = 0;
          }
        }
      }
    }
  }
  bool operator==(const Matrix& other) {
    return data_ == other.data_;
  }
 private:
  vector<vector<int>> data_;
}; // class Matrix

istream& operator>>(istream& is, Matrix& mat) {
  // auto epoch = chrono::high_resolution_clock::now().time_since_epoch();
  // srand(epoch.count());
  // int m = rand() % 10;
  // mat.data_.resize(m);
  // for (auto& row : mat.data_) {
  //   row.reserve(m);
  //   for (int i = 0; i < m; ++i) {
  //     row.push_back(rand() % 2);
  //   }
  // }
  mat.data_ = {
    {1, 1, 1, 0},
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {0, 1, 0, 0}
  };
  return is;
}

ostream& operator<<(ostream& os, const Matrix& mat) {
  // for (auto& row : mat.data_) {
  //   for (auto it : row) {
  //     os << it << " ";
  //   }
  //   os << endl;
  // }
  int m = mat.data_.size();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << mat.data_[j][i] << " ";
    }
    cout << endl;
  }
  return os;
}

int main (int argc, char *argv[]) {
  Matrix mat, tmat;
  cin >> mat;
  tmat = mat;
  //cout << mat << endl;
  mat.zero();
  //tmat.zero_test();
  // cout << mat << endl;
  // cout << tmat << endl;
  // if (mat == tmat) {
  //   cout << "yes" << endl;
  // } else {
  //   cout << "no" << endl;
  // }
  getchar();
  return EXIT_SUCCESS;
}
