all: prime prime.wasm png2bng tsodinw.bng

prime: prime.c
	$(CC) -O3 -o prime prime.c

prime.wasm: prime.wat
	wat2wasm prime.wat

png2bng: png2bng.c bng.h stb_image.h
	$(CC) -O3 -o png2bng png2bng.c -lm

tsodinw.bng: png2bng tsodinw.png
	./png2bng
