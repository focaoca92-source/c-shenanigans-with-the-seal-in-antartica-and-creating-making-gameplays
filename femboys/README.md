compile:

CMake (needs Visual Studio):
```
Remove-Item -Recurse -Force build
cmake -B build .
cmake --build build --config Release
.\build\Release\Femboys.exe
```

or:
```
g++.exe -std=c++23 -c src/main.cc -I"C:\SFML\include" -o bin/main.o -lstdc++exp
g++.exe -std=c++23 bin/main.o -o bin/app.exe -L"C:\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system -lstdc++exp
.\bin\app.exe
```