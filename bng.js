const IMAGE_FILENAME = "tsodinw.bng";

async function bng() {
    let bngFile = await fetch(IMAGE_FILENAME);
    let fileData = await bngFile.arrayBuffer();
    let memory = new WebAssembly.Memory({initial: 300, maximum: 1000});
    new Uint8Array(memory.buffer).set(new Uint8Array(fileData));
    let bngProgram = await WebAssembly.instantiateStreaming(
        fetch("bng.wasm"),
        { js: { mem: memory, print: arg => console.log(arg) } });
    let offset = bngProgram.instance.exports.bng_offset();
    let size = bngProgram.instance.exports.bng_size();
    let width = bngProgram.instance.exports.bng_width();
    let height = bngProgram.instance.exports.bng_height();
    bngProgram.instance.exports.bng_process();
    let imageData = new ImageData(new Uint8ClampedArray(memory.buffer).slice(offset, offset + size), width, height);
    let canvas = document.querySelector("#bng");
    canvas.width = width;
    canvas.height = height;
    let context = canvas.getContext("2d");
    context.putImageData(imageData, 0, 0);
}

bng().catch((e) => console.log(e));
