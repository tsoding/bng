async function bng() {
    let bngFile = await fetch("tsodinw.bng");
    let fileData = await bngFile.arrayBuffer();
    let memory = new WebAssembly.Memory({initial: 10, maximum: 10});
    new Uint8Array(memory.buffer).set(new Uint8Array(fileData));
    let bngProgram = await WebAssembly.instantiateStreaming(
        fetch("bng.wasm"),
        { js: { mem: memory, print: arg => console.log(arg) } });
    bngProgram.instance.exports.bng();
}

bng().catch((e) => console.log(e));
