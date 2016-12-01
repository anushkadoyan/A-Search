#include "GridPathPlanner.h"
#include <iostream>
#include <cmath>        // std::abs
#include <algorithm>

using namespace std;


xyLoc start(1,1);
GridPathPlanner::GridPathPlanner(PartiallyKnownGrid* grid, bool use_adaptive_a_star) {
	// TODO
}
GridPathPlanner::~GridPathPlanner(){
	// TODO
}
bool GridPathPlanner::contains(vector<GridPathPlanner::PathNode>  vect, PathNode node)
{
        for(int i = 0; i < vect.size(); i++){
            if ( vect[i].position == node.position ) {
                return true;
            }
        }
        return false;
    
}

void GridPathPlanner::removeFromOpen(vector<GridPathPlanner::PathNode>  vect, PathNode node) {
    for(int i = 0; i < vect.size(); i++){
        if ( vect[i].position == node.position ) {
//            cout <<"swap me!\n";
            swap(node, vect.back());
            vect.pop_back();
            continue;
        }
    }
}


float GridPathPlanner::heuristic(xyLoc loc1, xyLoc loc2) {
    return abs(loc1.x - loc2.x)+abs(loc1.y - loc2.y);
}
GridPathPlanner::PathNode GridPathPlanner::squareWithLowestFScore(vector<GridPathPlanner::PathNode>  open) {
    int min = 0;
    PathNode minNode;
    minNode = open[0];
    int dups = 0;
    for(int i = 0; i < open.size(); i++)
        if(open[i].f < minNode.f) {
            minNode = open[i];
            min = i;
        }
        else if(open[i].f == minNode.f) {
//            cout << "lol\n";
            if(open[i].g>minNode.g) {
                minNode = open[i];
                min = i;

            } else if(open[i].g==minNode.g) {

                minNode = ((open[i].position < minNode.position) ? open[i] : minNode);
                min = i;

            }
        }

    
//    cout << "Min node "<<minNode.f<<"\n";
    return minNode;
}
xyLoc GridPathPlanner::GetNextMove(PartiallyKnownGrid* grid) {
	// TODO
    vector<GridPathPlanner::PathNode> closed;
    vector<GridPathPlanner::PathNode> open;
    
    PathNode currentNode;
    PathNode next;
    next.position = grid->GetCurrentLocation();
    currentNode.position = grid->GetGoalLocation();
//    currentNode.h = heuristic(currentNode.position, grid->GetGoalLocation());
//    currentNode.g = heuristic(start, currentNode.position);
//    currentNode.f = currentNode.h+currentNode.f;
//    cout << "Current node " << currentNode.position << "\n";
//    cout << "Current node f " << currentNode.f << "\n";
    
    closed.push_back(currentNode);
    do {
        xyLoc curr = grid->GetCurrentLocation();
        vector<xyLoc> neighbors;
        neighbors.push_back(xyLoc(currentNode.position.x+1, currentNode.position.y));
        neighbors.push_back(xyLoc(currentNode.position.x-1, currentNode.position.y));
        neighbors.push_back(xyLoc(currentNode.position.x, currentNode.position.y+1));
        neighbors.push_back(xyLoc(currentNode.position.x, currentNode.position.y-1));
        for (int i = 0; i < neighbors.size(); i++) {
            xyLoc n = neighbors[i];
            if (!grid->IsValidLocation(n) || grid->IsBlocked(n)) {
                neighbors[i] = neighbors.back();
                neighbors.pop_back();
                i--;
            }
        }
        for (int i = 0; i < neighbors.size(); i++) {
                PathNode neigh;
                neigh.position = neighbors[i];
                
                //|l1.x − l2.x| + |l1.y − l2.y|
                
                neigh.h = heuristic(neigh.position, grid->GetGoalLocation());
                neigh.g = heuristic(start, neigh.position);
                neigh.f = neigh.h+neigh.f;
                currentNode.adjacent.push_back(neigh);
                //            open.push_back(neigh)
                
            
        }
        for (int i = 0; i < currentNode.adjacent.size(); i++) {
//            cout << "Adjacent node " << currentNode.adjacent[i].position << "\n";
//            cout << "Adjacent node f " << currentNode.adjacent[i].f << "\n";

//            if (currentNode.adjacent[i].position == grid->GetGoalLocation()) {
//                return currentNode.adjacent[i].position;
//            }
            if (contains(closed, currentNode.adjacent[i])){
                continue;
            }
            else if(!contains(open, currentNode.adjacent[i])) {
//                cout << "Not in open " << currentNode.adjacent[i].position << "\n";
                currentNode.adjacent[i].parent = currentNode.position;
                currentNode.adjacent[i].h = heuristic(currentNode.adjacent[i].position, next.position);
                currentNode.adjacent[i].g = currentNode.g + 1;
                currentNode.adjacent[i].f = currentNode.adjacent[i].h+currentNode.adjacent[i].f;
                open.push_back(currentNode.adjacent[i]);
                
                /* v contains x */
            }
            else {
//                cout <<"thingss\n";
                if ((currentNode.g+1 )< currentNode.adjacent[i].g) {
                    currentNode.adjacent[i].parent = currentNode.position;
                    currentNode.adjacent[i].g =currentNode.g+1;
                    currentNode.adjacent[i].f = currentNode.adjacent[i].g+currentNode.adjacent[i].h;

                }

            }
            
        }
        if (open.size() == 0) {
            return kInvalidXYLoc;
        }
        int min = 0;
        PathNode minNode;
        minNode = open[0];
        int dups = 0;
        for(int i = 0; i < open.size(); i++)
            if(open[i].f < minNode.f) {
                minNode = open[i];
                min = i;
            }
            else if(open[i].f == minNode.f) {
                //            cout << "lol\n";
                if(open[i].g>minNode.g) {
                    minNode = open[i];
                    min = i;
                    
                } else if(open[i].g==minNode.g) {
                    
                    minNode = ((open[i].position < minNode.position) ? open[i] : minNode);
                    min = i;
                    
                }
            }
        
    
    //    cout << "Min node "<<minNode.
        currentNode = minNode;
//        cout <<"Lowest node " << currentNode.position << "\n";
        closed.push_back(currentNode);
//        cout <<"open before: " << open.size() << "\n";
        open[min] = open.back();
        open.pop_back();
//        cout <<"open after: " << open.size()<< "\n";

        
//        cout << grid->GetCurrentLocation();
       
//        else
//            //        cout <<neighbors[rand()%neighbors.size()];
//            return neighbors[rand()%neighbors.size()];

    } while (currentNode.position !=next.position);
//                return xyLoc(3,3);
//    cout <<"Return node " << currentNode.position << "\n";
    return currentNode.parent;


}

int GetNumExpansions() {
	// TODO
	return 0;
}
