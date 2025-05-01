@rem Usage:
@rem   run clean   # Clean
@rem   run AC6     # Run compilation flow with Arm Compiler 6
@rem   run CLANG   # Run compilation flow with LLVM Embedded toolchain for Arm
@rem   run GCC     # Run compilation flow with GCC
@rem   run IAR     # Run compilation flow with IAR compiler

set PROJECT_NAME=coremark
set HARDWARE_TYPE=MPS2_CM4_FP
set CSOLUTION_FILE=%PROJECT_NAME%.csolution.yml
set CSOLUTION_OPTIONS=
set CFG_UPDATE_RTE=1

if %CFG_UPDATE_RTE%.==1. set CSOLUTION_OPTIONS=--update-rte %CSOLUTION_OPTIONS%

set HARDWARE_LIST= MPS2_CM0 ^
  MPS2_CM0plus ^
  MPS2_CM3 ^
  MPS2_CM4 ^
  MPS2_CM4_FP ^
  MPS2_CM7 ^
  MPS2_CM7_SP ^
  MPS2_CM7_DP ^
  MPS2_CM23 ^
  MPS2_CM33 ^
  MPS2_CM33_FP ^
  MPS3-Corstone-300 ^
  MPS3-Corstone-310

@rem Default toolchain
@rem TOOLCHAIN = GCC/CLANG/AC6/IAR
set TOOLCHAIN=AC6

@if %1.==clean. goto clean
@if %1.==CLEAN. goto clean
@if %1.==AC6. goto use_AC6
@if %1.==ac6. goto use_AC6
@if %1.==GCC. goto use_GCC
@if %1.==gcc. goto use_GCC
@if %1.==CLANG. goto use_CLANG
@if %1.==clang. goto use_CLANG
@if %1.==IAR. goto use_IAR
@if %1.==iar. goto use_IAR

:use_AC6
set TOOLCHAIN=AC6
@goto setup_end

:use_GCC
set TOOLCHAIN=GCC
@goto setup_end

:use_CLANG
set TOOLCHAIN=CLANG
@goto setup_end

:use_IAR
set TOOLCHAIN=IAR
@goto setup_end

:setup_end

@echo -------------------------------------
@echo Step 1 - Optional. If local index file get outdated, you need to run this
cpackget update-index

@echo -------------------------------------
@echo Step 2 - Build project with Command Line Interface

for %%t in ( %HARDWARE_LIST%  ) do (
  cbuild %CSOLUTION_FILE% %CSOLUTION_OPTIONS% --packs --context %PROJECT_NAME%+%%t --toolchain %TOOLCHAIN% 
  )

@rem -------------------------------------
@rem Generate disassembly and binary file

@if %TOOLCHAIN%==AC6 goto step3_AC6
@if %TOOLCHAIN%==GCC goto step3_GCC
@if %TOOLCHAIN%==CLANG goto step3_CLANG
@if %TOOLCHAIN%==IAR goto step3_IAR

:step3_AC6
for %%t in ( %HARDWARE_LIST%  ) do (
  fromelf -c -d -e -s out\%%t\%PROJECT_NAME%.axf --output out\%%t\list.txt
  fromelf --bin --output out\%%t\test.bin out\%%t\%PROJECT_NAME%.axf
  )
@goto end

:step3_GCC
for %%t in ( %HARDWARE_LIST%  ) do (
  arm-none-eabi-objdump -S out\%%t\%PROJECT_NAME%.elf > out\%%t\list.txt
  arm-none-eabi-objcopy  -O binary out\%%t\%PROJECT_NAME%.elf out\%%t\test.bin
  )
@goto end

:step3_CLANG
for %%t in ( %HARDWARE_LIST%  ) do (
  llvm-objdump -S out\%%t\%PROJECT_NAME%.elf > out\%%t\list.txt
  llvm-objcopy  -O binary out\%%t\%PROJECT_NAME%.elf out\%%t\test.bin
  )
@goto end

:step3_IAR
for %%t in ( %HARDWARE_LIST%  ) do (
  ielfdumparm --all --source out\%%t\%PROJECT_NAME%.out --output out\%%t\list.txt
  ielftool --bin out\%%t\%PROJECT_NAME%.out out\%%t\test.bin
  )
@goto end

@REM -------------------------------------------
@REM Clean
@REM -------------------------------------------

:clean
@echo Clean
@rmdir /s /q tmp
@rmdir /s /q out
@rmdir /s /q RTE
@del %PROJECT_NAME%+*.*
@del *.cbuild-idx.yml
@del *.cbuild-pack.yml
@del required_pack*.txt

@goto end

@REM -------------------------------------------
:end
@REM -------------------------------------------
