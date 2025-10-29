@rem Usage:
@rem   run clean   # Clean
@rem   run AC6     # Run compilation flow with Arm Compiler 6
@rem   run CLANG   # Run compilation flow with LLVM Embedded toolchain for Arm
@rem   run GCC     # Run compilation flow with GCC
@rem   run IAR     # Run compilation flow with IAR compiler

set PROJECT_NAME=coremark-pro
set HARDWARE_TYPE=MPS2_CM7_DP
set CSOLUTION_FILE=%PROJECT_NAME%.csolution.yml
set CSOLUTION_OPTIONS=
set CFG_UPDATE_RTE=1

if %CFG_UPDATE_RTE%.==1. set CSOLUTION_OPTIONS=--update-rte %CSOLUTION_OPTIONS%

@rem List of tests in CoreMark-Pro
@rem Note: zip-test is skipped because a file in ziplib is not folowing modern C standard
@rem       and therefore can have problem with certain compilers.
set TEST_LIST=core ^
  cjpeg-rose7-preset ^
  linear_alg-mid-100x100-sp ^
  loops-all-mid-10k-sp ^
  nnet_test ^
  parser-125k ^
  radix2-big-64k ^
  sha-test

@rem Default toolchain
@rem TOOLCHAIN = GCC/CLANG/AC6/IAR
set TOOLCHAIN=AC6

@if %1.==CLEAN. goto clean
@if %1.==clean. goto clean
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

for %%t in ( %TEST_LIST%  ) do (
  cbuild %CSOLUTION_FILE% %CSOLUTION_OPTIONS% --context %%t+%HARDWARE_TYPE% --packs --toolchain %TOOLCHAIN%
  )

@rem -------------------------------------
@rem Generate disassembly and binary file

@if %TOOLCHAIN%==AC6 goto step3_AC6
@if %TOOLCHAIN%==GCC goto step3_GCC
@if %TOOLCHAIN%==CLANG goto step3_CLANG
@if %TOOLCHAIN%==IAR goto step3_IAR

:step3_AC6
for %%t in ( %TEST_LIST%  ) do (
  fromelf -c -d -e -s out\%%t\%HARDWARE_TYPE%\%%t.axf --output out\%%t\%HARDWARE_TYPE%\list.txt
  fromelf --bin --output out\%%t\%HARDWARE_TYPE%\test.bin out\%%t\%HARDWARE_TYPE%\%%t.axf
  )
@goto end

:step3_GCC
for %%t in ( %TEST_LIST%  ) do (
  arm-none-eabi-objdump -S out\%%t\%HARDWARE_TYPE%\%%t.elf > out\%%t\%HARDWARE_TYPE%\list.txt
  arm-none-eabi-objcopy  -O binary out\%%t\%HARDWARE_TYPE%\%%t.elf out\%%t\%HARDWARE_TYPE%\test.bin
  )
@goto end

:step3_CLANG
for %%t in ( %TEST_LIST%  ) do (
  llvm-objdump -S out\%%t\%HARDWARE_TYPE%\%%t.elf > out\%%t\%HARDWARE_TYPE%\list.txt
  llvm-objcopy  -O binary out\%%t\%HARDWARE_TYPE%\%%t.elf out\%%t\%HARDWARE_TYPE%\test.bin
  )
@goto end

:step3_IAR
for %%t in ( %TEST_LIST%  ) do (
  ielfdumparm --all --source out\%%t\%HARDWARE_TYPE%\%%t.out --output out\%%t\%HARDWARE_TYPE%\list.txt
  ielftool --bin out\%%t\%HARDWARE_TYPE%\%%t.out out\%%t\%HARDWARE_TYPE%\test.bin
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
for %%t in ( %TEST_LIST%  ) do (
  del proj_%%t\%%t+%HARDWARE_TYPE%.cprj
  del proj_%%t\%%t+%HARDWARE_TYPE%.cbuild.yml
  rmdir /s /q proj_%%t\RTE
  )
@goto end

@REM -------------------------------------------
:end
@REM -------------------------------------------
