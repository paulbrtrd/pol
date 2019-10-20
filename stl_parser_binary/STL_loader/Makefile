myApp: main.o parse_stl.o tools.o opengl_display.o
	g++ -o myApp main.o parse_stl.o tools.o opengl_display.o -lglut -lGLU -lGL

main.o: main.cpp
	g++ -c main.cpp 

parse_stl.o: parse_stl.cpp parse_stl.h 
	g++ -c parse_stl.cpp 

tools.o: tools.cpp tools.h
	g++ -c tools.cpp

opengl_display.o: opengl_display.cpp opengl_display.h
	g++ -c opengl_display.cpp
