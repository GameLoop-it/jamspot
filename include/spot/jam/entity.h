#pragma once

#include <spot/handle.h>

namespace spot::gfx
{
class Input;
class Node;
}

namespace spot::jam
{

class Entity
{
  public:
	Handle<gfx::Node> node;
};


} // namespace spot::jam
