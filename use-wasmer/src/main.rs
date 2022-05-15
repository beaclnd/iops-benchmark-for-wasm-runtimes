use std::error::Error;
use std::{ env, fs };
use wasmer::{Instance, Module, NativeFunc, Store};
use wasmer_wasi::WasiState;
use wasmer_compiler_singlepass::Singlepass;
use wasmer_compiler_cranelift::Cranelift;
use wasmer_compiler_llvm::LLVM;
use wasmer_engine_universal::Universal;

fn main() -> Result<(), Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();
    let compiler_name = &args[1];
    let wasm_file_path = &args[2];
    let count = args[3].parse::<i64>()?;
    let v1 = args[4].parse::<i64>()?;
    let v2 = args[5].parse::<i64>()?;
    let v3 = args[6].parse::<i64>()?;
    let v4 = args[7].parse::<i64>()?;
    let wasm_bytes = fs::read(wasm_file_path)?;

    // println!("wasm_bytes': {:?}", wasm_bytes);

    let store = match compiler_name.as_str() {
        "singlepass" => Store::new(&Universal::new(Singlepass::default()).engine()),
        "cranelift" => Store::new(&Universal::new(Cranelift::default()).engine()),
        "llvm" => Store::new(&Universal::new(LLVM::default()).engine()),
        _ =>  Store::default(),
    };
    let module = Module::new(&store, wasm_bytes)?;
    let mut wasi_env = WasiState::new("import_example").finalize()?;
    let wasi_import_object = wasi_env.import_object(&module)?;
    let instance = Instance::new(&module, &wasi_import_object)?;
    let run_func: NativeFunc<(i64, i64, i64, i64, i64), ()> = instance.exports.get_native_function("get_iops")?;
    run_func.call(count, v1, v2, v3, v4)?;

    Ok(())
}

