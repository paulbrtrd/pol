
all: end


MeshReductor: main.o stl_data.o triangle.o vertex.o tools.o opengl_display.o
	@if [ -e MeshReductor ];  then rm MeshReductor; fi
	@g++ -o MeshReductor main.o stl_data.o triangle.o vertex.o tools.o opengl_display.o  -lglut -lGLU -lGL
	@echo "MeshReductor generated"

main.o: main.cpp
	@g++ -c main.cpp
	@echo "main.o generated"

stl_data.o: Structures/stl_data.cpp Structures/stl_data.h Structures/triangle.h Structures/vertex.h
	@g++ -c Structures/stl_data.cpp
	@echo "parse_stl.o generated"

triangle.o: Structures/triangle.cpp Structures/triangle.h Structures/vertex.h Structures/stl_data.h
	@g++ -c Structures/triangle.cpp
	@echo "triangle.o generated"

vertex.o: Structures/vertex.cpp Structures/vertex.h Structures/stl_data.h
	@g++ -c Structures/vertex.cpp
	@echo "vertex.o generated"

tools.o: Structures/tools.cpp Structures/tools.h Structures/vertex.h
	@g++ -c Structures/tools.cpp
	@echo "tools.o generated"

opengl_display.o: opengl_display.cpp opengl_display.h
	@g++ -c opengl_display.cpp
	@echo "opengl_display.o generated"

end: MeshReductor
	@if [ -e Build ];  then rm -r Build; fi
	@mkdir Build
	@mv *.o Build/
	@echo "Files moved to Build/"
