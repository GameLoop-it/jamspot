#include "spot/jam/editor/editor.h"

#include <imgui.h>

#include "spot/jam/tileset.h"
#include "spot/jam/tile.h"

namespace spot::jam
{


void Editor::draw( Tileset& tileset )
{
	ImGui::Begin( "Tileset" );

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


	ImGui::End();
}

} // namespace spot::jam