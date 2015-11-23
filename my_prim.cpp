/*
 * Copyright 2015 Thiago Nascimento <thiago.rodrigues@tre-es.jus.br>
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

#include "prim/prim2.h"
#include "prim/Grafo.h"


typedef int32_t    node_t;
typedef int32_t    edge_t;
typedef int64_t    cost_t;

class PrimGraph
{
private:
	Grafo grafo;
	node_t n_nodes;
	edge_t m_edges;
	int total_cost;
	
public:
	PrimGraph(node_t nodes, edge_t edges) : n_nodes(nodes), m_edges(edges), grafo(Grafo(n_nodes)) {  }
	
	void addArc(node_t source_node, node_t target_node, cost_t cost) 
	{    
		grafo.addAresta(source_node, target_node, cost);
	}
	
	void prim_mst()
	{
		total_cost = primMST(n_nodes, &grafo);
	}
	
	int get_total_cost()
	{
		return total_cost;
	}
	
};