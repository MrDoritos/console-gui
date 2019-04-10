@echo off
set "sourcePath=source\"
set "headerPath=headers\"
set "sources=%sourcePath%gameEngine.cpp %sourcePath%imath.cpp %sourcePath%lodepng.cpp %sourcePath%pixel.cpp %sourcePath%png.cpp %sourcePath%rigidbody.cpp %sourcePath%rigidbox.cpp %sourcePath%eventHandler.cpp %sourcePath%screenManager.cpp %sourcePath%screen.cpp"
set "includes=-I%headerPath%"
set "arg=-DGCC -o a.exe -std=c++11 -w"

set "ret=0"

echo Split box.h into box.h and box.cpp
echo Split boxsize.h into boxsize.h and boxsize.cpp
echo Split image.h into image.h and image.cpp

g++ %sources% %includes% %arg% %*
set "ret=%errorlevel%"


@echo on
if "%ret%" NEQ "0" (
pause
)
@echo off
Exit /b %ret%
