#include "GridPathPlanner.h"
#include <iostream>
#include <cmath>        // std::abs

using namespace std;


vector<GridPathPlanner::PathNode> closed;
vector<GridPathPlanner::PathNode> open;

GridPathPlanner::GridPathPlanner(PartiallyKnownGrid* grid, bool use_adaptive_a_star) {
	// TODO
}
GridPathPlanner::~GridPathPlanner(){
	// TODO
}
bool GridPathPlanner::contains(string vect, PathNode node)
{
    if(vect == "open") {
        for(int i = 0; i < open.size(); i++){
            if ( open[i].position == node.position ) {
                return true;
            }
        }
        return false;
    }
    else if(vect == "closed") {
        for(int i = 0; i < closed.size(); i++){
            if ( closed[i].position == node.position ) {
                return true;
            }
        }
        return false;
    }
}
float GridPathPlanner::heuristic(xyLoc curr,xyLoc goal) {
    return abs(curr.x - goal.x)+abs(curr.y - goal.y);
}

xyLoc GridPathPlanner::GetNextMove(PartiallyKnownGrid* grid) {
	// TODO
	// This is just a dummy implementation that returns a random neighbor.
    PathNode currentNode;
    closed.push_back(currentNode);
	xyLoc curr = grid->GetCurrentLocation();
	vector<xyLoc> neighbors;
	neighbors.push_back(xyLoc(curr.x+1, curr.y));
	neighbors.push_back(xyLoc(curr.x-1, curr.y));
	neighbors.push_back(xyLoc(curr.x, curr.y+1));
	neighbors.push_back(xyLoc(curr.x, curr.y-1));
    
	for (int i = 0; i < neighbors.size(); i++) {
		xyLoc n = neighbors[i];
		if (!grid->IsValidLocation(n) || grid->IsBlocked(n)) {
			neighbors[i] = neighbors.back();
            PathNode neigh;
            neigh.position = neighbors[i];
            
            //|l1.x − l2.x| + |l1.y − l2.y|
            
            neigh.h = heuristic(neigh.position, grid->GetGoalLocation());
            
            currentNode.adjacent.push_back(neigh);
//            open.push_back(neigh)
			neighbors.pop_back();
			i--;
		}
	}
    for (int i = 0; i < currentNode.adjacent.size(); i++) {
        if (currentNode.adjacent[i].position == grid->GetGoalLocation()) {
            return currentNode.adjacent[i].position;
        }
        if (contains("closed", currentNode.adjacent[i])){
            continue;
        }
        else if(contains("open", currentNode.adjacent[i])) {
               /* v contains x */
        }
        else {
            
        }
        
    }


    cout << grid->GetCurrentLocation();
	if (neighbors.size() == 0)
		return kInvalidXYLoc;
	else
        cout <<neighbors[rand()%neighbors.size()];
		return neighbors[rand()%neighbors.size()];
}

int GetNumExpansions() {
	// TODO
	return 0;
}
