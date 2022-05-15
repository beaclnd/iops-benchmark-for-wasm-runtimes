use std::error::Error;
use std::{ env };
use wasmtime::*;
use wasmtime_wasi::*;

fn main() -> Result<(), Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();
    let wasm_file_path = &args[1];
    let count = args[2].parse::<i64>()?;
    let v1 = args[3].parse::<i64>()?;
    let v2 = args[4].parse::<i64>()?;
    let v3 = args[5].parse::<i64>()?;
    let v4 = args[6].parse::<i64>()?;

    let engine = Engine::default();
    let mut linker = Linker::new(&engine);
    wasmtime_wasi::add_to_linker(&mut linker, |s| s)?;
    let wasi = WasiCtxBuilder::new()
        .inherit_stdio()
        .inherit_args()?
        .build();
    let mut store = Store::new(&engine, wasi);

    let module = Module::from_file(&engine, wasm_file_path)?;
    linker.module(&mut store, "", &module)?;
    linker
        .get(&mut store, "", "get_iops").unwrap().into_func().unwrap()
        .typed::<(i64, i64, i64, i64, i64), (), _>(&store)?
        .call(&mut store, (count, v1, v2, v3, v4))?;

    Ok(())
}
