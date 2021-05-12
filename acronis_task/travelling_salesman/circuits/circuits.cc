#include "circuits.hh"

namespace CTS
{

std::ostream &operator<<(std::ostream &ost, const Edge &edge)
{
  //double real_cur = MX::is_zero(edge.cur) ? 0.0 : edge.cur;

  ost << edge.junc1 << " -- " << edge.junc2 << ": " << edge.weight << " A" << std::endl;

  return ost;
}

}
