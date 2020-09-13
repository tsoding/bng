BNGVIEWER_CFLAGS=$(shell pkg-config --cflags sdl2) -ggdb 
BNGVIEWER_LIBS=$(shell pkg-config --libs sdl2)

PNG2BNG_CFLAGS=-ggdb 

BNG_TEST_CFLAGS=-ggdb

.PHONY: all
all: png2bng tsodinw.bng bngviewer bng.wasm

png2bng: png2bng.c bng.h stb_image.h
	$(CC) $(PNG2BNG_CFLAGS) -o png2bng png2bng.c -lm

tsodinw.bng: png2bng tsodinw.png
	./png2bng tsodinw.png tsodinw.bng GRAB

bngviewer: bngviewer.c bng.h
	$(CC) $(BNGVIEWER_CFLAGS) -o bngviewer bngviewer.c $(BNGVIEWER_LIBS)

bng.wasm: bng.wat
	wat2wasm bng.wat

bng.wat: bng.wat.in
	cpp -P bng.wat.in > bng.wat

.PHONY: test
test: bng_test
	./bng_test

bng_test: bng_test.c bng.h stb_image.h
	$(CC) $(BNG_TEST_CFLAGS) -o bng_test bng_test.c -lm
