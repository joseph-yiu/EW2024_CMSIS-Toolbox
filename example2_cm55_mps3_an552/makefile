# Usage:
# make all      # Run all steps using default compiler choice
# make AC6      # Run all steps using Arm Compiler 6
# make CLANG    # Run all steps using LLVM Embedded Toolchain for Arm
# make GCC      # Run all steps using GCC
# make IAR      # Run all steps using IAR
# make step1                                # Run step1 only - update local index file 
# make step2 TOOLCHAIN={AC6/CLANG/GCC/IAR)  # Build project with Command Line Interface
# make step3 TOOLCHAIN={AC6/CLANG/GCC/IAR)  # Generate disassembly and binary file

PROJECT_NAME   = hello
HARDWARE_TYPE  = MPS3-Corstone-300
CSOLUTION_FILE = $(PROJECT_NAME).csolution.yml

CSOLUTION_OPTIONS =

CFG_UPDATE_RTE = 1

ifeq ($(CFG_UPDATE_RTE),1)
  CSOLUTION_OPTIONS += --update-rte
endif

# TOOLCHAIN = AC6/GCC/CLANG/IAR
TOOLCHAIN = AC6

all: step1 step2 step3 step4 step5 step6

ac6: AC6

AC6:
	cpackget update-index
	cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --packs --toolchain AC6 
	make step3_AC6

gcc: GCC

GCC:
	cpackget update-index
	cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --packs --toolchain GCC
	make step3_GCC

clang: CLANG

CLANG:
	cpackget update-index
	cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --packs --toolchain CLANG
	make step3_CLANG

iar: IAR

IAR:
	cpackget update-index
	cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --packs --toolchain IAR
	make step6_IAR


step1:
	# Optional. If local index file get outdated, you need to run this
	cpackget update-index
	
step2:
	# Build project with Command Line Interface and automatically download packs if needed
	cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --packs --toolchain $(TOOLCHAIN)

step3: step3_$(TOOLCHAIN)

step3_AC6:
	# Generate disassembly and binary file
	fromelf -c -d -e -s out/$(HARDWARE_TYPE)/$(PROJECT_NAME).axf --output out/$(HARDWARE_TYPE)/list.txt
	fromelf --bin --output out/$(HARDWARE_TYPE)/test.bin out/$(HARDWARE_TYPE)/$(PROJECT_NAME).axf

step3_GCC:
	# Generate disassembly and binary file
	arm-none-eabi-objdump -S out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf > out/$(HARDWARE_TYPE)/list.txt
	arm-none-eabi-objcopy  -O binary out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf out/$(HARDWARE_TYPE)/test.bin

step3_CLANG:
	# Generate disassembly and binary file
	llvm-objdump -S out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf > out/$(HARDWARE_TYPE)/list.txt
	llvm-objcopy  -O binary out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf out/$(HARDWARE_TYPE)/test.bin

step3_IAR:
	# Generate disassembly and binary file
	ielfdumparm --all --source out/$(HARDWARE_TYPE)/$(PROJECT_NAME).out --output out/$(HARDWARE_TYPE)/list.txt
	ielftool --bin out/$(HARDWARE_TYPE)/$(PROJECT_NAME).out out/$(HARDWARE_TYPE)/test.bin


clean:
	@if [ -e *.cbuild-idx.yml ] ; then \
	  rm *.cbuild-idx.yml ; \
	fi
	@if [ -e *.cbuild-pack.yml ] ; then \
	  rm *.cbuild-pack.yml ; \
	fi
	@if [ -e *.cbuild.yml ] ; then \
	  rm *.cbuild.yml ; \
	fi
	@if [ -e *.cprj ] ; then \
	  rm *.cprj ; \
	fi
	@if [ -e required_packs.txt ] ; then \
	  rm required_packs.txt; \
	fi
	@if [ -d tmp ] ; then \
	  rm -rf tmp ; \
	fi
	@if [ -d out ] ; then \
	  rm -rf out ; \
	fi
	@if [ -d RTE ] ; then \
	  rm -rf RTE ; \
	fi
	
