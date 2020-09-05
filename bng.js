async function bng() {
    let bngFile = await fetch("tsodinw.bng");
    let fileData = await bngFile.arrayBuffer();
    let memory = new WebAssembly.Memory({initial: 10, maximum: 10});
    new Uint8Array(memory.buffer).set(new Uint8Array(fileData));
    let bngProgram = await WebAssembly.instantiateStreaming(
        fetch("bng.wasm"),
        { js: { mem: memory, print: arg => console.log(arg) } });
    let size = bngProgram.instance.exports.bng_size();
    let width = bngProgram.instance.exports.bng_width();
    let height = bngProgram.instance.exports.bng_height();
    let imageData = new ImageData(new Uint8ClampedArray(memory.buffer).slice(12, 12 + size), width, height);
    let canvas = document.querySelector("#bng");
    let context = canvas.getContext("2d");
    context.putImageData(imageData, 0, 0);
}

bng().catch((e) => console.log(e));
