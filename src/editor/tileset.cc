#include "spot/jam/editor/editor.h"

#include <imgui.h>

#include "spot/jam/tileset.h"
#include "spot/jam/tile.h"

namespace spot::jam
{


void Editor::draw( Tileset& tileset )
{
	ImGui::Begin( "Tileset" );

	for ( auto& [tile,_] : tileset.tiles )
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
		flags |= ( selected == &tile ) ? ImGuiTreeNodeFlags_Selected : 0;
		bool open = ImGui::TreeNodeEx( tile.name.c_str(), flags );

		if ( ImGui::IsItemClicked() )
		{
			selected = &tile;
		}

		if ( open )
		{
			ImGui::TreePop();
		}
	}


	ImGui::End();
}

} // namespace spot::jam