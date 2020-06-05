#include "spot/jam/editor/editor.h"

#include <imgui.h>

#include "spot/jam/tileset.h"
#include "spot/jam/tile.h"

namespace spot::jam
{


void Editor::draw( Tile& tile )
{
	ImGui::Begin( "Tile" );
	tile.name.resize( 16 );
	ImGui::Text( "[%u,%u]", tile.id.x, tile.id.y );
	ImGui::SameLine();
	ImGui::InputText( "", tile.name.data(), tile.name.size() - 1 );
	ImGui::Checkbox( "non passable", &tile.non_passable );
	ImGui::Checkbox( "movable", &tile.movable );
	ImGui::End();
}


void Editor::draw( Tileset& tileset, gfx::Model& model )
{
	ImGui::Begin( "Tileset" );

	int x = new_tile.id.x;
	ImGui::InputInt( "x", &x );
	new_tile.id.x = uint32_t( x );

	int y = new_tile.id.y;
	ImGui::InputInt( "y", &y );
	new_tile.id.y = uint32_t( y );

	ImGui::InputText( "", new_tile.name.data(), new_tile.name.size() - 1 );

	if ( ImGui::Button( "new" ) )
	{
		tileset.emplace( new_tile, model );
	}

	Tile* current_selected = nullptr;

	for ( auto& [id,pair] : tileset.tiles )
	{
		Tile& tile = pair.first;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

		if ( selected == &tile )
		{
			current_selected = &tile;
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		bool open = ImGui::TreeNodeEx( tile.name.c_str(), flags );

		if ( ImGui::IsItemClicked() )
		{
			selected = current_selected = &tile;
		}

		if ( open )
		{
			ImGui::TreePop();
		}
	}

	if ( current_selected )
	{
		draw( *current_selected );
	}

	ImGui::End();
}

} // namespace spot::jam