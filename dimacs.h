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
#include <fstream>
#include <sstream>

#ifndef DIMACS_H
#define DIMACS_H

typedef int32_t    node_t;
typedef int32_t    edge_t;
typedef int64_t    cost_t;

template<typename G>
class Dimacs
{
    public :
  
        static G load_digraph(char* dimacs_instance_path)
        { 
            node_t n_nodes;
            edge_t m_edges;
        
            /// Read instance from the DIMACS
            ifstream infile(dimacs_instance_path); 
            if (!infile) 
            exit (EXIT_FAILURE); 

            string line, ps;
            char lineheader;
            bool finishedHeader = false;
            
            // Reading file header
            while (!finishedHeader) 
            {
                getline(infile, line);
                istringstream linestream(line);
                linestream >> lineheader;
                
                switch(lineheader) {
                    
                    case 'c': 
                        break;
                    
                    case 'p':
                        linestream >> ps >> n_nodes >> m_edges;
                        break;
                        
                    case 'a': 
                        finishedHeader = true;
                        break;
                }
            }
            
            /// Build the graph
            G digraph = G(n_nodes, m_edges);
            
            int v, w;
            cost_t c;
            
            // Reading file body
            do 
            {
                istringstream linestream(line);
                linestream >> lineheader >> v >> w >> c;
                digraph.addArc(v-1, w-1, c);
            } while (getline(infile, line));
            
            return digraph;
        }
};


#endif // DIMACS_H
