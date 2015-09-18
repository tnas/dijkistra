#include <iostream>

//#include <boost/version.hpp>
//#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dimacs.hpp>
#include <boost/graph/graphviz.hpp>


using namespace boost::graph;
  
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;





int main(int argc, char **argv) {
    
  std::ifstream inGraphFile;
  inGraphFile.open("instances/USA-road-d.NY.gr");
  
  
  dimacs_basic_reader reader(inGraphFile, false);
  dimacs_basic_reader end;
  
  dimacs_edge_iterator<dimacs_basic_reader> dimacsStart(reader);
  dimacs_edge_iterator<dimacs_basic_reader> endIter(end);
  
  Graph graph(dimacsStart, endIter, reader.n_vertices());
  boost::write_graphviz<Graph>(std::cout, graph); 
  
  return 0;
}



void get_boost_version() 
{
  std::cout << "Using Boost "
	    << BOOST_VERSION / 100000 << "."
	    << BOOST_VERSION / 100 % 1000 << "."
	    << BOOST_VERSION % 100
	    << std::endl;
}