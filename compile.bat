@echo off
set "sourcePath=source\"
set "headerPath=headers\"
set "sources=%sourcePath%gameEngine.cpp %sourcePath%imath.cpp %sourcePath%lodepng.cpp %sourcePath%pixel.cpp %sourcePath%png.cpp %sourcePath%rigidbody.cpp %sourcePath%rigidbox.cpp"
set "includes=-I%headerPath%"
set "arg=-DGCC -o a.exe"

echo Split box.h into box.h and box.cpp
echo Split boxsize.h into boxsize.h and boxsize.cpp
echo Split image.h into image.h and image.cpp

@echo on
%userprofile%\Downloads\pocketcpp-0.7\pocketcpp\MinGW\bin\g++ %includes% %sources% %arg% main.cpp
if "%errorlevel%" NEQ "0" (
pause
)
@echo off
