function setImageDataToCanvas(imageData, canvasId)
{
    let canvas = document.getElementById(canvasId);
    canvas.width = imageData.width;
    canvas.height = imageData.height;
    let context = canvas.getContext("2d");
    context.putImageData(imageData, 0, 0);
}

async function bng(imageFileName) {
    // TODO(#4): keep bng.wasm as a byte array of bng.js
    let bngFile = await fetch(imageFileName);
    let fileData = await bngFile.arrayBuffer();
    // TODO(#5): allocate WebAssembly memory based on the file size
    let memory = new WebAssembly.Memory({initial: 300, maximum: 1000});
    new Uint8Array(memory.buffer).set(new Uint8Array(fileData));
    let bngProgram = await WebAssembly.instantiateStreaming(
        fetch("bng.wasm"),
        { js: { mem: memory, print: arg => console.log(arg) } });
    let offset = bngProgram.instance.exports.bng_offset();
    let size = bngProgram.instance.exports.bng_size();
    let width = bngProgram.instance.exports.bng_width();
    let height = bngProgram.instance.exports.bng_height();

    let unprocessedImageData = new ImageData(
        new Uint8ClampedArray(memory.buffer).slice(offset, offset + size), width, height);
    setImageDataToCanvas(unprocessedImageData, "bng-unprocessed");

    bngProgram.instance.exports.bng_process();
    let processedImageData = new ImageData(
        new Uint8ClampedArray(memory.buffer).slice(offset, offset + size), width, height);
    setImageDataToCanvas(processedImageData, "bng-processed");
}

bng("tsodinw.bng").catch((e) => console.log(e));
