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
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <fstream>

using namespace boost;
using namespace std;

typedef int32_t    node_t;
typedef int32_t    edge_t;
typedef int64_t    cost_t;

typedef adjacency_list < vecS, vecS, undirectedS, no_property, property < edge_weight_t, int > > GraphB;
typedef graph_traits<GraphB>::edge_descriptor EdgeB;
typedef graph_traits<GraphB>::vertex_descriptor Vertex;
typedef std::pair<int, int> E;


class GraphBoost {
  
private:
    int num_nodes;
    size_t num_edges;
    GraphB g;
    property_map<GraphB, edge_weight_t>::type weightmap;
    property_map < GraphB, edge_weight_t >::type weight;
    vector<EdgeB> spanning_tree;
  
public:
  
    GraphBoost(node_t n_nodes, edge_t m_edges) : num_nodes(n_nodes), num_edges(m_edges), g(GraphB(n_nodes)) 
    { 
        get(edge_weight, g);
    }
  
  void addArc(node_t source_node, node_t target_node, cost_t cost) 
  {    
    EdgeB e; bool inserted;
    tie(e, inserted) = add_edge(source_node, target_node, g);
    weightmap[e] = cost;
  }
  
  void kruskal_mst()
  {
    weight = get(edge_weight, g);
    kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
  }
  
  void print_spanning_tree() 
  {
    for (vector<EdgeB>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
      cout << source(*ei, g) << " <--> " << target(*ei, g) << " with weight of " << weight[*ei]	<< std::endl;
    }
  }
  
  int get_total_cost() 
  {
    int cost = 0;
    
    for (vector<EdgeB>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) 
      cost += weight[*ei];
    
    return cost;
  }
  
};


 

  

