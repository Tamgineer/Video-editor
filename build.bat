if not exist build mkdir build
cd build
cmake -S ../ -B . -G "Visual Studio 18 2026"
cd ..
