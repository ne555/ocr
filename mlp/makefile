CXX = g++
CPPFLAGS = -Wall -pedantic-errors -O3
LIBRARIES_mlp = 
objdir = obj
headerdir = header
bindir = bin
bin = $(bindir)/mlp.bin

obj_mlp = mlp.o neurona.o simulator.o capa.o network.o

object_mlp = $(addprefix $(objdir)/,$(obj_mlp))

objects = $(object_mlp)

all: $(bin)


bin/mlp.bin: $(object_mlp)
	$(CXX) $(LIBRARIES_mlp) $(object_mlp) -o $@

$(objdir)/capa.o: $(addprefix $(headerdir)/,neurona.h math_vector.h capa.h util.h)
$(objdir)/mlp.o: $(addprefix $(headerdir)/,simulator.h capa.h math_vector.h neurona.h util.h)
$(objdir)/input.o: $(addprefix $(headerdir)/,util.h math_vector.h)
$(objdir)/neurona.o: $(addprefix $(headerdir)/,neurona.h math_vector.h util.h)
$(objdir)/network.o: $(addprefix $(headerdir)/,network.h capa.h math_vector.h neurona.h util.h)
$(objdir)/simulator.o: $(addprefix $(headerdir)/,simulator.h network.h capa.h math_vector.h neurona.h util.h)

$(objdir)/%.o : src/%.cpp
	$(CXX) $< -c $(CPPFLAGS) -I$(headerdir) -o $@

$(objects): | $(objdir)

$(bin): | $(bindir)

$(objdir):
	mkdir $(objdir)

$(bindir):
	mkdir $(bindir)


.PHONY: clean

clean:
	-rm $(objects) $(bin)
	-rmdir $(bindir) $(objdir)

