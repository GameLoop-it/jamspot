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
	void update( const float delta, const gfx::Input& input );

	float speed = 32.0f;

	Handle<gfx::Node> node;
};


} // namespace spot::jam
