# Blinky example for Cortex-M55 running on Arm MPS3 FPGA board (AN552 FPGA image)
[![CMSIS Compliance](https://img.shields.io/github/actions/workflow/status/Arm-Examples/EW2024_CMSIS-Toolbox/verify-example1_cm55_mps3_an552.yml?logo=arm&logoColor=0091bd&label=CMSIS%20Compliance)](https://www.keil.arm.com/cmsis)

## Documentation related to the system

* [Application Note AN552 - Arm Corstone SSE-300 with Cortex-M55 and Ethos-U55: Example Subsystem for MPS3](https://developer.arm.com/documentation/dai0552/latest/)
* [Arm MPS3 FPGA Prototyping Board Technical Reference Manual](https://developer.arm.com/documentation/100765/latest/)
* [Arm MPS3 FPGA Prototyping board product page](https://developer.arm.com/Tools%20and%20Software/MPS3%20FPGA%20Prototyping%20Board)
* [Download FPGA images (Please see AN552)](https://developer.arm.com/downloads/-/download-fpga-images)

## Steps to use this demo using command line interface

Before starting, edit blink.csolution.yml to select toolchain (GCC/CLANG/AC6/IAR).

```
/* Step 1 : Update local copy of pack index */
cpackget update-index
```
Note: This is not required for a new installation and usually this is not needed. But if the local CMSIS-Pack storage hasn't been used for a while, it worth running it to ensure the index is up-to-date.
```
/* Step 2: Download packs and compile the project in one go */
cbuild blink.csolution.yml --packs --update-rte
```

Note: For IAR EWARM only - Instead of running step 2, you can import csolution project in EWARM to compile the project.

You can also override the toolchain choice (the following example use AC6, but it can also be GCC, CLANG or IAR):
```
/* Step 2: Download packs and compile the project in one go */
cbuild blink.csolution.yml --packs --update-rte --toolchain AC6
```
