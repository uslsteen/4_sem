#ifndef CIRC_CIRCUITS_HH
#define CIRC_CIRCUITS_HH

#include "../matrix/matrix.hh"
#include <cstdlib>
#include <fstream>
#include <stack>
#include <unordered_set>

// TODO: найти где будут Edge

namespace CTS
{
struct Edge final // rtor, junc1, junc2, voltage
{
  size_t junc1, junc2;

  int weight;

  Edge(size_t j1, size_t j2, int w) : junc1(j1), junc2(j2), weight(w)
  {
  }

  double get_cur() const
  {
    //return MX::is_zero(cur) ? 0.0 : cur;
  }
};

std::ostream &operator<<(std::ostream &ost, const Edge &edge);

}
#endif // CIRC_CIRCUITS_HH
