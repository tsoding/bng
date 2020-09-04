# Extending Native Browser Capabilities with WebAssembly

- [x] Premise: Performance of WASM is probably comparable to native code
  - [x] Let's check it by implementing a Prime Number Crunching as a "Benchmark":
    - [x] [Native C Implementation](./prime.c)
      ```console
        $ time ./prime
        179424673

        real    0m52.964s
        user    0m52.766s
        sys     0m0.196s
      ```
    - [x] [JavaScript Implementation](./prime-naive.js)
      ```console
        $ time node prime-naive.js
        179424673

        real    2m4.781s
        user    2m4.414s
        sys     0m0.208s
      ```
    - [x] [WebAssembly Implemention](./prime.wat)
      ```console
        $ time node prime-wasm.js
        179424673

        real    1m17.061s
        user    1m16.844s
        sys     0m0.192s
      ```
- [ ] Idea: Let's imagine we invented a new image format that didn't exist before
  - [ ] If we implement the image support in WASM can we make it feel like a native browser support
    - [x] [Implement png2bng](./png2bng.c)
    - [x] [Implement bngviewer](./bngviewer.c)
    - [ ] Implement bng support in WASM
      - [x] fetch("tsodinw.bng"):
        ```js
          fetch("./tsodinw.bng").then((x) => console.log(x.arrayBuffer()))
        ```
      - [x] Put the fetched file into WASM memory
        ```js
          let bngFile = await fetch("tsodinw.bng");
          let fileData = await bngFile.arrayBuffer();
          let memory = new WebAssembly.Memory({initial: 10, maximum: 10});
          new Uint8Array(memory.buffer).set(new Uint8Array(fileData));
        ```
      - [ ] Call a WASM function that turns the file into Image Data
      - [ ] Take out the Image Data from WASM memory and display it
    - [ ] Add more interesting features to bng to test the support
