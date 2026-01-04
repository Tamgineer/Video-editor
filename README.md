# Video editor
## Goal
A video editor that aims to be relatively lightweight.

**Note:** This project is subject to change drastically as of now whilst I take time in fully realising the project.

## How to build (if you want to build it for some reason)
### VS2022
1. git clone the repository onto the folder
2. Open `CMakeList.txt` and make sure that the following is edited for the project to build properly
  a. line 29, to point to the Vulkan include folder
  b. line 30, to point to the GLFW include folder
  c. line 31, to point to the glm root folder
  d. line 32, to point to the tinyObjLoader root folder
  e. line 33, to point to the stb root folder
4. open terminal and run `cmake -B build`
5. open shaders and edit `compile.bat` to make sure the batch file points to the `glslc.exe` compiler before running the batch file.
6. open the build folder and open `Editor.sln`.
7. Delete `ALL_BUILD` and press `CTRL+B` to build the project.
8. Finally run the build to check if it works.

## Roadmap
 - [x] Set up project
 - [x] Create CMakeList
 - [ ] Incorporate FFMPEG into project
 - [ ] Demonstrate videos being played.
 - [ ] Design a low fidelity page for the software.

## Checklist
Here are the things I need the video editor to be able to do
 - [ ] Take in videos
 - [ ] Output a video
 - [ ] Play a video ontop of a video
 - [ ] Play audio
 - [ ] Export a video
 - [ ] Render text
 - [ ] Cut a video
 - [ ] Change the speed
 - [ ] Reposition the video
 - [ ] Add audio
 - [ ] Add plugins
 - [ ] Preview
 - [ ] Auto transcript
