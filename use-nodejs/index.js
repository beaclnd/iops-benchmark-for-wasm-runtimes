const fs = require("fs");
const path = require("path");
const { WASI } = require("wasi");

const func = async () => {
    const args = process.argv.slice(2);
    const wasmFilePath = args[0];
    const count = BigInt(parseInt(args[1], 10));
    const v1 = parseInt(args[2], 10);
    const v2 = parseInt(args[3], 10);
    const v3 = parseInt(args[4], 10);
    const v4 = parseInt(args[5], 10);

    const wasmBytes = fs.readFileSync(wasmFilePath);

    const module = await WebAssembly.compile(wasmBytes);
    const wasi = new WASI();
    const importObject = { wasi_snapshot_preview1: wasi.wasiImport }
    const instance = await WebAssembly.instantiate(module, importObject);
    // Must call the start function firstly to prevent the Error: wasi.start() has not been called
    wasi.start(instance);
    instance.exports.get_iops_for_int(count, v1, v2, v3, v4);
    instance.exports.get_iops_for_long_long(count, BigInt(v1), BigInt(v2), BigInt(v3), BigInt(v4));
}

func();