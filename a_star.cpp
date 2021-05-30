#include<bits/stdc++.h>
using namespace std;
#define ROW 9
#define COL 10
typedef pair<int, int> Pair;

typedef pair<double, pair<int, int> > pPair;
struct cell {
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

bool isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) && (col >= 0)
		&& (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col)
{
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

double calculateHValue(int row, int col, Pair dest)
{
	return ((double)sqrt(
		(row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}
void tracePath(cell cellDetails[][COL], Pair dest)
{
	printf("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
	}

	return;
}
void aStarSearch(int grid[][COL],Pair src, Pair dest){
	if(isValid(src.first,src.second)==false){
		cout<<"Source is Invalid"<<endl;
		return;
	}
	if(isValid(dest.first,dest.second)==false){
		cout<<"Destination is invalid"<<endl;
		return;
	}
	bool closedList[ROW][COL];
	memset(closedList,false,sizeof(closedList));
	cell cellDetails[ROW][COL];
	int i,j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;
	set<pPair> openList;
	openList.insert(make_pair(0.0,make_pair(i,j)));
	bool foundDest = false;
	while(!openList.empty()){
		pPair p = *openList.begin();
		
		i = p.second.first;
		j = p.second.second;
		openList.erase(openList.begin());

		closedList[i][j]=true;
		double gNew, hNew, fNew;
		vector<int> dir={-1,0,1,0,-1}; 
		for(int k=0;k<dir.size()-1;k++){
			if(isValid(i+dir[k],j+dir[k+1])==true){
				if(isDestination(i+dir[k],j+dir[k+1],dest)==true){
					cellDetails[i+dir[k]][j+dir[k+1]].parent_i=i;
					cellDetails[i+dir[k]][j+dir[k+1]].parent_j=j;
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				}
			else if(closedList[i+dir[k]][j+dir[k+1]]== false && isUnBlocked(grid, i+dir[k],j+dir[k+1])== true){
				gNew=cellDetails[i][j].g+1.0;
				hNew = calculateHValue(i+dir[k],j+dir[k+1], dest);
				fNew = gNew + hNew;
				if (cellDetails[i+dir[k]][j+dir[k+1]].f == FLT_MAX || cellDetails[i+dir[k]][j+dir[k+1]].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i+dir[k],j+dir[k+1])));
					cellDetails[i+dir[k]][j+dir[k+1]].f = fNew;
					cellDetails[i+dir[k]][j+dir[k+1]].g = gNew;
					cellDetails[i+dir[k]][j+dir[k+1]].h = hNew;
					cellDetails[i+dir[k]][j+dir[k+1]].parent_i = i;
					cellDetails[i+dir[k]][j+dir[k+1]].parent_j = j;
				}
			}
		}
	}
	}
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");
	return;
}

int main(){
		int grid[ROW][COL] = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
			{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
			{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
	Pair src = make_pair(8, 0);

	Pair dest = make_pair(0, 0);

	aStarSearch(grid, src, dest);
	return 0;
}
