CXX = g++
CPPFLAGS = -Wall -pedantic-errors -O3 #-pg# -ggdb 
LIBRARIES_grapher = $(addprefix -l,GL GLU glut)
LIBRARIES_rbf = #-pg

object_rbf = $(addprefix obj/,main.o neurona.o neurona_rbf.o rbf.o util.o)
objects = $(object_rbf)
binaries = $(addprefix bin/,rbf.bin) 

project: $(binaries)

all: $(objects)

bin/rbf.bin: $(object_rbf)
	$(CXX) $(LIBRARIES_rbf) $(object_rbf) -o $@

obj/main.o: $(addprefix header/,rbf.h neurona.h neurona_rbf.h)
obj/neurona.o: $(addprefix header/,util.h neurona.h)
obj/neurona_rbf.o: $(addprefix header/,util.h neurona_rbf.h)
obj/rbf.o: $(addprefix header/,rbf.h neurona.h neurona_rbf.h util.h)
obj/util.o: $(addprefix header/,util.h)

obj/%.o : src/%.cpp
	$(CXX) $< -c $(CPPFLAGS) -Iheader -o $@

$(objects): | obj

$(binaries): | bin

obj:
	mkdir $@

bin:
	mkdir $@


.PHONY: clean 

clean:
	-rm $(objects) $(binaries)
	-rmdir bin obj
