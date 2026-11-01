cmake_minimum_required(VERSION 3.24)

project(VideoEditor)

#TODO: if Visual Studio do this, else don't worry about it
set(CMAKE_SUPPRESS_REGENERATION true)

add_executable(Editor)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Editor)

#TODO: later on turn core into a library
add_executable(Core)

target_compile_features(Editor PUBLIC cxx_std_17)

target_compile_features(Core PUBLIC cxx_std_17)

target_sources(Editor PUBLIC
	Editor/src/Main.cpp
	Editor/src/Renderer/Application.cpp
	Editor/src/Renderer/Window.cpp
	Editor/src/Renderer/imgui.cpp
	Editor/src/Renderer/imgui_demo.cpp
	Editor/src/Renderer/imgui_tables.cpp
	Editor/src/Renderer/imgui_widgets.cpp
	Editor/src/Renderer/imgui_draw.cpp
	Editor/src/Renderer/imgui_impl_vulkan.cpp
	Editor/src/Renderer/imgui_impl_glfw.cpp	
	Editor/src/Renderer/Window.h
	Editor/src/Renderer/Application.h
	Editor/src/Renderer/Vertex.h
)

target_include_directories(Editor PRIVATE
	C:/VulkanSDK/1.4.357.0/Include
	C:/Libraries/glfw-3.5.1.bin.WIN64/include
	C:/Libraries/glm
	C:/Libraries/tinyObjLoader
	C:/Libraries/stb
	Thirdparty/imgui
)

target_link_directories(Editor PUBLIC
	C:/VulkanSDK/1.4.357.0/Lib
	C:/Libraries/glfw-3.5.1.bin.WIN64/lib-vc2026
)

target_link_libraries(Editor glfw3 vulkan-1)

target_sources(Core PUBLIC
	Core/src/Main.cpp
	Core/src/ITrack.cpp
	Core/src/ITrack.h
	Core/src/Project.h
	Core/src/NotImplemented.h
)

target_include_directories(Core PRIVATE
	C:/Libraries/ffmpeg-8.0.1-full_build-shared/include
)

target_link_directories(Core PUBLIC
	C:/Libraries/ffmpeg-8.0.1-full_build-shared/lib/
)

target_link_libraries(Core avcodec avutil avformat swscale)
