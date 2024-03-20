CXX = clang++-16

LIB = /usr/local/lib
INC = /usr/local/include

PRECOMPILE = -fprebuilt-module-path=build --precompile
CFLAGS = -Wall -Wextra  -std=c++20 #for modules
CFLAGS += -O0 # for debug

ifeq ($(wildcard $(LIB)/SFML/libsfml-system.so.2.6),)
# SFML2.6.0 not installed
	LDFLAGS = -l sfml-window -l sfml-system -l sfml-graphics -l sfml-audio
	SFML_FLAG = 
else
# SFML2.6.0 installed
	LDFLAGS = -L $(LIB)/SFML -l:libsfml-window.so.2.6.0  -l:libsfml-system.so.2.6.0 -l:libsfml-graphics.so.2.6.0 -l:libsfml-audio.so.2.6.0
	SFML_FLAG = -I $(INC)/SFML
	CFLAGS+= -D SFML_2_6_0
#Quelques différences dans le code
endif

XML_FLAG = -I /usr/include/rapidxml




# ========= commands for users =========

all : createBuild  createModules Bomberman_Plat

cleanAll:
	- rm  build/*
#	rm Bomberman_Plat.x

createBuild:
	- mkdir build



# ========= rules for compiling =========

API = src/engine/libAPI
build/%.o : $(API)/%.cppm # engine/libAPI
	$(CXX) $(CFLAGS) $(PRECOMPILE) $(XML_FLAG) $(SFML_FLAG) $^ -o $(patsubst $(API)/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst $(API)/%.cppm, build/%.pcm, $<) -o $@

LOGIC = src/engine/logic
build/%.o : $(LOGIC)/%.cppm # engine/logic
	$(CXX) $(CFLAGS) $(PRECOMPILE)  $^ -o $(patsubst $(LOGIC)/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst $(LOGIC)/%.cppm, build/%.pcm, $<) -o $@


BOMB = src/bomberman
build/%.o : $(BOMB)/%.cppm # bomberman
	$(CXX) $(CFLAGS) $(PRECOMPILE)  $^ -o $(patsubst $(BOMB)/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst $(BOMB)/%.cppm, build/%.pcm, $<) -o $@


GAME = src/bomberman/game
build/%.o : $(GAME)/%.cppm # bomberman/game
	$(CXX) $(CFLAGS) $(PRECOMPILE)  $^ -o $(patsubst $(GAME)/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst $(GAME)/%.cppm, build/%.pcm, $<) -o $@


# compile: 
#     @for file in $(SOURCES); do \
#         $(CC) $(CFLAGS) -c $$file -o $$(basename $$file .c).o; \
# 		$(CXX) $(CFLAGS) $(PRECOMPILE) $^ -o $(patsubst $(V)/%.cppm, build/%.pcm, $<) \
# 		$(CXX) $(CFLAGS) -c $(patsubst $(V)/%.cppm, build/%.pcm, $<) -o $@ \
#     done



SOURCES = $(shell find src -type f -iname '*.cppm')
MODULES = $(notdir $(SOURCES))
OBJ = $(patsubst %.cppm, build/%.o, $(MODULES))

Bomberman_Plat : src/engine/logic/main.cpp  $(OBJ)
# Linkage
	@echo $(MODULES)
	$(CXX) $(CFLAGS)  -fprebuilt-module-path=build $^ -o $@.x $(LDFLAGS)



# ========= When things go wrong =========

ORDER_MODULES = menu viewAPI Event parser assetsBindings Entity Board gameVars Editor  modeGame modeMenu modeEditor
createModules : $(addsuffix .o, $(addprefix build/,$(ORDER_MODULES))) 
	@echo "pls work"

TEST = boardManager
test : $(addsuffix .o, $(addprefix build/,$(TEST))) 
	@echo "pls work its making me sad"