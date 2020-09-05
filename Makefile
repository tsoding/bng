BNGVIEWER_CFLAGS=$(shell pkg-config --cflags sdl2)
BNGVIEWER_LIBS=$(shell pkg-config --libs sdl2)

all: prime prime.wasm png2bng tsodinw.bng bngviewer bng.wasm

prime: prime.c
	$(CC) -O3 -o prime prime.c

prime.wasm: prime.wat
	wat2wasm prime.wat

png2bng: png2bng.c bng.h stb_image.h
	$(CC) -O3 -o png2bng png2bng.c -lm

tsodinw.bng: png2bng tsodinw.png
	./png2bng

bngviewer: bngviewer.c bng.h
	$(CC) $(BNGVIEWER_CFLAGS) -O3 -o bngviewer bngviewer.c $(BNGVIEWER_LIBS)

bng.wasm: bng.wat
	wat2wasm bng.wat
