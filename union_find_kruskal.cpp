/*
 * Copyright 2015 Thiago Nascimento <nascimenthiago@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "stdio.h"
#include "string.h"
#include "vector"
#include "algorithm"

using namespace std;

#define pii pair<int, int>
#define pip pair<int, pii>
#define F first
#define S second

typedef int32_t    node_t;
typedef int32_t    edge_t;
typedef int64_t    cost_t;

// Fast input function
inline void inp(int *n)	
{
    *n = 0;
    int ch = getchar_unlocked();
    int sign = 1;
    while(ch < '0' || ch > '9') 
    {
        if (ch == '-') 
            sign = -1;
        ch = getchar_unlocked();
    }
    while(ch >= '0' && ch <= '9')
        (*n) = ((*n)<<3) + ((*n)<<1) + ch - '0', ch = getchar_unlocked();
    *n = (*n)*sign;
}

const int MAX = 99999999;

// Class implementing Union Find Data Structure with Path Compression
class Union_Find
{
  public:

	int id[MAX], sz[MAX];
	Union_Find(int n)	//class constructor
	{
		for (int i = 0; i < n; ++i)
		{
			id[i] = i;
			sz[i] = 1;
		}
	}
	
	int root(int i)
	{
		while(i != id[i])
		{
			id[i] = id[id[i]];	//path Compression
			i = id[i];
		}
		return i;
	}
	int find(int p, int q)
	{
		return root(p)==root(q);
	}
	void unite(int p, int q)
	{
		int i = root(p);
		int j = root(q);

		if(sz[i] < sz[j])
		{
			id[i] = j;
			sz[j] += sz[i];
		}
		else
		{
			id[j] = i;
			sz[i] += sz[j];
		}
	}
};


class GraphUF {
  
private:
  vector<pip> graph;
  int n, e;
  long long int T;
  int i;
  
public:
  
  GraphUF(node_t n_nodes, edge_t m_edges) : n(n_nodes), e(m_edges), i(0), T(0)
  {
    graph.resize(e);
  }
  
  
  void addArc(node_t source_node, node_t target_node, cost_t cost) 
  {    
    graph[i++] = pip(cost, pii(source_node, target_node));
  }
  
  void Kruskal_MST()
  {
	//sort the edges in increasing order of cost
	sort(graph.begin(), graph.end());
	
	Union_Find UF(n);
	int u, v;

	for (int i = 0; i < e; ++i)
	{
		u = graph[i].S.F;
		v = graph[i].S.S;
		if( !UF.find(u, v) )
		{
			UF.unite(u, v);
			T += graph[i].F;
		}
	}
  }
  
  long long int get_total_cost()
  {
    return T;
  }
  
};
  





