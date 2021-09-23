set PATH=C:\Qt\Tools\CMake_64\bin;%PATH%
set PATH=C:\Qt\Tools\Ninja;%PATH%
set PATH=C:\Qt\Tools\mingw810_64\bin;%PATH%

cmake^
 -G "Ninja"^
 -D CMAKE_PREFIX_PATH="C:\Qt\6.1.3\mingw81_64"^
 ..
	
cmake --build .
