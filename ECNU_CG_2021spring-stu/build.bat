@echo off
mkdir vs2015
cd vs2015
.\..\cmake\bin\cmake.exe .. -G "Visual Studio 14 2015"
cd ..

mkdir vs2010
cd vs2010
.\..\cmake\bin\cmake.exe .. -G "Visual Studio 10 2010"
cd ..
