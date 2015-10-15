#include <iostream>
#include <vector>
#include <string>
#include <inttypes.h>
#include <fstream>
#include <assert.h>
#include <sstream>

#include <boost/cstdint.hpp> // ver o que eh
#include <boost/integer_traits.hpp> // ver o que eh
#include <boost/progress.hpp> // ver o que eh
#include <boost/heap/d_ary_heap.hpp>
#include <boost/heap/fibonacci_heap.hpp>

using namespace boost;
using boost::timer;

using namespace std;
using std::vector;


typedef int32_t    node_t;
typedef int32_t    edge_t;
typedef int64_t    cost_t;

void inline print_distance_vector(vector<node_t> path);

/// Data structure to store Key-Value pairs in a 
/// PriorityQueue (as a Fibonacci heap)
struct ValueKey {
   cost_t d;
   node_t u;
   ValueKey(cost_t _d, node_t _u)
      : d(_d), u(_u) {}
   /// The relation establishes the order in the PriorityQueue
   inline bool operator<(const ValueKey& rhs) const { return d < rhs.d; }
};


typedef boost::heap::d_ary_heap<ValueKey, boost::heap::arity<2>, boost::heap::mutable_<true> > BinaryHeap;
typedef boost::heap::fibonacci_heap<ValueKey> FibonacciHeap;


/// Label for the labeling and/or dijkstra algorithm
enum Label { UNREACHED, LABELED, CLOSED };


/// Simple Arc class: store tuple (i,j,c)
class Arc {
   public:
      node_t    w;  /// Target node
      cost_t    c;  /// Cost of the arc
      /// Standard constructor
      Arc ( node_t _w, cost_t _c ) 
         : w(_w), c(_c) {}
};


/// Forward and Backward star: intrusive list
typedef vector<Arc> 	    FSArcList;
typedef FSArcList::iterator FSArcIter;


class Digraph {
  
   private:
      node_t  n_nodes;
      edge_t  m_edges;

      vector<FSArcList> adjacency_list;   

      /// Initialize distance vector with Infinity
      const cost_t Inf;
      
   public:
      ///Standard constructor
      Digraph(node_t _n, edge_t _m) 
         : n_nodes(_n), m_edges(_m), Inf(std::numeric_limits<cost_t>::max())
      {
         assert(n_nodes < Inf && m_edges < Inf);
         adjacency_list.reserve(n_nodes);
         /// Reserve memory for the set of arcs
         int avg_degree = m_edges/n_nodes+1;
         for ( int i = 0; i < n_nodes; ++i ) {
            FSArcList tmp;
            tmp.reserve(avg_degree);   
            adjacency_list.push_back(tmp);
         }
      }
      
      void addArc(node_t source_node, node_t target_node, cost_t cost) {    
         adjacency_list[source_node].push_back(Arc(target_node, cost));
      }
      
      void print_adjacency_list() {
	
	vector<FSArcList>::iterator it_nodes;
	node_t node = 0;
	
	for (it_nodes = adjacency_list.begin(); it_nodes < adjacency_list.end(); ++it_nodes) {
	  
	  cout << "from: " << node++ << " ==> ";
	  
	  FSArcIter it_arc;
	  
	  for (it_arc = (*it_nodes).begin(); it_arc < (*it_nodes).end(); ++it_arc) {
	    cout << "to:" << (*it_arc).w << " (" << (*it_arc).c << ") | ";
	  }
	  
	  cout << "\n";
	}
      }
     
