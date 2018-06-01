#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include "graph.h"
using namespace std;

const int INF = 1000000000;//"infinfty"

TEST_CASE("Attributes graph without edges")
{
  CHECK_THROWS(Graph gr = Graph(-20));

  Graph gr = Graph(10);  

  vector<vector<int>> graph = gr.get_graph();

  CHECK(gr.get_size() == 10);

  for (int count = 0; count < 10; count++)
  {
    CHECK(graph[count].size() == 10);
  }
}

TEST_CASE("Add vertex")
{ 
  Graph gr = Graph(10);  

  gr.add_vertex();

  vector<vector<int>> graph = gr.get_graph();  

  CHECK(gr.get_size() == 11);

  for (int count = 0; count < 11; count++)
  {
    CHECK(graph[count].size() == 11);
  }
}

TEST_CASE("Add edge")
{
  Graph gr = Graph(10);  

  CHECK_THROWS(gr.add_edge(-1, 2, 3));
  CHECK_THROWS(gr.add_edge(1, -2, 3));
  CHECK_THROWS(gr.add_edge(1, 2, -3));
  CHECK_THROWS(gr.add_edge(11, 2, 3));
  CHECK_THROWS(gr.add_edge(1, 12, 3));

  CHECK_THROWS(gr.add_edge(1, 2, -3));

  CHECK_THROWS(gr.add_edge(1, 1, 3));

  CHECK_NOTHROW(gr.add_edge(1, 2, 3));
  CHECK_NOTHROW(gr.add_edge(5, 2, 3));
  CHECK_NOTHROW(gr.add_edge(9, 2, 3));

  vector<vector<int>> graph = gr.get_graph(); 

  CHECK(graph[1][2] == 3);
  CHECK(graph[5][2] == 3);
  CHECK(graph[9][2] == 3);  
}

TEST_CASE("Delete vertex")
{
  Graph gr = Graph(10);  

  CHECK_THROWS(gr.delete_vertex(-2));
  CHECK_THROWS(gr.delete_vertex(12));
  
  gr.add_edge(2, 5, 210);
  
  CHECK_NOTHROW(gr.delete_vertex(1));

  vector<vector<int>> graph = gr.get_graph(); 

  CHECK(graph[1][4] == 210);
}

TEST_CASE("Delete edge")
{
  Graph gr = Graph(10);  

  CHECK_THROWS(gr.delete_edge(-1, 2));
  CHECK_THROWS(gr.delete_edge(1, -2));
  CHECK_THROWS(gr.delete_edge(11, 2));
  CHECK_THROWS(gr.delete_edge(1, 12));

  CHECK_THROWS(gr.delete_edge(1, 2));

  CHECK_NOTHROW(gr.delete_edge(1, 1));
  
  gr.add_edge(2, 5, 210);

  CHECK_NOTHROW(gr.delete_edge(2, 5));

  vector<vector<int>> graph = gr.get_graph(); 

  CHECK(graph[2][5] == INF);
  CHECK(graph[5][2] == INF);
}

TEST_CASE("Degree of vertex")
{
  Graph gr = Graph(5);  

  gr.add_edge(1, 0, 2);
  gr.add_edge(2, 0, 1);
  gr.add_edge(2, 1, 3);
  gr.add_edge(3, 0, 2);
  gr.add_edge(3, 2, 4);
  gr.add_edge(4, 0, 10);

  CHECK(gr.get_degree_of_vertex(0) == 4);
  CHECK(gr.get_degree_of_vertex(1) == 2);
  CHECK(gr.get_degree_of_vertex(2) == 3);
  CHECK(gr.get_degree_of_vertex(3) == 2);
  CHECK(gr.get_degree_of_vertex(4) == 1);
}

TEST_CASE("Kruskal_algorithm - 1")
{
  Graph gr = Graph(5);  

  gr.add_edge(1, 0, 2);
  gr.add_edge(2, 0, 1);//will be in the carcass
  gr.add_edge(3, 0, 4);
  gr.add_edge(4, 0, 5);
  gr.add_edge(2, 1, 1);//will be in the carcass
  gr.add_edge(3, 1, 6);
  gr.add_edge(4, 1, 1);///will be in the carcass
  gr.add_edge(3, 2, 2);//will be in the carcass
  gr.add_edge(4, 2, 2);
  gr.add_edge(4, 3, 3);

  gr.Prim_algorithm();

  vector<vector<int>> carcass = gr.get_carcass();

  CHECK(carcass[0][2] == 1);
  CHECK(carcass[1][2] == 1);
  CHECK(carcass[1][4] == 1);
  CHECK(carcass[2][3] == 2);
  CHECK(carcass[2][0] == 1);
  CHECK(carcass[2][1] == 1);
  CHECK(carcass[4][1] == 1);
  CHECK(carcass[3][2] == 2); 

  CHECK(gr.get_weight_of_carcass() == 5);
}

TEST_CASE("Kruskal_algorithm - 2")
{
  Graph gr = Graph(5);  

  gr.add_edge(1, 0, 2);//will be in the carcass
  gr.add_edge(2, 0, 1);//will be in the carcass
  gr.add_edge(2, 1, 3);
  gr.add_edge(3, 0, 2);//will be in the carcass
  gr.add_edge(4, 0, 10);//will be in the carcass

  gr.Prim_algorithm();

  vector<vector<int>> carcass = gr.get_carcass();

  CHECK(carcass[0][1] == 2);
  CHECK(carcass[0][2] == 1);
  CHECK(carcass[0][3] == 2);
  CHECK(carcass[0][4] == 10);
  CHECK(carcass[1][0] == 2);
  CHECK(carcass[2][0] == 1);
  CHECK(carcass[3][0] == 2);
  CHECK(carcass[4][0] == 10); 

  CHECK(gr.get_weight_of_carcass() == 15);
}
