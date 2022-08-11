#include <boost/core/demangle.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

#define TypeName(i) boost::core::demangle(typeid(i).name())
#define TypeNameS(i) typeid(i).name()
#define LOGLOC cout << __LINE__ << endl;
#define LOGLOCF cout << __FUNCTION__ << "-" << __LINE__ << endl;
//#define LOGLOC 
//#define LOGLOCF

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

//using namespace std;
//#include <bits/stdc++.h>
#define NOT_HR

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

string GridToString(const vector<int8_t> &int_grid);
enum class PlacementType {DDR, RUU, UUR, RDD, RRU, DRR, URR, RRD};

bool IsDone(vector<int8_t> int_grid){
  for (auto &i : int_grid){
    if (i != -1)
      return false;
  }

  return true;
}

unordered_map<string, pair<int, int>> FindFirstAvailableLocation_results;
pair<int, int> FindFirstAvailableLocation(const vector<int8_t> &int_grid){
  string temp_str = GridToString(int_grid);
  if (FindFirstAvailableLocation_results.find(temp_str) != FindFirstAvailableLocation_results.end())
    return FindFirstAvailableLocation_results[temp_str];

  for (size_t i = 0; i < int_grid.size(); ++i){
    if (int_grid[i] == -1) continue;
    for (size_t j = 0; j < 8; ++j) {
      if (!(int_grid[i] & (1 << (7 - j)))){
        FindFirstAvailableLocation_results[temp_str] = make_pair(i, j);
        return make_pair(i, j);
      }
    }
  }
  
  return make_pair(-1, -1);
}

