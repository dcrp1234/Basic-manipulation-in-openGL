all: frustum

frustum: frustum.o
		gcc frustum.o -o frustum -lGL -lGLU -lglut -lm
      
main.o: frustum.cc
		gcc -c  frustum.cc -lGL -lGLU -lglut -lm
		
clean:
		rm -rf *o frustum