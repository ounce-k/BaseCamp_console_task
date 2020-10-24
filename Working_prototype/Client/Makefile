# Specify compiler
CC=cl.exe
 
# Specify linker
LINK=link.exe
LIBS = user32.lib
.PHONY : all
all : Client
 
# Link the object files into a binary
Client : main.o functions.o
    $(LINK) /OUT:Client.exe main.o functions.o  $(LIBS)
 
# Compile the source files into object files
main.o : main.cpp
    $(CC) /c main.cpp /Fomain.o

functions.o : functions.cpp
    $(CC) /c functions.cpp /Fofunctions.o	
 
# Clean target

clean :
    del main.o functions.o Client.exe