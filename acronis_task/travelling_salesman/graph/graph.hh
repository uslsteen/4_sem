#ifndef GRAPH_H__
#define GRAPH_H__

#include "../matrix/matrix.hh"
#include <cstdlib>
#include <fstream>
#include <stack>
#include <unordered_set>

// TODO: найти где будут Edge

namespace detail
{
struct Edge final // rtor, junc1, junc2, voltage
{
  size_t junc1, junc2;

  int weight;

  Edge(size_t j1, size_t j2, int w) : junc1(j1), junc2(j2), weight(w)
  {
  }

  double get_weight() const
  {
      return weight;
  }
};

std::ostream &operator<<(std::ostream &ost, const Edge &edge);

}
#endif // GRAPH_H__
