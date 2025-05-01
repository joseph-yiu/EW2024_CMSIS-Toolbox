# Hello world example for Cortex-M4 running on Arm MPS2/MPS2+ FPGA board (AN386 FPGA image)
[![CMSIS Compliance](https://img.shields.io/github/actions/workflow/status/Arm-Examples/EW2024_CMSIS-Toolbox/verify-example2_cm4_mps2_an386.yml?logo=arm&logoColor=0091bd&label=CMSIS%20Compliance)](https://www.keil.arm.com/cmsis)

## Descriptions

Printf "Hello world" and then a incrementing number at 10 Hz.

The printf is handled by CMSIS-Compiler, with uart_funcs.c provides the low level UART functions and interface to CMSIS-Compiler.

The UART is configured as 38400bps, 8-bit, no parity.

## Documentation related to the system

* [Application Note AN386 - ARM Cortex-M4 SMM on V2M-MPS2](https://developer.arm.com/documentation/dai0386/latest/)
* [Arm MPS2 and MPS2+ FPGA Prototyping Boards Technical Reference Manual](https://developer.arm.com/documentation/100112/latest/)
* [MPS2+ FPGA Prototyping board product page](https://developer.arm.com/Tools%20and%20Software/MPS2%20Plus%20FPGA%20Prototyping%20Board)
* [Download FPGA images (Please see VEM31)](https://developer.arm.com/downloads/-/download-fpga-images)

## Steps to use this demo using command line interface

Before starting, edit <project_name>.csolution.yml to select toolchain (GCC/CLANG/AC6/IAR).

```
/* Step 1 : Update local copy of pack index */
cpackget update-index
```
Note: This is not required for a new installation and usually this is not needed. But if the local CMSIS-Pack storage hasn't been used for a while, it worth running it to ensure the index is up-to-date.
```
/* Step 2: Download packs and compile the project in one go */
cbuild hello.csolution.yml --packs --update-rte
```

Note: For IAR EWARM only - Instead of running step 2, you can import csolution project in EWARM to compile the project.

You can also override the toolchain choice (the following example use AC6, but it can also be GCC, CLANG or IAR):
```
/* Step 2: Download packs and compile the project in one go */
cbuild hello.csolution.yml --packs --update-rte --toolchain AC6
```
