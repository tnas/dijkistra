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

using namespace boost;
using boost::timer;

using namespace std;
using std::vector;


typedef int32_t    node_t;
typedef int32_t    edge_t;
typedef int64_t    cost_t;


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


/// Label for the labeling and/or dijkstra algorithm
enum Label { UNREACHED, LABELED, SCANNED };


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
      /// Maybe it is better to intialize with an upper bound on the optimal path (optimal rcsp path)
      const cost_t Inf;
      
   public:
      ///Standard constructor
      Digraph(node_t _n, edge_t _m) 
         : n_nodes(_n), m_edges(_m), Inf(std::numeric_limits<cost_t>::max())
      {
         assert( n_nodes < Inf && m_edges < Inf );
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
      /// With a Fibonacci Heap, as given in the book "Algorithms" by Vazirani et all.
      /// NOTE: since 'increase' is O(1), while 'decrease' is O(log n)
      /// We use negative distances in the heap, i.e., we start with distance labels set to -\infinity
      /// However, the distance labels are kept with the correct value 
      
      template <typename PriorityQueue>
      cost_t shortest_path(node_t start_node, node_t end_node, vector<node_t>& path) {    
         typedef typename PriorityQueue::handle_type     handle_t;

         PriorityQueue     H;
         vector<handle_t>  K(n_nodes);
         vector<Label>     Q(n_nodes, UNREACHED);  
	 
         /// Initialize the source distance
         K[start_node] = H.push(ValueKey(0,S));
         /*
         while ( !H.empty() ) {
            /// u = deleteMin(H)
            ValueKey p = H.top();
            H.pop();
            node_t u  = p.u;
            Q[u] = SCANNED;
            cost_t Du = -(*K[u]).d;
            if ( u == end_node ) { break; }
            /// for all edges (u, v) \in E
            for ( FSArcIter it = Nc[u].begin(), it_end = Nc[u].end(); it != it_end; ++it ) {
               node_t v   = it->w;
               if ( Q[v] != SCANNED ) {
                  cost_t Duv = it->c;
                  cost_t Dv  = Du + Duv;
                  if ( Q[v] == UNREACHED ) {
                     path[v] = u;
                     Q[v] = LABELED;
                     K[v] = H.push( ValueKey(-Dv,v) );
                  } else {
                     if ( -(*K[v]).d > Dv ) {
                        path[v] = u;
                        H.increase( K[v], ValueKey(-Dv,v) );
                     }
                  }
               }
            }
         }
         assert( R[T] == SCANNED );
         */
         return -(*K[end_node]).d;
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
   Graph.print_adjacency_list();
   
   vector<node_t> P(n_nodes);
   cost_t T_dist; 
   
   // TODO: Dijikistra execution

   return T_dist;
   
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


