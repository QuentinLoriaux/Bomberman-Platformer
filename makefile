CXX=clang++

LIBSFML = /home/quentin/_dev/clones/SFML_build/lib

MFLAGS = -std=c++20 -fmodules -fbuiltin-module-map -fprebuilt-module-path=build # for modules
CFLAGS =  -Wall -Wextra -I include
LDFLAGS = -Wl,-rpath=$(LIBSFML) -L $(LIBSFML) -l:libsfml-system.so.2.6.0 -l:libsfml-window.so.2.6.0 -l:libsfml-graphics.so.2.6.0 -l:libsfml-audio.so.2.6.0 #-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

M = src/model
V = src/view
C = src/controller

MODULES = display

all : Bomberman_Plat

Bomberman_Plat : $(M)/main.cpp  $(addsuffix .o, $(addprefix build/,$(MODULES))) 
# Linkage
	$(CXX)  $(MFLAGS)  $(CFLAGS) $^ -o $@.x $(LDFLAGS)



build/%.o : $(M)/%.cppm
# précompilation des modules
	$(CXX) $(MFLAGS) $(CFLAGS) --precompile $^ -o $(patsubst $(M)/%.cppm, build/%.pcm, $<)
# génération des fichiers objets
	$(CXX) $(MFLAGS) $(CFLAGS) -c $(patsubst $(M)/%.cppm, build/%.pcm, $<) -o $@

build/%.o : $(V)/%.cppm
	$(CXX) $(MFLAGS) $(CFLAGS) --precompile $^ -o $(patsubst $(V)/%.cppm, build/%.pcm, $<)
	$(CXX) $(MFLAGS) $(CFLAGS) -c $(patsubst $(V)/%.cppm, build/%.pcm, $<) -o $@

build/%.o : $(C)/%.cppm
	$(CXX) $(MFLAGS) $(CFLAGS) --precompile $^ -o $(patsubst $(C)/%.cppm, build/%.pcm, $<)
	$(CXX) $(MFLAGS) $(CFLAGS) -c $(patsubst $(C)/%.cppm, build/%.pcm, $<) -o $@


run:
	./Bomberman_Plat.x

clean:
	rm  build/*