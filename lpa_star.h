#ifndef LPASTAR_H
#define LPASTAR_H

#include <vector>
#include <list>
#include <string>
#include <sparsehash/dense_hash_map>
#include <boost/heap/fibonacci_heap.hpp>
#include "dynamic_constraints_manager.h"
#include "map_loader.h"
#include "lpa_node.h"
#include "XytHolder.h"
#include "conflict_avoidance_table.h"

using google::dense_hash_map;
using std::hash;
using std::cout;
using std::vector;
using std::list;
using std::pair;
using std::make_pair;
using std::string;

class LPAStar {
 public:

  // heap<Data, Comparator>
  typedef boost::heap::fibonacci_heap< LPANode* , boost::heap::compare<LPANode::compare_node> > heap_open_t;

// Data Members ---------------------------------------------------------------------------------------------
  int search_iterations;
  vector<int> path;
  //vector< vector<int> > paths;  // for each search iteration there's a path (all kept for statistics)
  float path_cost;
  //vector<float> path_costs;  // for each search iteration path there's a cost (all kept for statistics)
  int start_location;
  int goal_location;
  const float* my_heuristic;  // this is the precomputed heuristic for this agent
  const bool* my_map;  // (not all saved for efficiency)
  int map_rows;
  int map_cols;
  const int* actions_offset;
  uint64_t num_expanded;
  //vector<uint64_t> num_expandeds;  // each search iteration has num_expanded nodes (all kept for statistics)
  //vector< vector<int> > expandedHeatMap;  // (all kept for statistics)
  LPANode* goal_n;
  list<LPANode*> possible_goals;
  int min_goal_timestep;  // Used in identifying nodes with goal locations that can serve as goal nodes because there are no later constraints on WAITing at the goal
  LPANode* start_n;

  DynamicConstraintsManager dcm;

  heap_open_t open_list;
  XytHolder<LPANode*> allNodes_table;
//  vector<set<LPANode*>> v_buckets;
//  vector<vector<LPANode*>*> mddLevels;
    vector<int> mddLevelSizes;

//  void update_v_bucket(LPANode* node, float old_v);

  // nodes_comparator(a,b) returns false if 'a' has (strictly) lower priority than 'b'.
  LPANode::compare_node nodes_comparator;
// ----------------------------------------------------------------------------------------------------------

  int agent_id;  // For debugging

/* ctor
   Note -- ctor also pushes the start node into OPEN (as findPath is incremental).
*/
  LPAStar(int start_location, int goal_location,
          const float* my_heuristic,
          const MapLoader* ml, int agent_id = -1);


/* Returns a pointer to the path found.
*/
  const vector<int>* getPath(/*int i*/) {
      return &path;
      //return &paths[i];
  }


/* Releases all memory used by nodes stored in the hash table.
*/
  inline void releaseNodesMemory();


  inline void printAllNodesTable();


/* Updates the path datamember (vector<int>).
   After update it will contain the sequence of locations found from the goal to the start.
*/
  bool updatePath(LPANode* goal);  // $$$ make inline?


/* LPA* helper methods
*/
  inline std::pair<bool, LPANode*> retrieveNode(int loc_id, int t, bool create_missing = true);
  inline void openlistAdd(LPANode* n);
  inline void openlistUpdate(LPANode* n);
  inline void openlistRemove(LPANode* n);
  inline LPANode* openlistPopHead();
  inline LPANode* retrieveMinPred(LPANode* n);
  inline void updateState(LPANode* n, const ConflictAvoidanceTable& cat, bool bp_already_set=false);

  // Vertex constraint semantics: being at loc_id at time ts is disallowed (hence, a move from it to any neighbor at ts is disallowed).
  void addVertexConstraint(int loc_id, int ts, const ConflictAvoidanceTable& cat);  // Also calls updateState.
  void popVertexConstraint(int loc_id, int ts, const ConflictAvoidanceTable& cat);  // Also calls updateState.
  // Edge constraint semantics: moving from from_id to to_id and arriving there at ts is disallowed.
  void addEdgeConstraint(int from_id, int to_id, int ts, const ConflictAvoidanceTable& cat);  // Also calls updateState.
  void popEdgeConstraint(int from_id, int to_id, int ts, const ConflictAvoidanceTable& cat);  // Also calls updateState.

  // Finds a new path, returns whether a solution was found
  bool findPath(const ConflictAvoidanceTable& cat, int fLowerBound, int minTimestep, clock_t end_by, bool only_improve_current_path = false);
  bool findBetterPath(const ConflictAvoidanceTable& cat, clock_t end_by);
  bool buildMdd(const ConflictAvoidanceTable* cat, clock_t end_by);

  string openToString(bool print_priorities) const;

    LPAStar(const LPAStar& other);  // Copy ctor (deep copy).  When splitting this is needed
    ~LPAStar();  // Dtor.

private:
    void updateGoal();
    int findLeastConflictingPath(const ConflictAvoidanceTable& cat, LPANode *node, int so_far, int upper_bound, map<LPANode*,int>& suffix_lowest_counts);
};


#endif
