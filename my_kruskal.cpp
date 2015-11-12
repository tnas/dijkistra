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

#define NO_CONNECTED_COMPONENT -1

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
typedef vector<Edge> EdgeList;
typedef vector<EdgeList>::iterator EdgeListIterator;


struct EdgeComponent {
  int component_source_node;
  int component_target_node;
  
  EdgeComponent() : 
    component_source_node(NO_CONNECTED_COMPONENT), component_target_node(NO_CONNECTED_COMPONENT) { }
};


class SpanningTree {
  
private:
  vector<EdgeList> connected_components;
  cost_t total_cost;
  long max_edges;
  
public:
  
  SpanningTree(node_t n_nodes) : total_cost(0), max_edges(n_nodes-1) { 
    
  }
  
  void print_connected_components() 
  {
    for(int component = 0; component < connected_components.size(); ++component)
    {
      for (EdgeIterator iter = connected_components[component].begin(); iter != connected_components[component].end(); ++iter)
      {
	cout << "from: " << (*iter).u+1 << " ==> to: " << (*iter).v+1 << " (" << (*iter).c << ")\n";
      }
    }
  }
  
  cost_t get_total_cost()
  {
    return total_cost;
  }
  
  bool addEdge(Edge _edge, EdgeComponent map)
  {
    if (map.component_source_node == map.component_target_node) 
    {
      if (map.component_source_node == NO_CONNECTED_COMPONENT)
      {
	int component = connected_components.size();
	connected_components[component].push_back(_edge);
	return true;
      }
      
      return false;
    }
    else 
    {
      int component = map.component_source_node == NO_CONNECTED_COMPONENT ? map.component_target_node
	: map.component_source_node;
      connected_components[component].push_back(_edge);
      
      for (EdgeIterator iter = connected_components[map.component_target_node].begin(); 
	 iter != connected_components[map.component_target_node].end(); ++iter)
	   connected_components[component].push_back(*iter);
      connected_components.erase(connected_components.begin()+map.component_target_node);
    }
    
    total_cost += _edge.c;
    
    return true;
  }
  
  long get_max_edges()
  {
    return max_edges;
  }
  
  
  EdgeComponent lookup_edge_component(Edge edge)
  {
    EdgeComponent map;
    
    for(int component = 0; component < connected_components.size(); ++component)
    {
      for (EdgeIterator iter = connected_components[component].begin(); iter != connected_components[component].end(); ++iter)
      {
	if (edge.u == (*iter).u || edge.u == (*iter).v)
	  map.component_source_node = component;
	
	if (edge.v == (*iter).u || edge.v == (*iter).v)
	  map.component_target_node = component;
      }
    }
    
    return map;
  }
  
};



class Graph {
  
   private:
     
      node_t  n_nodes;
      edge_t  m_edges;
      vector<Edge> edges;   

   public:	
     
      Graph(node_t _n, edge_t _m) : n_nodes(_n), m_edges(_m) { }
      
      void addArc(node_t source_node, node_t target_node, cost_t cost) {    
         edges.push_back(Edge(source_node, target_node, cost));
      }

      node_t get_nnodes()
      {
	return n_nodes;
      }
      
      void print_edges() 
      {
	for (EdgeIterator iter = edges.begin(); iter < edges.end(); ++iter)
	  cout << "from: " << (*iter).u+1 << " ==> to: " << (*iter).v+1 << " (" << (*iter).c << ")\n";
      }
      
      SpanningTree kruskal_mst() 
      {
	SpanningTree mst(n_nodes);
	sort(edges.begin(), edges.end());
	
	long edges_added = 0;
	
	for(EdgeIterator iter = edges.begin(); iter < edges.end(); ++iter)
	{
	  
	  if (edges_added == mst.get_max_edges()) break;
	  
	  EdgeComponent edge_comp;
	  edge_comp = mst.lookup_edge_component(*iter);
	  if (mst.addEdge(*iter, edge_comp)) ++edges_added;
	}
	
	return mst;
      }
};

