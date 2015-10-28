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
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <vector>

using std::vector;

typedef int32_t    node_t;
typedef int32_t    edge_t;
typedef int64_t    cost_t;

using namespace boost;

typedef adjacency_list <vecS, vecS, directedS, no_property, property<edge_weight_t, cost_t> > DigraphB;
typedef graph_traits<DigraphB>::vertex_descriptor NodeB;


class DigraphBoost {
  
   private:
     
      node_t  n_nodes;
      edge_t  m_edges;
      DigraphB digraph;
      
   public:	
     
      DigraphBoost(node_t _n, edge_t _m) : n_nodes(_n), m_edges(_m), digraph(DigraphB(_n)) { }
     
      void addArc(node_t source_node, node_t target_node, cost_t cost) 
      {    
	add_edge(source_node, target_node, cost, digraph);
      }
      
      cost_t shortest_path(node_t start_node, node_t end_node)
      {
	vector<NodeB> P(n_nodes);
	vector<cost_t> D(n_nodes, std::numeric_limits<cost_t>::max());
	
	dijkstra_shortest_paths(digraph, start_node, predecessor_map(&P[0]).distance_map(&D[0]));
	
	return D[end_node];
      }
};

