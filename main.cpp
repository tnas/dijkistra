

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "common/dimacs.h"
#include "test/spptest.cpp"

using namespace boost;
using namespace std;
using boost::timer;

enum Algorithm { DIJKSTRA, KRUSKAL, PRIM };

int main(int argc, char **argv) {

    int opt;
    int alg = DIJKSTRA;
    char* file_name = NULL;
	SPPTest spptest;

    while ((opt = getopt(argc, argv, "a:f:")) != -1)
    {
        switch (opt)
        {
            case 'f' :
                file_name = optarg;
                break;
                
            case 'a' :
                alg = atoi(optarg);
                break;      
                
            default :
                cout << "usage: ./[dijkstra|kruskal|prim] <filename>\n";
                exit (EXIT_FAILURE);
        }
    }

   switch (alg) 
   {
        case (DIJKSTRA) :
        spptest.run_dijkstra(file_name);
        break;
	
        case (KRUSKAL) :
        spptest.run_kruskal(file_name);
        break;
       
        case(PRIM) :
		cout << "Prim algorithm is not available\n";
			
        break;
   }
   
   return 0;
}


