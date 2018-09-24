cmake_minimum_required(VERSION 3.10)
project(NodeRenderer_GL CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

find_library(ASSETLIB assetlib PATHS ../..)
find_path(ASSETLIB_INCLUDE_DIR NAMES 
image.c image.h model.h obj_utils.c obj_utils.h png_utils.c png_utils.h
PATH_SUFFIXES assetlib/)

find_library(NODERENDERER NodeRenderer PATHS ../..)
find_path(NODERENDERER_INCLUDE_DIR NAMES
Buffer.cpp Buffer.hpp CommonTypes.hpp Model.cpp Model.hpp Renderer.cpp Renderer.hpp
Shader.cpp Shader.hpp ShaderConstantData.cpp ShaderConstantData.hpp System.hpp
Texture.cpp Texture.hpp VertexDataLayout.cpp VertexDataLayout.hpp PATH_SUFFIXES NodeRenderer/)


if(NOT ASSETLIB)
	message(FATAL_ERROR "Could not locate assetlib")
endif()
if (NOT ASSETLIB_INCLUDE_DIR)
	message(FATAL_ERROR "Could not locate assetlib include directory")
endif()

if(NOT NODERENDERER)
	message(FATAL_ERROR "Could not locate NodeRenderer")
endif()
if (NOT NODERENDERER_INCLUDE_DIR)
	message(FATAL_ERROR "Could not locate NodeRenderer include directory")
endif()

include_directories(${ASSETLIB_INCLUDE_DIR})
include_directories(${NODERENDERER_INCLUDE_DIR})

set(SOURCE_FILES
	Buffer_GL.cpp
	Buffer_GL.hpp
	Renderer_GL.cpp
	Renderer_GL.hpp
	Shader_GL.cpp
	Shader_GL.hpp
	System_GL.cpp
	Texture_GL.cpp
	Texture_GL.hpp)

add_library(NodeRenderer_GL STATIC ${SOURCE_FILES})
target_link_libraries(NodeRenderer_GL ${NODERENDERER})
target_link_libraries(NodeRenderer_GL ${ASSETLIB})
set_target_properties(NodeRenderer_GL PROPERTIES PREFIX "")

