#include "graph.h"
#include <iostream>
#include <stdexcept>
using namespace std;

const int INF = 1000000000;//"infinfty"

Graph::Graph(int amount_of_vertexes)
{
  if (amount_of_vertexes < 1)
  {
    throw invalid_argument("Unable to create graph with less than 1 vertex");
  }
  
  size = amount_of_vertexes;

  adjacency_matrix.resize(size);
  
  for (int count = 0; count < size; count++)
  {
    adjacency_matrix[count].resize(size);
  }  

  carcass.resize(size);

  for (int count = 0; count < size; count++)
  {
    carcass[count].resize(size);
  }

  for (int count1 = 0; count1 < size; count1++)
  {
    for(int count2 = 0; count2 < size; count2++)
    {
      adjacency_matrix[count1][count2] = INF;
    }
  }
};

Graph::~Graph()
{
  for (int count = 0; count < size; count++)
  {
    adjacency_matrix.erase(adjacency_matrix.begin());
  }

  size = 0;
}

void Graph::add_vertex()
{
  size++;

  adjacency_matrix.resize(size);

  for (int count = 0; count < size; count++)
  {
    adjacency_matrix[count].resize(size);
  }

  for (int count = 0; count < size; count++)
  {
    adjacency_matrix[count][size - 1] = INF;
    adjacency_matrix[size - 1][count] = INF;
  }
}

void Graph::add_edge(int vertex1, int vertex2, int weight)
{
  if (vertex1 < 0 || vertex2 < 0 || vertex1 >= size || vertex2 >= size)
  {
    throw invalid_argument("Non-existing vertex");
  }

  if (weight < 0)
  {
    throw invalid_argument("Non-existing weight of edge");
  }
  
    if (vertex1 == vertex2)
  {
    throw invalid_argument("Creating an edge between the same vertex");
  }

  adjacency_matrix[vertex1][vertex2] = weight;
  adjacency_matrix[vertex2][vertex1] = weight;
}

void Graph::delete_vertex(int vertex)
{
  if (vertex < 0 || vertex >= size)
  {
    throw invalid_argument("Non-xisting vertex");
  }

  adjacency_matrix.erase(adjacency_matrix.begin() + vertex - 1);

  for (int count = 0; count < (size - 1); count++)
  {
    adjacency_matrix[count].erase(adjacency_matrix[count].begin() + vertex - 1);
  }

  size--;
}

void Graph::delete_edge(int vertex1, int vertex2)
{
    if (vertex1 < 0 || vertex2 < 0 || vertex1 >= size || vertex2 >= size)
  {
    throw invalid_argument("Non-existing vertex");
  }

  if (adjacency_matrix[vertex2][vertex1] == INF && vertex1 != vertex2)
  {
    throw invalid_argument("Non-existing edge");
  }

  adjacency_matrix[vertex1][vertex2] = INF;
  adjacency_matrix[vertex2][vertex1] = INF;
}

void Graph::print_graph()
{
  for (int count1 = 0; count1 < 5; count1++)
  {
    for (int count2 = 0; count2 < 5; count2++)
    {
      if (adjacency_matrix[count2][count1] == INF)
      {
        cout << "0" << "  ";
      }
      else
      {
        cout << adjacency_matrix[count2][count1] << "  ";
      }
    }

    cout << "\n";
  }
}

void Graph::print_carcass()
{
  for (int count1 = 0; count1 < 5; count1++)
  {
    for (int count2 = 0; count2 < 5; count2++)
    {
      cout << carcass[count2][count1] << "  ";
    }

    cout << "\n";
  }
}

void Graph::fill_carcass(int vertex1, int vertex2)
{
  carcass[vertex1][vertex2] = adjacency_matrix[vertex1][vertex2];
  carcass[vertex2][vertex1] = adjacency_matrix[vertex1][vertex2];
}

void Graph::Prim_algorithm()
{
  vector<bool> used(size);
  vector<int> min_elements(size, INF), end_element(size, -1);

  min_elements[0] = 0;

  for (int count1 = 0; count1 < size; ++count1)
  {
    int vertex = -1;
    
    for (int count2 = 0; count2 < size; ++count2)
    {
      if (!used[count2] && (vertex == -1 || min_elements[count2] < min_elements[vertex]))
      {
        vertex = count2;
      }
    }

    if (min_elements[vertex] == INF)
    {
      throw invalid_argument("Minimum spanning tree does not exist");
    }

    used[vertex] = true;

    if (end_element[vertex] != -1)
    {
      fill_carcass(vertex, end_element[vertex]);
    }

    for (int count3 = 0; count3 < size; ++count3)
    {
      if (adjacency_matrix[vertex][count3] < min_elements[count3])
      {
        min_elements[count3] = adjacency_matrix[vertex][count3];
        end_element[count3] = vertex;
      }
    }
  }  
}

int Graph::get_weight_of_carcass()
{
  int weight = 0;

  for (int count1 = 0; count1 < size; count1++)
  {
    for (int count2 = 0; count2 < size; count2++)
    {
      weight += carcass[count1][count2]; 
    }
  }

  weight /= 2;

  return weight;
}

int Graph::get_degree_of_vertex(int vertex)
{
  int degree = 0;
  
  for (int count = 0; count < size; count++)
  {
    if (adjacency_matrix[vertex][count] != INF)
    {
      degree++; 
    }
  }

  return degree;
}
