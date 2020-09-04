const fs = require("fs");

WebAssembly
    .instantiate(new Uint8Array(fs.readFileSync("./prime.wasm")), {})
    .then((obj) => console.log(obj.instance.exports.prime(10 * 1000 * 1000)))
    .catch((x) => console.log(x));
