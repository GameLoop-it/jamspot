#include "spot/jam/editor/editor.h"

#include <imgui.h>
#include <spot/gfx/node.h>

#include "spot/jam/map.h"


namespace spot::jam
{


void Editor::draw( Entity& entity, Map& map )
{
	ImGui::Begin( "Entity" );

	gfx::Node& node = *entity.node;

	node.name.resize( 16 );
	ImGui::InputText( "", node.name.data(), node.name.size() - 1 );

	if ( ImGui::Button( "Remove" ) )
	{
		entity.node->remove_from_parent();
		entity.node->invalidate();
		entity.handle.invalidate();
	}

	ImGui::End();
}


void Editor::draw( Map& map )
{
	ImGui::Begin( "Map" );

	if ( ImGui::Button( "Save" ) )
	{
		map.save( "res/data/map.json" );
	}

	if ( map.entities->empty() )
	{
		selected_entity = {};
		ImGui::End();
		return;
	}

	Handle<Entity> current_selected;

	for ( auto& entity : *map.entities )
	{
		// Skip invalid entities
		if ( !entity.handle )
		{
			continue;
		}

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

		if ( selected_entity == entity.handle )
		{
			current_selected = entity.handle;
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		gfx::Node& node = *entity.node;
		auto open = ImGui::TreeNodeEx( node.name.c_str(), flags );

		if ( ImGui::IsItemClicked() )
		{
			selected_entity = current_selected = entity.handle;
		}

		if ( open )
		{
			ImGui::TreePop();
		}
	}

	if ( current_selected )
	{
		draw( *current_selected, map );
	}

	ImGui::End();
}


} // namespace spot::jam
