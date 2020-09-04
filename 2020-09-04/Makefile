all: prime prime.wasm

prime: prime.c
	$(CC) -O3 -o prime prime.c

prime.wasm: prime.wat
	wat2wasm prime.wat
