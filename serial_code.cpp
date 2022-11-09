#include<bits/stdc++.h>

using namespace std;

int grid[100][100];

vector<pair<int,int>>empty_cells;
vector<pair<int,int>>type1_cells;
vector<pair<int,int>>type2_cells;
vector<pair<int,int>>unsatisfied_nodes;

//Here 0 = empty ,1= of type 1,2=of type 

void populate(int n,int m) 
{
    int i,j;
    srand(time(0));
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            int c=rand()%3;// 0,1,2 
            grid[i][j]=c;
        }
    }
    
}
void set_type(int n,int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(grid[i][j]==0)
            {
                empty_cells.push_back(make_pair(i,j));
            }
            else if(grid[i][j]==1)
            {
                type1_cells.push_back(make_pair(i,j));
            }
            else if(grid[i][j]==2)
            {
                type2_cells.push_back(make_pair(i,j));
            }
        }
    }
}
//displaying the grid
void display_grid(int n,int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
}

//finding unsatisfied nodes
void unsatisfied(int n,int m,int t)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(grid[i][j]==0)
            continue;
            int similar=0;
            int type=grid[i][j];
            if (i > 0 && grid[i - 1][j] == type)
                similar++;
            if (j > 0 && grid[i][j - 1] == type)
                similar++;
            if (i > 0 && j > 0&& grid[i - 1][j - 1] == type)
                similar++;            
            if (i < n - 1 && grid[i + 1][j] == type)
                similar++;
            if (j < m - 1 && grid[i][j + 1] == type)
                similar++;
            if (i < n- 1 && j < m - 1&& grid[i + 1][j + 1] == type)
                similar++;
            if (i < n - 1 && j > 0&& grid[i + 1][j - 1] == type)
                similar++;
            if (i > 0 && j < m - 1&& grid[i - 1][j + 1] == type)
                similar++;
            if(similar<t)
            unsatisfied_nodes.push_back(make_pair(i,j));
        }
    }
}

void make_a_node_satisfied()
{
    //srand(time(0));
    if(unsatisfied_nodes.size()!=0)
    {
        int c1=rand()%(unsatisfied_nodes.size());  
        int c2=rand()%(empty_cells.size());
        grid[empty_cells[c2].first][empty_cells[c2].second]=grid[unsatisfied_nodes[c1].first][unsatisfied_nodes[c1].second];
        grid[unsatisfied_nodes[c1].first][unsatisfied_nodes[c1].second]=0;
    }
}

int main()
{
    int n,m; // houses as grid of nxm
    cin>>n>>m;
    int t; //threshold value
    cin>>t;
    populate(n,m);
    set_type(n,m);
    display_grid(n,m);
    //boundary_cells(n,m);
    unsatisfied(n,m,t);
    int i;
    for(i=0;i<1000;i++)
    {
        make_a_node_satisfied();
        empty_cells.clear();
        type1_cells.clear();
        type2_cells.clear();
        set_type(n,m);
    }
    cout<<"After Schelling Segregation :"<<endl;
    display_grid(n,m);
    return 0;
}
/*
input: 

2 2 1 2 1 2 2 1 0 1 
1 2 2 0 0 2 0 2 0 2 
2 1 2 2 0 1 1 0 0 0 
2 0 0 1 2 2 0 0 1 1 
2 0 0 1 0 2 0 1 1 1 
1 1 0 1 2 0 0 0 0 2 
1 0 2 1 2 0 0 2 1 2 
1 0 0 2 1 1 2 2 2 1 
0 2 2 1 1 1 1 1 2 0 
1 0 0 1 1 0 2 2 0 0 

*/

/*
output :
2 2 0 0 0 2 2 0 0 0 
0 2 2 1 2 2 2 0 1 0 
2 0 2 2 2 0 0 0 0 1 
2 0 2 0 2 2 1 1 1 1 
0 0 2 1 1 2 0 1 1 1 
1 1 1 1 2 1 1 2 0 0 
1 1 0 1 2 1 0 2 0 2 
0 1 0 2 1 1 2 2 2 0 
2 0 2 1 1 1 1 0 2 0 
0 0 0 1 1 1 0 2 2 1
*/

