GPP=g++
CFLAGS=-c

prog:	 Main.o Matrix.o Image.o
	$(GPP) Main.o Matrix.o Image.o -o prog

Main.o:	Main.cpp Matrix.h Image.h
	$(GPP) $(CFLAGS) Main.cpp

Matrix.o:	Matrix.cpp Matrix.h
	$(GPP) $(CFLAGS) Matrix.cpp

Image.o:	Image.cpp Image.h
	$(GPP) $(CFLAGS) Image.cpp

clean:
	rm *.o prog
