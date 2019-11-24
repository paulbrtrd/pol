DEST=Build

all: end

create_dir: 
	@if [ ! -e Build ];  then mkdir Build && echo "Build folder created"; fi

myApp: main.o parse_stl.o tools.o opengl_display.o ClassifyVertex.o
	@if [ -e myApp ];  then rm myApp; fi
	@g++ -o myApp main.o parse_stl.o tools.o opengl_display.o ClassifyVertex.o -lglut -lGLU -lGL
	@echo "myApp generated"

main.o: main.cpp
	@g++ -c main.cpp
	@echo "main.o generated"

parse_stl.o: parse_stl.cpp parse_stl.h
	@g++ -c parse_stl.cpp
	@echo "parse_stl.o generated"

tools.o: tools.cpp tools.h
	@g++ -c tools.cpp
	@echo "tools.o generated"

ClassifyVertex.o: ClassifyVertex.cpp ClassifyVertex.h
	@g++ -c ClassifyVertex.cpp
	@echo "ClassifyVertex.o generated"

opengl_display.o: opengl_display.cpp opengl_display.h
	@g++ -c opengl_display.cpp
	@echo "opengl_display.o generated"

end: myApp create_dir
	@rm Build/*
	@mv *.o Build/
	@echo "Files moved to Build/"
