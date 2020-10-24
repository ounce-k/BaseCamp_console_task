# Specify compiler
CC=cl.exe
 
# Specify linker
LINK=link.exe
LIBS = user32.lib
.PHONY : all
all : Server
 
# Link the object files into a binary
Server : main.o functions.o
    $(LINK) /OUT:Server.exe main.o functions.o  $(LIBS)
 
# Compile the source files into object files
main.o : main.cpp
    $(CC) /c /EHsc main.cpp /Fomain.o

functions.o : functions.cpp
    $(CC) /c /EHsc functions.cpp /Fofunctions.o	
 
# Clean target

clean :
    del main.o functions.o Server.exe