CC=g++
LD=g++

SRC=./src
BIN=./bin

INCS=-I./include -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sysprof-4 -pthread -I/usr/include/AL

LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
CFLAGS=$(INCS)
LDFLAGS=$(LIBS)

OBJS=$(shell find $(SRC) -type f -iname '*.cpp' | sed 's/.\/src\//.\/bin\//g' | sed 's/\.cpp/\.o/g')

EXE=test.elf


#.SILENT:
all: $(BIN) clean build run

run: build
	$(BIN)/$(EXE)


build: clean $(EXE)


$(EXE): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $(BIN)/$@

$(OBJS): $(BIN)/%.o : $(SRC)/%.cpp
	$(CC) -c $< $(CFLAGS) -o $@

#-------------------------------Build----------------------------------------------------------------------



clean: $(BIN)
	@rm -fv $(BIN)/*.o*


$(BIN):
	mkdir -p bin
