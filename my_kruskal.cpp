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
#include <boost/concept_check.hpp>

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


int compare(const void* a, const void* b)
{
	if ((*(Edge*)a).c < (*(Edge*)b).c) return -1;
// 	if ((*(Edge*)a).c == (*(Edge*)b).c) return 0;
	if ((*(Edge*)a).c > (*(Edge*)b).c) return 1;
    return 0; //(*(Edge*)a).c == (*(Edge*)b).c
}

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
  
  SpanningTree(node_t n_nodes) : total_cost(0), max_edges(n_nodes-1) { }
  
  void print_connected_components() 
  {
    for(unsigned int component = 0; component < connected_components.size(); ++component)
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
	EdgeList tmp;
	tmp.reserve(10);
	connected_components.push_back(tmp);
	connected_components[component].push_back(_edge);
	
	// Adding back arc
	Edge back_arc(_edge.v, _edge.u, _edge.c);
	connected_components[component].push_back(back_arc);
	
	total_cost += _edge.c;
	
	return true;
      }
      
      return false;
    }
    else 
    {
      
      if (map.component_source_node == NO_CONNECTED_COMPONENT || map.component_target_node == NO_CONNECTED_COMPONENT)
      {
	int component = map.component_source_node == NO_CONNECTED_COMPONENT ? map.component_target_node
	  : map.component_source_node;
	connected_components[component].push_back(_edge);
	
	// Adding back arc
	Edge back_arc(_edge.v, _edge.u, _edge.c);
	connected_components[component].push_back(back_arc);
      }
      else
      {
	int component, del_component;
	
	if (map.component_source_node < map.component_target_node)
	{
	  component = map.component_source_node;
	  del_component = map.component_target_node;
	}
	else 
	{
	  component = map.component_target_node;
	  del_component = map.component_source_node;
	}
	
	connected_components[component].push_back(_edge);
	
	// Adding back arc
	Edge back_arc(_edge.v, _edge.u, _edge.c);
	connected_components[component].push_back(back_arc);
	
	for (EdgeIterator iter = connected_components[del_component].begin(); 
	  iter != connected_components[del_component].end(); ++iter)
	    connected_components[component].push_back(*iter);
	connected_components.erase(connected_components.begin()+del_component);
      }
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
    
    for(unsigned int component = 0; component < connected_components.size(); ++component)
    {
      for (EdgeIterator iter = connected_components[component].begin(); iter != connected_components[component].end(); ++iter)
      {
	if (edge.u == (*iter).u || edge.u == (*iter).v)
	  map.component_source_node = component;
	
	if (edge.v == (*iter).u || edge.v == (*iter).v)
	  map.component_target_node = component;
	
	if (edge.u != NO_CONNECTED_COMPONENT && edge.v != NO_CONNECTED_COMPONENT)
		return map;
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
      
      
      
      SpanningTree kruskal_mst() 
      {
	SpanningTree mst(n_nodes);
	//sort(edges.begin(), edges.end());
	qsort(&edges[0], edges.size(), sizeof(Edge), compare);
	
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

