/*
 * Copyright 2015 <copyright holder> <email>
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
#include <algorithm>
#include <vector>

#include "dimacs.h"

using namespace std;


/// Simple Edge class: store tuple (i,j,c)
class Edge {
  
   public:
      node_t    u;  /// Source node
      node_t    v;  /// Target node
      cost_t    c;  /// Cost of the arc
      
      /// Standard constructor
      Edge( node_t _u, node_t _v, cost_t _c ) 
         : u(_u), v(_v), c(_c) {}
      
      inline bool operator<(const Edge& rhs) const { return c < rhs.c; }
};

typedef vector<Edge>::iterator EdgeIterator;


class SpanningTree {
  
private:
  
  vector<Edge> edges;
  cost_t total_cost;
  long max_edges;
  
public:
  
  SpanningTree(node_t n_nodes) : total_cost(0), max_edges(n_nodes-1) { }
  
  void print_edges() 
  {
    for (EdgeIterator iter = edges.begin(); iter < edges.end(); ++iter)
	  cout << "from: " << (*iter).u+1 << " ==> to: " << (*iter).v+1 << " (" << (*iter).c << ")\n";
  }
  
  cost_t get_total_cost()
  {
    return total_cost;
  }
  
  void addEdge(Edge _edge)
  {
    edges.push_back(_edge);
    total_cost += _edge.c;
  }
  
  bool is_completed()
  {
    return edges.size() == max_edges;
  }
  
  bool generate_cycle(Edge edge)
  {
    bool source_match, target_match;
    source_match = target_match = false;
    
    for (EdgeIterator iter = edges.begin(); iter < edges.end(); ++iter)
    {
      if (edge.u == (*iter).u || edge.u == (*iter).v)
	source_match = true;
      
      if (edge.v == (*iter).u || edge.v == (*iter).v)
	target_match = true;
      
      if (source_match && target_match) return true;
    }
    
    return false;
  }
  
};



class Graph {
  
   private:
     
      node_t  n_nodes;
      edge_t  m_edges;
      vector<Edge> edges;   

   public:	
     
      Graph(node_t _n, edge_t _m) : n_nodes(_n), m_edges(_m)
      {
         //edges.reserve(n_nodes-1);
      }
      
      void addArc(node_t source_node, node_t target_node, cost_t cost) {    
         edges.push_back(Edge(source_node, target_node, cost));
      }

      node_t get_nnodes()
      {
	return n_nodes;
      }
      
      void print_edges_list() 
      {
	for (EdgeIterator iter = edges.begin(); iter < edges.end(); ++iter)
	  cout << "from: " << (*iter).u+1 << " ==> to: " << (*iter).v+1 << " (" << (*iter).c << ")\n";
      }
      
      SpanningTree kruskal_mst() 
      {
	SpanningTree mst(n_nodes);
	sort(edges.begin(), edges.end());
	
	for(EdgeIterator iter = edges.begin(); iter < edges.end(); ++iter)
	{
	  if (mst.is_completed()) break;
	  
	  if (mst.generate_cycle(*iter)) continue;
	  
	  mst.addEdge(*iter);
	}
	
	return mst;
      }
};

