CXX=clang++-16

LIB = /usr/local/lib
INC = /usr/local/include


PRECOMPILE = -fprebuilt-module-path=build --precompile
CFLAGS =  -Wall -Wextra  -std=c++20 #for modules
LDFLAGS =  -L $(LIB)/SFML 
LDFLAGS += -l:libsfml-window.so.2.6.0  -l:libsfml-system.so.2.6.0 -l:libsfml-graphics.so.2.6.0 -l:libsfml-audio.so.2.6.0


# ========= rules for compiling =========

API = src/engine/libAPI
SFML_FLAG = -I $(INC)/SFML
XML_FLAG = -I /usr/include/rapidxml

build/%.o : $(API)/%.cppm # API
	$(CXX) $(CFLAGS) $(PRECOMPILE) $(XML_FLAG) $(SFML_FLAG) $^ -o $(patsubst $(API)/%.cppm, build/%.pcm, $<)
	$(CXX) $(CFLAGS) -c $(patsubst $(API)/%.cppm, build/%.pcm, $<) -o $@







SOURCES = $(shell find src -type f -iname '*.c')
MODULES = $(notdir $(SOURCES))
OBJ = $(patsubst %.cppm, build/%.pcm, $(MODULES))


compile:
    @for file in $(SOURCES); do \
        $(CC) $(CFLAGS) -c $$file -o $$(basename $$file .c).o; \
		$(CXX) $(CFLAGS) $(PRECOMPILE) $(XML_FLAG) $(SFML_FLAG) $^ -o $(patsubst $(V)/%.cppm, build/%.pcm, $<) \
		$(CXX) $(CFLAGS) -c $(patsubst $(V)/%.cppm, build/%.pcm, $<) -o $@ \
    done









Bomberman_Plat : src/engine/logic/main.cpp  $(OBJ)
# Linkage
	$(CXX) $(CFLAGS)  -fprebuilt-module-path=build $^ -o $@.x $(LDFLAGS)

# ========= commands for users =========

all : create_modules Bomberman_Plat

cleanAll:
	rm  build/*
#	rm Bomberman_Plat.x


# ========= When things go wrong =========

ORDER_MODULES = tMode viewAPI Menu Event parser Entity Board
create_modules : $(addsuffix .o, $(addprefix build/,$(ORDER_MODULES))) 
	@echo "pls work"

TEST = boardManager
test : $(addsuffix .o, $(addprefix build/,$(TEST))) 
	@echo "pls work its making me sad"