      ///--------------------------------------------------
      /// Shortest Path for a graph with positive weights
      ///--------------------------------------------------
      template <typename PriorityQueue>
      cost_t shortest_path(node_t start_node, node_t end_node, vector<node_t>& previous) {    
	
         typedef typename PriorityQueue::handle_type     handle_t;
	 
         PriorityQueue     digraph_priority_queue;
         vector<handle_t>  distance_from_source(n_nodes);
         vector<Label>     node_status(n_nodes, UNREACHED);  
	 
         /// Initialize the source distance
         distance_from_source[start_node] = digraph_priority_queue.push(ValueKey(0, start_node));
         
         while (!digraph_priority_queue.empty()) {
	   
	    //print_vector(previous);
	   
            ValueKey p = digraph_priority_queue.top();
            digraph_priority_queue.pop();
            node_t current_node  = p.u;
            node_status[current_node] = CLOSED;
            cost_t Du = -(*distance_from_source[current_node]).d;
	    
            if (current_node == end_node) { break; }
            
            /// For all edges (u, v) in E
            for (FSArcIter arc_iter = adjacency_list[current_node].begin(), it_end = adjacency_list[current_node].end(); arc_iter != it_end; ++arc_iter) {
	      
               node_t target_node = arc_iter->w;
	       
               if (node_status[target_node] != CLOSED) {
		 
                  cost_t Duv = arc_iter->c;
                  cost_t Dv  = Du + Duv;
		  
                  if (node_status[target_node] == UNREACHED) {
                     previous[target_node] = current_node;
                     node_status[target_node] = LABELED;
                     distance_from_source[target_node] = digraph_priority_queue.push(ValueKey(-Dv, target_node));
                  } 
                  else {
                     if (-(*distance_from_source[target_node]).d > Dv) {
                        previous[target_node] = current_node;
                        digraph_priority_queue.increase(distance_from_source[target_node], ValueKey(-Dv, target_node));
                     }
                  }
               }
            }
         }
         
         return -(*distance_from_source[end_node]).d;
      }
      
      void print_vector(vector<node_t> previous) {
	for (vector<node_t>::iterator iter = previous.begin(); iter != previous.end(); ++iter) 
	  cout << *iter << " ";
	cout << "\n";
      }
      
};


/// Read input data, build graph, and run Dijkstra
cost_t runDijkstra( char* argv[] ) {
  
   /// Read instance from the DIMACS
   ifstream infile(argv[1]); 
   if (!infile) 
      exit ( EXIT_FAILURE ); 

   int n_nodes;     /// Number of nodes
   int m_edges;     /// Number of edges
      
   string line, ps;
   char lineheader;
   bool finishedHeader = false;
   
   // Reading file header
   while (!finishedHeader) {
     getline(infile, line);
     istringstream linestream(line);
     linestream >> lineheader;
     
     switch(lineheader) {
       case 'c': break;
       case 'p':
	 linestream >> ps >> n_nodes >> m_edges;
	 break;
       case 'a': 
	 finishedHeader = true;
	 break;
     }
   }
   
   /// Build the graph
   Digraph Graph(n_nodes, m_edges);
   
   int v, w;
   cost_t c;
   
   // Reading file body
   do {
     istringstream linestream(line);
     linestream >> lineheader >> v >> w >> c;
     Graph.addArc(v-1, w-1, c);
   } while (getline(infile, line));
   
   
   // Printing Digraph's adjacency_list
   //Graph.print_adjacency_list();
   
   vector<node_t> Path(n_nodes);
   cost_t dist; 
   
   // Dijikistra execution
   timer execution_timer;
   double init_time = execution_timer.elapsed();
   dist = Graph.shortest_path<BinaryHeap>(0, 5, Path);
   cout << "Run Dijikistra - Binary Heap\n";
   cout << "Distance Vector: ";
   print_distance_vector(Path);
   fprintf(stdout, "Time: %.4f, Cost: %d\n", execution_timer.elapsed() - init_time, dist);
   
   cout << "\n";
   
   // Dijikistra execution
   init_time = execution_timer.elapsed();
   dist = Graph.shortest_path<FibonacciHeap>(0, 5, Path);
   cout << "Run Dijikistra - Fibonacci Heap\n";
   cout << "Distance Vector: ";
   print_distance_vector(Path);
   fprintf(stdout, "Time: %.4f, Cost: %d\n", execution_timer.elapsed() - init_time, dist);

   return dist;
   
}


void inline print_distance_vector(vector<node_t> path) {
  for (vector<node_t>::iterator iter = path.begin(); iter != path.end(); ++iter)
     cout << *iter << " ";
  cout << "\n";
}

int main(int argc, char **argv) {
    
  if (argc != 2) {
      cout << "usage: ./dijkstra <filename>\n";
      exit ( EXIT_FAILURE );
  }
  
  /// Invoke the Dijkstra algorithm implementation
  cost_t T_dist = runDijkstra(argv);
  
  return 0;
}


