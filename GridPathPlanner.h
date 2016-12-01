#ifndef GRID_PATH_PLANNER_H
#define GRID_PATH_PLANNER_H

#include "PartiallyKnownGrid.h"
using namespace std;

class GridPathPlanner{
public:
    struct PathNode {
        xyLoc position;
        xyLoc parent;

        vector<PathNode> adjacent;
        float f = 0.0f;
        float g = 0.0f;
        float h = 0.0f;
    };
	GridPathPlanner(PartiallyKnownGrid* grid, bool use_adaptive_a_star = false);
	~GridPathPlanner();

	xyLoc GetNextMove(PartiallyKnownGrid* grid);
    bool contains(vector<PathNode>  vect, PathNode node);
    float heuristic(xyLoc loc1,xyLoc loc2);
    int GetNumExpansions();
    PathNode squareWithLowestFScore(vector<PathNode> open);
    void removeFromOpen(vector<PathNode>  vect, PathNode node);
private:

};

#endif