vector<pair<int, int>> GetGridIndexes(const vector<int8_t> &int_grid, int i, int j, PlacementType pt, int location){
  vector<pair<int, int>> result;

  int height = int_grid.size(), width = 8;

  switch (pt)
  {
    case PlacementType::DDR:
      switch (location) {
        case 1: result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i + 1, j + 0)); result.push_back(make_pair(i + 2, j + 0)); result.push_back(make_pair(i + 2, j + 1)); break;
        case 2: result.push_back(make_pair(i - 1, j + 0)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i + 1, j + 0)); result.push_back(make_pair(i + 1, j + 1)); break;
        case 3: result.push_back(make_pair(i - 2, j + 0)); result.push_back(make_pair(i - 1, j + 0)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i + 0, j + 1)); break;
        case 4: result.push_back(make_pair(i - 2, j - 1)); result.push_back(make_pair(i - 1, j - 1)); result.push_back(make_pair(i + 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
    case PlacementType::RUU:
      switch (location) {
        case 1: result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 0, j + 1)); result.push_back(make_pair(i - 1, j + 1)); result.push_back(make_pair(i - 2, j + 1)); break;
        case 2: result.push_back(make_pair(i - 0, j - 1)); result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 1, j + 0)); result.push_back(make_pair(i - 2, j + 0)); break;
        case 3: result.push_back(make_pair(i + 1, j - 1)); result.push_back(make_pair(i + 1, j + 0)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i - 1, j + 0)); break;
        case 4: result.push_back(make_pair(i + 2, j - 1)); result.push_back(make_pair(i + 2, j - 0)); result.push_back(make_pair(i + 1, j - 0)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
    case PlacementType::UUR:
      switch (location) {
        case 1: result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 1, j + 0)); result.push_back(make_pair(i - 2, j + 0)); result.push_back(make_pair(i - 2, j + 1)); break;
        case 2: result.push_back(make_pair(i + 1, j - 0)); result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 1, j + 0)); result.push_back(make_pair(i - 1, j + 1)); break;
        case 3: result.push_back(make_pair(i + 2, j - 0)); result.push_back(make_pair(i + 1, j + 0)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i - 0, j + 1)); break;
        case 4: result.push_back(make_pair(i + 2, j - 1)); result.push_back(make_pair(i + 1, j - 1)); result.push_back(make_pair(i + 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
    case PlacementType::RDD:
      switch (location) {
        case 1: result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 0, j + 1)); result.push_back(make_pair(i + 1, j + 1)); result.push_back(make_pair(i + 2, j + 1)); break;
        case 2: result.push_back(make_pair(i + 0, j - 1)); result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i + 1, j + 0)); result.push_back(make_pair(i + 2, j + 0)); break;
        case 3: result.push_back(make_pair(i - 1, j - 1)); result.push_back(make_pair(i - 1, j + 0)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i + 1, j + 0)); break;
        case 4: result.push_back(make_pair(i - 2, j - 1)); result.push_back(make_pair(i - 2, j - 0)); result.push_back(make_pair(i - 1, j - 0)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
    case PlacementType::RRU:
      switch (location) {
        case 1: result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 0, j + 1)); result.push_back(make_pair(i + 0, j + 2)); result.push_back(make_pair(i - 1, j + 2)); break;
        case 2: result.push_back(make_pair(i + 0, j - 1)); result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i + 0, j + 1)); result.push_back(make_pair(i - 1, j + 1)); break;
        case 3: result.push_back(make_pair(i - 0, j - 2)); result.push_back(make_pair(i - 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i - 1, j + 0)); break;
        case 4: result.push_back(make_pair(i + 1, j - 2)); result.push_back(make_pair(i + 1, j - 1)); result.push_back(make_pair(i + 1, j - 0)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
    case PlacementType::DRR:
      switch (location) {
        case 1: result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i + 1, j + 0)); result.push_back(make_pair(i + 1, j + 1)); result.push_back(make_pair(i + 1, j + 2)); break;
        case 2: result.push_back(make_pair(i - 1, j - 0)); result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i + 0, j + 1)); result.push_back(make_pair(i - 0, j + 2)); break;
        case 3: result.push_back(make_pair(i - 1, j - 1)); result.push_back(make_pair(i - 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i - 0, j + 1)); break;
        case 4: result.push_back(make_pair(i - 1, j - 2)); result.push_back(make_pair(i + 0, j - 2)); result.push_back(make_pair(i + 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
    case PlacementType::URR:
      switch (location) {
        case 1: result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 1, j + 0)); result.push_back(make_pair(i - 1, j + 1)); result.push_back(make_pair(i - 1, j + 2)); break;
        case 2: result.push_back(make_pair(i + 1, j - 0)); result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i + 0, j + 1)); result.push_back(make_pair(i - 0, j + 2)); break;
        case 3: result.push_back(make_pair(i + 1, j - 1)); result.push_back(make_pair(i - 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i - 0, j + 1)); break;
        case 4: result.push_back(make_pair(i + 1, j - 2)); result.push_back(make_pair(i + 0, j - 2)); result.push_back(make_pair(i + 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
    case PlacementType::RRD:
      switch (location) {
        case 1: result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i - 0, j + 1)); result.push_back(make_pair(i + 0, j + 2)); result.push_back(make_pair(i + 1, j + 2)); break;
        case 2: result.push_back(make_pair(i + 0, j - 1)); result.push_back(make_pair(i - 0, j + 0)); result.push_back(make_pair(i + 0, j + 1)); result.push_back(make_pair(i + 1, j + 1)); break;
        case 3: result.push_back(make_pair(i - 0, j - 2)); result.push_back(make_pair(i - 0, j - 1)); result.push_back(make_pair(i + 0, j + 0)); result.push_back(make_pair(i + 1, j + 0)); break;
        case 4: result.push_back(make_pair(i - 1, j - 2)); result.push_back(make_pair(i - 1, j - 1)); result.push_back(make_pair(i - 1, j - 0)); result.push_back(make_pair(i + 0, j + 0)); break;
      }
      break;
  } 

  for (auto &i : result) {
    if (i.first < 0 || i.first >= height || i.second < 0 || i.second >= width){
      result.clear();
      break;
    }
  }

  return result;
}


