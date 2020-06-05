# Library
set( LIB_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/game.cc
	${CMAKE_CURRENT_SOURCE_DIR}/tile.cc
	${CMAKE_CURRENT_SOURCE_DIR}/tileset.cc
	${CMAKE_CURRENT_SOURCE_DIR}/player.cc
	${CMAKE_CURRENT_SOURCE_DIR}/map.cc
	${CMAKE_CURRENT_SOURCE_DIR}/serialization/serialization.cc
	${CMAKE_CURRENT_SOURCE_DIR}/serialization/entity.cc
	${CMAKE_CURRENT_SOURCE_DIR}/serialization/tile.cc
	${CMAKE_CURRENT_SOURCE_DIR}/serialization/node.cc
	${CMAKE_CURRENT_SOURCE_DIR}/serialization/map.cc
	${CMAKE_CURRENT_SOURCE_DIR}/editor/tileset.cc
)

add_library( ${CMAKE_PROJECT_NAME} ${LIB_SOURCES} )
target_include_directories( ${CMAKE_PROJECT_NAME}
	PUBLIC ${CMAKE_SOURCE_DIR}/include )
target_link_libraries( ${CMAKE_PROJECT_NAME}
	project-options
	gfxspot )

# Executable
set( SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
)

add_executable( game-${CMAKE_PROJECT_NAME} ${SOURCES} )
target_link_libraries( game-${CMAKE_PROJECT_NAME}
	${CMAKE_PROJECT_NAME} )
