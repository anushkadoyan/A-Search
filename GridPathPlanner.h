#ifndef GRID_PATH_PLANNER_H
#define GRID_PATH_PLANNER_H

#include "PartiallyKnownGrid.h"
using namespace std;

class GridPathPlanner{
public:
    struct PathNode {
        xyLoc position;
        vector<PathNode> adjacent;
        float f = 0.0f;
        float g = 0.0f;
        float h = 0.0f;
    };
	GridPathPlanner(PartiallyKnownGrid* grid, bool use_adaptive_a_star = false);
	~GridPathPlanner();

	xyLoc GetNextMove(PartiallyKnownGrid* grid);
    bool contains(string vect, PathNode node);

	int GetNumExpansions();

private:

};

#endif