pair<bool, vector<pair<int, int>>> PlacementPossible(const vector<int8_t> &int_grid, PlacementType placement, int loc){
  auto temp_pair = FindFirstAvailableLocation(int_grid);
  int i = temp_pair.first, j = temp_pair.second;

  vector<pair<int, int>> points;

  if (placement == PlacementType::DDR && loc != 1) return make_pair(false, points);
  if (placement == PlacementType::RUU && loc != 4) return make_pair(false, points);
  if (placement == PlacementType::UUR && loc != 3) return make_pair(false, points);
  if (placement == PlacementType::RDD && loc != 1) return make_pair(false, points);
  if (placement == PlacementType::RRU && loc != 4) return make_pair(false, points);
  if (placement == PlacementType::DRR && loc != 1) return make_pair(false, points);
  if (placement == PlacementType::URR && loc != 2) return make_pair(false, points);
  if (placement == PlacementType::RRD && loc != 1) return make_pair(false, points);

  points = GetGridIndexes(int_grid, i, j, placement, loc);

  if (points.size() == 0) return make_pair(false, points);

  for (auto &i : points) {
    if (int_grid[i.first] & (1 << (7 - i.second))) 
      return make_pair(false, points);
  }

  return make_pair(true, points);
}

void Place(vector<int8_t> &int_grid, const vector<pair<int, int>> &points){
  for (auto &i : points) 
    int_grid[i.first] |= (1 << (7 - i.second));
}
void UnPlace(vector<int8_t> &int_grid, const vector<pair<int, int>> &points){
  for (auto &i : points) 
    int_grid[i.first] &= ~(1 << (7 - i.second));
}

string GridToString(const vector<int8_t> &int_grid){
  string result;
  for (auto &i : int_grid) result += to_string(i + 256);
  return result;

}

unordered_map<string, long int> saved_results;
long int brickTilingUtil(vector<int8_t> &int_grid) {
  string temp = GridToString(int_grid);
  if (saved_results.find(temp) != saved_results.end()) 
    return saved_results[temp];

  if (IsDone(int_grid))
    return 1;

  PlacementType placements[] = {PlacementType::DDR, PlacementType::RUU, PlacementType::UUR, PlacementType::RDD, 
                                PlacementType::RRU, PlacementType::DRR, PlacementType::URR, PlacementType::RRD};

  long int result = 0;
  for (auto &placement : placements) {
    for (int loc = 1; loc <= 4; ++loc) {
      auto temp = PlacementPossible(int_grid, placement, loc);
      if (temp.first){
        Place(int_grid, temp.second);
        result += brickTilingUtil(int_grid);
        UnPlace(int_grid, temp.second);
      }
    }
  }

  saved_results[temp] = result;
  return result;
}

int8_t SetBit(int8_t i, int8_t bit){
  return i | (1 << (7 - bit));
}

long int brickTiling(vector<string> grid) {
  for (auto &i : grid) {
    i = ltrim(rtrim(i));
  }

  int height = grid.size();
  int width = grid[0].size();

  if (height == 19 && width == 3)
    height = 19;

  vector<int8_t> int_grid;
  for (int i = 0; i < 20; ++i) {
    int8_t temp = 0;
    if (i >= height){
      temp = -1;
      continue;
    }

    for (int j = 0; j < 8; ++j) {
      if (grid[i][j] == '#' || j >= width) 
        temp = SetBit(temp, j);
    }
    int_grid.push_back(temp);
  }
  return brickTilingUtil(int_grid) % 1000000007;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    ostream & fout = cout;

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<string> grid(n);

        for (int i = 0; i < n; i++) {
            string grid_item;
            getline(cin, grid_item);

            grid[i] = grid_item;
        }

        int result = brickTiling(grid);

        fout << result << "\n";
    }

    //fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
