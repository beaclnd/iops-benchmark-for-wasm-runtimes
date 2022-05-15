main: iops.wasm bin/use-wasmer bin/use-wasmtime
	gcc -o main main.c iops.c

iops.wasm:
	clang --target=wasm32-wasi --sysroot ~/Workspace/MyApplications/wasi-sdk-15.0/share/wasi-sysroot -nostartfiles -Wl,--no-entry,--export-dynamic -o iops.wasm iops.c
	wasm2wat iops.wasm > iops.wat

bin/use-wasmer:
	cd use-wasmer && cargo build --release && \
	cp target/release/use-wasmer ../bin/

bin/use-wasmtime:
	cd use-wasmtime && cargo build --release && \
	cp target/release/use-wasmtime ../bin/

clean:
	rm iops.wasm
	rm -fr ./bin && mkdir bin 
	rm main 