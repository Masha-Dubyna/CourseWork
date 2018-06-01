#include <vector>
using namespace std;

class Graph
{
  private:
    vector<vector<int>> adjacency_matrix;
    vector<vector<int>> carcass;
    int size;

    void fill_carcass(int vertex1, int vertex2);

  public:
    Graph(int amount_of_vertexes);
    ~Graph();

    void add_vertex();
    void add_edge(int vertex1, int vertex2, int weight);
    void delete_vertex(int vertex);
    void delete_edge(int vertex1, int vertex2);
    void Prim_algorithm();

    void print_graph();
    void print_carcass();

    int get_weight_of_carcass();
    int get_degree_of_vertex(int vertex);

    int get_size()
    {
      return size;
    }

    vector<vector<int>> get_graph()
    {
      return adjacency_matrix;
    }

    vector<vector<int>> get_carcass()
    {
      return carcass;
    }
};
