cmake_minimum_required(VERSION 3.24)

project(Editor)

#TODO: if Visual Studio do this, else don't worry about it
set(CMAKE_SUPPRESS_REGENERATION true)

add_executable(Editor)

target_compile_features(Editor PUBLIC cxx_std_17)

target_sources(Editor PUBLIC 
	Renderer/src/Main.cpp
	Renderer/src/Application.cpp
	Renderer/src/Window.cpp
	Renderer/src/imgui.cpp
	Renderer/src/imgui_demo.cpp
	Renderer/src/imgui_tables.cpp
	Renderer/src/imgui_widgets.cpp
	Renderer/src/imgui_draw.cpp
	Renderer/src/imgui_impl_vulkan.cpp
	Renderer/src/imgui_impl_glfw.cpp	
	Renderer/src/Window.h
	Renderer/src/Application.h
)

target_include_directories(Editor 
	PRIVATE	
	C:/VulkanSDK/1.3.268.0/Include
	C:/Libraries/glfw-3.3.9.bin.WIN64/include
	C:/Libraries/glm
	C:/Libraries/tinyObjLoader
	C:/Libraries/stb
	Thirdparty/imgui
)

target_link_directories(Editor PUBLIC
	C:/VulkanSDK/1.3.268.0/Lib
	C:/Libraries/glfw-3.3.9.bin.WIN64/lib-vc2022
)

target_link_libraries(Editor glfw3 vulkan-1)
