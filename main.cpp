#include <boost/progress.hpp> 

//#include "my_dijkstra.cpp"
//#include "dijkstra_boost.cpp"
//#include "dimacs.h"


using namespace boost;
using boost::timer;

#include "dumbqueuetest.h"

int main(int argc, char **argv) {
    
   if (argc != 2) {
       cout << "usage: ./dijkstra <filename>\n";
       exit ( EXIT_FAILURE );
   }
   
  /*
   cost_t dist; 
   timer execution_timer;
   double init_time;
   node_t n_nodes, end_node;
  
   Digraph Graph = Dimacs<Digraph>::load_digraph(argv[1]);
   n_nodes = Graph.get_nnodes();
   end_node = n_nodes - 1;
   vector<node_t> Path(n_nodes);
   
   // Dijikistra execution
   init_time = execution_timer.elapsed();
   dist = Graph.shortest_path_for_dummies<SimpleQueue>(0, end_node, Path);
   cout << "Run Dijikistra - Traditional Queue\n";
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
   
   cout << "\n";
   
   // Dijikistra execution
   init_time = execution_timer.elapsed();
   dist = Graph.shortest_path<BinaryHeap>(0, end_node, Path);
   cout << "Run Dijikistra - Binary Heap\n";
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
   
   cout << "\n";
   
   // Dijikistra execution
   init_time = execution_timer.elapsed();
   dist = Graph.shortest_path<FibonacciHeap>(0, end_node, Path);
   cout << "Run Dijikistra - Fibonacci Heap\n";
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
   
   cout << "\n";
   
   // Dijikistra execution
   DigraphBoost GraphB = Dimacs<DigraphBoost>::load_digraph(argv[1]);
   init_time = execution_timer.elapsed();
   dist = GraphB.shortest_path(0, end_node);
   cout << "Run Dijikistra - Boost Library\n";
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
  */
  
  DumbQueueTest queueTest;
  queueTest.test_push_top();
  queueTest.test_push_pop();
  queueTest.test_push_increase();
  queueTest.test_push_pop_increase();
  
  return 0;
}


