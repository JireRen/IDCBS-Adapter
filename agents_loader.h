// Load's agents' init and goal states.
// First line: number of agents
// Second line and onward, (x_init,y_init),(x_goal,y_goal) of each agent (one per line)
#pragma once

#include "map_loader.h"

using namespace std;

class AgentsLoader 
{
public:
	int num_of_agents = 0;
	vector< pair<int, int> > initial_locations;
	vector< pair<int, int> > goal_locations;

	AgentsLoader(const std::string fname, const MapLoader &ml, int agentsNum, int width);
    AgentsLoader(std::vector<std::pair<int, int> > starts, std::vector<std::pair<int, int> > goals); // mapf-adapter: load agents
	AgentsLoader(){}
	void printAgentsInitGoal ();
	void saveToFile(const std::string fname);
};
