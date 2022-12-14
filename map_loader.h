#pragma once
#include "common.h"

class MapLoader {
 public:
  bool* my_map;  // true means a cell is blocked
  int rows;
  int cols;
  int start_loc;
  int goal_loc;
  std::string name;

  enum valid_moves_t { NORTH, EAST, SOUTH, WEST, WAIT_MOVE, MOVE_COUNT };  // MOVE_COUNT is the enum's size
  int* moves_offset;

  MapLoader(){}
  MapLoader(std::string fname); // load map from file
  MapLoader(int rows, int cols); // initialize new [rows x cols] empty map
  MapLoader(int rows, int cols, std::vector<std::pair<int, int>> obstacles); // mapf-adapter: initialize new [rows x cols] with obstacles
  inline bool is_blocked (int row, int col) const { return my_map[row * this->cols + col]; }
  inline bool is_blocked (int loc) const { return my_map[loc]; }
  inline size_t map_size() const { return rows * cols; }
  void printMap ();
  void printMap (char* mapChar);
  void printHeuristic (const double* mapH, const int agent_id);
  char* mapToChar();
  bool* copy_map () const; // return a deep-copy of my_map
  inline int linearize_coordinate(int row, int col) const { return ( this->cols * row + col); }
  inline int row_coordinate(int id) const { return id / this->cols; }
  inline int col_coordinate(int id) const { return id % this->cols; }
  void printPath (std::vector<int> path);
  void saveToFile(std::string fname);

  ~MapLoader();
};
