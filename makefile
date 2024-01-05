CXX=clang++

LIB = /usr/local/lib
INC = /usr/local/include


MFLAGS = -std=c++20  -fprebuilt-module-path=build # for modules
CFLAGS =  -Wall -Wextra -I $(INC) -I include
LDFLAGS =  -L $(LIB)/SFML #-Wl,--disable-new-dtags,--rpath=$(LIBSFML) 
LDFLAGS += -l:libsfml-window.so.2.6.0  -l:libsfml-system.so.2.6.0 -l:libsfml-graphics.so.2.6.0 -l:libsfml-audio.so.2.6.0

# # Static attempt
# LDFLAGS +=  -D SFML_STATIC -l GL  -l X11 -l freetype -l Xrandr -l Xcursor -l udev  
# LDFLAGS +=  -l openal -l vorbisenc -l vorbisfile -l vorbis -l ogg -l FLAC -l pthread
# LDFLAGS += -l:libsfml-system.so.2.6
# LDFLAGS += -l:libsfml-window-s.a  -l:libsfml-system-s.a -l:libsfml-graphics-s.a -l:libsfml-audio-s.a


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