#include <boost/progress.hpp> 

#include "my_dijkstra.cpp"
#include "my_kruskal.cpp"
#include "dijkstra_boost.cpp"
#include "kruskal_boost.cpp"
#include "union_find_kruskal.cpp"
#include "dimacs.h"
#include "my_prim.cpp"


using namespace boost;
using boost::timer;

enum Algorithm { DIJKSTRA, KRUSKAL, PRIM };


void run_dijkstra(char* graph_path)
{
   cost_t dist; 
   timer execution_timer;
   double init_time;
   node_t n_nodes, end_node;
  
   Digraph Graph = Dimacs<Digraph>::load_digraph(graph_path);
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
   DigraphBoost GraphB = Dimacs<DigraphBoost>::load_digraph(graph_path);
   init_time = execution_timer.elapsed();
   dist = GraphB.shortest_path(0, end_node);
   cout << "Run Dijikistra - Boost Library\n";
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, dist);
}

void run_kruskal(char* graph_path)
{
  
   timer execution_timer;
   double init_time;
   
   Graph graph = Dimacs<Graph>::load_digraph(graph_path);
   init_time = execution_timer.elapsed();
   SpanningTree mst = graph.kruskal_mst();
   cout << "Run Kruskal - Vector Implementation\n";
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, mst.get_total_cost());
   
   cout << "\n";
   
   GraphBoost graphB = Dimacs<GraphBoost>::load_digraph(graph_path);
   init_time = execution_timer.elapsed();
   graphB.kruskal_mst();
   cout << "Run Kruskal - Boost Implementation\n";
   fprintf(stdout, "Time: %.4f\nCost: %d\n", execution_timer.elapsed() - init_time, graphB.get_total_cost());
   
   cout << "\n";
   
   GraphUF graphUF = Dimacs<GraphUF>::load_digraph(graph_path);
   init_time = execution_timer.elapsed();
   graphUF.Kruskal_MST();
   cout << "Run Kruskal - Union Find Implementation\n";
   fprintf(stdout, "Time: %.4f\nCost: %lld\n", execution_timer.elapsed() - init_time, graphUF.get_total_cost());
   
}


void run_prim(char* graph_path)
{
  
   timer execution_timer;
   double init_time;
   
   PrimGraph graph = Dimacs<PrimGraph>::load_digraph(graph_path);
   init_time = execution_timer.elapsed();
   graph.prim_mst();
   cout << "Run Prim - DHeap Implementation\n";
   fprintf(stdout, "Time: %.4f\nCost: %lu\n", execution_timer.elapsed() - init_time, graph.get_total_cost());
   
   cout << "\n";
}

int main(int argc, char **argv) {
   
   Algorithm alg = PRIM;
  
   if (argc != 2) {
       cout << "usage: ./[dijkstra|kruskal|prim] <filename>\n";
       exit ( EXIT_FAILURE );
   }
   
   switch (alg) 
   {
     case (DIJKSTRA) :
	run_dijkstra(argv[1]);
	break;
	
     case (KRUSKAL) :
       run_kruskal(argv[1]);
       break;
       
     case(PRIM) :
       run_prim(argv[1]);
       break;
   }
  
  return 0;
}


