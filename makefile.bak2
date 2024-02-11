CXX=clang++-16

LIB = /usr/local/lib
INC = /usr/local/include


PRECOMPILE = -fprebuilt-module-path=build --precompile
CFLAGS =  -Wall -Wextra  -std=c++20 #for modules
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

SRC_M = $(wildcard $(M)/*.cppm)
OBJ_M = $(patsubst $(M)/%.cppm,build/%.o,$(SRC_M))

SRC_V = $(wildcard $(V)/*.cppm)
OBJ_V = $(patsubst $(V)/%.cppm,build/%.o,$(SRC_V))

SRC_C = $(wildcard $(C)/*.cppm)
OBJ_C = $(patsubst $(C)/%.cppm,build/%.o,$(SRC_C))





all : create_modules Bomberman_Plat



ORDER_MODULES = tMode viewAPI Menu Event parser Entity Board
create_modules : $(addsuffix .o, $(addprefix build/,$(ORDER_MODULES))) 
	echo "pls work"

Bomberman_Plat : $(M)/main.cpp  $(OBJ_M) $(OBJ_V) $(OBJ_C)
# Linkage
	$(CXX) $(CFLAGS)  -fprebuilt-module-path=build $^ -o $@.x $(LDFLAGS)







TEST = boardManager
test : $(addsuffix .o, $(addprefix build/,$(TEST))) 
	echo "pls work its making me sad"



SFML_FLAG = -I $(INC)/SFML
XML_FLAG = -I /usr/include/rapidxml

build/%.o : $(M)/%.cppm # model
# précompilation des modules
	$(CXX) $(CFLAGS) $(PRECOMPILE) $^ -o $(patsubst $(M)/%.cppm, build/%.pcm, $<)
# génération des fichiers objets
	$(CXX) $(CFLAGS) -c $(patsubst $(M)/%.cppm, build/%.pcm, $<) -o $@

build/%.o : $(V)/%.cppm # view
	$(CXX) $(CFLAGS) $(PRECOMPILE) $(XML_FLAG) $(SFML_FLAG) $^ -o $(patsubst $(V)/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst $(V)/%.cppm, build/%.pcm, $<) -o $@

build/%.o : $(C)/%.cppm # controller
	$(CXX) $(CFLAGS) $(PRECOMPILE) $(SFML_FLAG) $^ -o $(patsubst $(C)/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst $(C)/%.cppm, build/%.pcm, $<) -o $@

build/%.o : src/%.cppm # classes et types
	$(CXX) $(CFLAGS) $(PRECOMPILE) $^ -o $(patsubst src/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst src/%.cppm, build/%.pcm, $<) -o $@




run:
	./Bomberman_Plat.x

cleanAll:
	rm  build/*