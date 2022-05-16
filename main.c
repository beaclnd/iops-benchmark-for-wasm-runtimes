#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "iops.h"

int main(int argc, char* argv[]) {
    char* wasm_file = argv[1];
    char cmd[1024] = {0};
	srand(time(NULL));
    long long v1 = rand() % 1000000;
    long long v2 = rand() % 1000000;
    long long v3 = rand() % 1000000;
    long long v4 = rand() % 1000000;

    // For the console output formats
    const char* spaces1 = "                              ";
    const char* spaces2 = "            ";
    const char* divider = "--------------------------------------------------------------------------------------------------------------------------------------------------";

    printf("Runtime%sInterger Type%sOperation Count%sTime(ms)%sIOPS(Interger Operations per Seconds)\n", spaces1, spaces2, spaces2, spaces2);
    printf("%s\n", divider);

    printf("native(use gcc without optimization)\n");
    get_iops_for_int(1000000000, (int)v1, (int)v2, (int)v3, (int)v4);
    get_iops_for_long_long(1000000000, v1, v2, v3, v4);
    printf("%s\n", divider);

    char count_str[100] = {0};
    sprintf(count_str, "%lld", 1000000000);
    char v1_str[100] = {0};
    sprintf(v1_str, "%lld", v1);
    char v2_str[100] = {0};
    sprintf(v2_str, "%lld", v2);
    char v3_str[100] = {0};
    sprintf(v3_str, "%lld", v3);
    char v4_str[100] = {0};
    sprintf(v4_str, "%lld", v4);

    printf("wasmer-singlepass\n");
    strcat(cmd, "./bin/use-wasmer singlepass ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    printf("%s\n", divider);

    printf("wasmer-cranelift\n");
    strcat(cmd, "./bin/use-wasmer cranelift ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    printf("%s\n", divider);

    printf("wasmer-llvm\n");
    strcat(cmd, "./bin/use-wasmer llvm ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    printf("%s\n", divider);

    printf("wasmtime(use cranelift in fact)\n");
    strcat(cmd, "./bin/use-wasmtime ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    printf("%s\n", divider);

    printf("wavm(use llvm in fact)\n");
    strcat(cmd, "wavm run --function=get_iops_for_int ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    strcat(cmd, "wavm run --function=get_iops_for_long_long ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    printf("%s\n", divider);

    printf("wamr(use interpreter in fact)\n");
    strcat(cmd, "iwasm --function get_iops_for_int ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    strcat(cmd, "iwasm --function get_iops_for_long_long ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    system(cmd);
    memset(cmd, 0, 1024);
    printf("%s\n", divider);

    printf("nodejs(use liftoff,turbofan in fact)\n");
    strcat(cmd, "node --experimental-wasi-unstable-preview1 use-nodejs/index.js ");
    strcat(cmd, wasm_file);
    strcat(cmd, " ");
    strcat(cmd, count_str);
    strcat(cmd, " ");
    strcat(cmd, v1_str);
    strcat(cmd, " ");
    strcat(cmd, v2_str);
    strcat(cmd, " ");
    strcat(cmd, v3_str);
    strcat(cmd, " ");
    strcat(cmd, v4_str);
    strcat(cmd, " 2>/dev/null");
    system(cmd);
    memset(cmd, 0, 1024);
    printf("%s\n", divider);
}

