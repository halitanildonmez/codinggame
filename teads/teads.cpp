#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <stdio.h>
#include <cstring>
#include <queue>  
#include <unordered_map>

using namespace std;

map <int, vector<int> > adjMatrix;

int getElemIndex (vector <int> lis, int elem)
{
    if ( lis.size() == 0)
    {
        return -1;
    }
    for ( int i = 0; i < lis.size(); i++)
    {
        if ( lis[i] == elem)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n;
    cin >> n; cin.ignore();
    
    int depth = 0;

    for (int i = 0; i < n; i++) {
        int xi;
        int yi;
        cin >> xi >> yi; cin.ignore();
        
        if ( adjMatrix.count(xi) > 0)
        {
            adjMatrix[xi].push_back(yi);
        }
        else
        {
            vector<int> tmp;
            tmp.push_back(yi);
            adjMatrix.insert(make_pair(xi,tmp));
        }
        
        if ( adjMatrix.count(yi) > 0)
        {
            adjMatrix[yi].push_back(xi);
        }
        else
        {
            vector<int> tmp;
            tmp.push_back(xi);
            adjMatrix.insert(make_pair(yi,tmp));
        }
    }
    
    int prevSize = adjMatrix.size();
    do
    {
        map <int , int> deletedKeys;
        map<int,vector<int>>::iterator it=adjMatrix.begin();
    
        while ( it!=adjMatrix.end())
        {
            if ( it->second.size() == 1 ){
                vector<int> tmp = it->second;
                deletedKeys.insert(make_pair(it->first, tmp.front() ));
                adjMatrix.erase(it++);
            }
            else if (it->second.size() == 0 )
            {
                adjMatrix.erase(it++);
            }
            else
                ++it;
        }
        
        for (map<int,int>::iterator it=deletedKeys.begin(); it!=deletedKeys.end(); ++it)
        {
            int vecToSearch = it->second;
            int itemIndex = it->first;
            int elemInd = getElemIndex(adjMatrix[vecToSearch], itemIndex);
            if ( elemInd != -1)
                adjMatrix[vecToSearch].erase(adjMatrix[vecToSearch].begin()+elemInd, adjMatrix[vecToSearch].begin()+elemInd+1);    
        }
        
        if (adjMatrix.size() > 0  && prevSize != adjMatrix.size()){
            depth++;
            prevSize = adjMatrix.size();
        }
    }
    while(adjMatrix.size() > 0);
 
 
    if ( depth > 2)
        cout << depth <<endl;
    else
        cout << 2 << endl;
    
}