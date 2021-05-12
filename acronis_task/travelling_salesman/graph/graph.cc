#include "graph.hh"

namespace detail
{

std::ostream &operator<<(std::ostream &ost, const Edge &edge)
{
  ost << edge.junc1 << " -- " << edge.junc2 << ": " << edge.weight << " A" << std::endl;

  return ost;
}

}
