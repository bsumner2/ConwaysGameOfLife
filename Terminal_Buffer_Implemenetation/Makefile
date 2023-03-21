CC=gcc
LD=gcc

INCLUDES=-I./include

LIBS=

CFLAGS=$(INCLUDES) $(LIBS)

LDFLAGS=$(LIBS)

SRC=./src

BIN=./bin

EXE=a.out


OBJS=$(shell find $(SRC) -type f -iname '*.c' | sed 's/.\/src\//.\/bin\//g' | sed 's/\.c/\.o/g')

.SILENT:
all: $(BIN) clean build run

run: build
	$(BIN)/$(EXE)


build: clean $(EXE)


$(EXE): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $(BIN)/$@

$(OBJS): $(BIN)/%.o : $(SRC)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

#-------------------------------Build----------------------------------------------------------------------



clean: $(BIN)
	@rm -fv $(BIN)/*.o*


$(BIN):
	mkdir -p bin
