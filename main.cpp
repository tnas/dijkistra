#include <boost/progress.hpp> 

#include "my_dijkstra.cpp"
#include "dijkstra_boost.cpp"
#include "dimacs.h"


using namespace boost;
using boost::timer;



int main(int argc, char **argv) {
    
   if (argc != 2) {
       cout << "usage: ./dijkstra <filename>\n";
       exit ( EXIT_FAILURE );
   }
  
   cost_t dist; 
   timer execution_timer;
   double init_time;
  
   /// Invoke the Dijkstra algorithm implementation
   Digraph Graph = Dimacs<Digraph>::load_digraph(argv[1]);
   vector<node_t> Path(Graph.get_nnodes());
   
   // Dijikistra execution
   init_time = execution_timer.elapsed();
   dist = Graph.shortest_path_for_dummies<SimpleQueue>(0, 5, Path);
   cout << "Run Dijikistra - Traditional Queue\n";
   //cout << "Distance Vector: "; print_distance_vector(Path);
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
   
   cout << "\n";
   
   // Dijikistra execution
   init_time = execution_timer.elapsed();
   dist = Graph.shortest_path<BinaryHeap>(0, 5, Path);
   cout << "Run Dijikistra - Binary Heap\n";
   //cout << "Distance Vector: "; print_distance_vector(Path);
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
   
   cout << "\n";
   
   // Dijikistra execution
   init_time = execution_timer.elapsed();
   dist = Graph.shortest_path<FibonacciHeap>(0, 5, Path);
   cout << "Run Dijikistra - Fibonacci Heap\n";
   //cout << "Distance Vector: "; print_distance_vector(Path);
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
   
   cout << "\n";
   
   // Dijikistra execution
   DigraphBoost GraphB = Dimacs<DigraphBoost>::load_digraph(argv[1]);
   init_time = execution_timer.elapsed();
   dist = GraphB.shortest_path(0, 5);
   cout << "Run Dijikistra - Boost Library\n";
   //cout << "Distance Vector: "; print_distance_vector(Path);
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
  
  return 0;
}


