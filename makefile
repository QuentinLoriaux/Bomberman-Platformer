CXX=clang++

MFLAGS = -std=c++20 -stdlib=libc++ -fmodules -fbuiltin-module-map # for modules
CFLAGS =  -Wall 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

M = src/model
V = src/view
C = src/controller

MODULES = window

all : Bomberman_Plat

Bomberman_Plat : build/main.o  $(addsuffix .o, $(addprefix build/,$(MODULES))) 
# Linkage
	$(CXX) $(MFLAGS) -fprebuilt-module-path=build $^ -o $@.x $(LDFLAGS)  


main.o : $(M)/main.cpp
	$(CXX) $(MFLAGS) $(CFLAGS) -c $< -o $@ -I/src

build/%.o : $(M)/%.cppm
# précompilation des modules
	$(CXX) $(MFLAGS) --precompile $^ -o $(patsubst $(M)/%.cppm, build/%.pcm, $<)
# génération des fichiers objets
	$(CXX) $(MFLAGS) $(CFLAGS) -c $(patsubst $(M)/%.cppm, build/%.pcm, $<) -o $@

build/%.o : $(V)/%.cppm
	$(CXX) $(MFLAGS) --precompile $^ -o $(patsubst $(V)/%.cppm, build/%.pcm, $<)
	$(CXX) $(MFLAGS) $(CFLAGS) -c $(patsubst $(V)/%.cppm, build/%.pcm, $<) -o $@

build/%.o : $(C)/%.cppm
	$(CXX) $(MFLAGS) --precompile $^ -o $(patsubst $(C)/%.cppm, build/%.pcm, $<)
	$(CXX) $(MFLAGS) $(CFLAGS) -c $(patsubst $(C)/%.cppm, build/%.pcm, $<) -o $@


run:
	./Bomberman_Plat.x