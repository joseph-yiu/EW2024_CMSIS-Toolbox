# Usage:
# make all      # Run all steps using default compiler choice
# make AC6      # Run all steps using Arm Compiler 6
# make CLANG    # Run all steps using LLVM Embedded Toolchain for Arm
# make GCC      # Run all steps using GCC
# make IAR      # Run all steps using IAR
# make step1                                # Run step1 only - update local index file 
# make step2                                # Run step2 only - Identified if any CMSIS-PACK is missing
# make step3                                # Run step3 only - Add missing CMSIS-PACK
# make step4 TOOLCHAIN={AC6/CLANG/GCC/IAR)  # Generate build information files
# make step5 TOOLCHAIN={AC6/CLANG/GCC/IAR)  # Build project with Command Line Interface
# make step6 TOOLCHAIN={AC6/CLANG/GCC/IAR)  # Generate disassembly and binary file

PROJECT_NAME   = coremark
HARDWARE_TYPE  = MPS2_CM4_FP
CSOLUTION_FILE = $(PROJECT_NAME).csolution.yml

CSOLUTION_OPTIONS =

CFG_UPDATE_RTE = 1

ifeq ($(CFG_UPDATE_RTE),1)
  CSOLUTION_OPTIONS += update-rte
endif

# TOOLCHAIN = AC6/GCC/CLANG/IAR
TOOLCHAIN = AC6

all: step1 step2 step3 step4 step5 step6

ac6: AC6

AC6:
	cpackget update-index
	csolution list packs -s $(CSOLUTION_FILE) -m > required_packs.txt
	cpackget add -f required_packs.txt
	csolution convert $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --toolchain AC6
	cbuild $(PROJECT_NAME)+$(HARDWARE_TYPE).cprj --toolchain AC6
	make step6_AC6

gcc: GCC

GCC:
	cpackget update-index
	csolution list packs -s $(CSOLUTION_FILE) -m > required_packs.txt
	cpackget add -f required_packs.txt
	csolution convert $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --toolchain GCC
	cbuild $(PROJECT_NAME)+$(HARDWARE_TYPE).cprj --toolchain GCC
	make step6_GCC

clang: CLANG

CLANG:
	cpackget update-index
	csolution list packs -s $(CSOLUTION_FILE) -m > required_packs.txt
	cpackget add -f required_packs.txt
	csolution convert $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --toolchain CLANG
	cbuild $(PROJECT_NAME)+$(HARDWARE_TYPE).cprj --toolchain CLANG
	make step6_CLANG

iar: IAR

IAR:
	cpackget update-index
	csolution list packs -s $(CSOLUTION_FILE) -m > required_packs.txt
	cpackget add -f required_packs.txt
	csolution convert $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --toolchain IAR
	cbuild $(PROJECT_NAME)+$(HARDWARE_TYPE).cprj --toolchain IAR
	make step6_IAR


step1:
	# Optional. If local index file get outdated, you need to run this
	cpackget update-index
	
step2:
	# Identified if any CMSIS-PACK is missing
	csolution list packs -s $(CSOLUTION_FILE) -m > required_packs.txt
	cat required_packs.txt

step3:
	# Add missing CMSIS-PACK
	cpackget add -f required_packs.txt

step4:
	# Generate build information files
	csolution convert $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --toolchain $(TOOLCHAIN)

step5:
	# Build project with Command Line Interface
	cbuild $(PROJECT_NAME)+$(HARDWARE_TYPE).cprj --toolchain $(TOOLCHAIN)

step6: step6_$(TOOLCHAIN)

step6_AC6:
	# Generate disassembly and binary file
	fromelf -c -d -e -s out/$(HARDWARE_TYPE)/$(PROJECT_NAME).axf --output out/$(HARDWARE_TYPE)/list.txt
	fromelf --bin --output out/$(HARDWARE_TYPE)/test.bin out/$(HARDWARE_TYPE)/$(PROJECT_NAME).axf

step6_GCC:
	# Generate disassembly and binary file
	arm-none-eabi-objdump -S out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf > out/$(HARDWARE_TYPE)/list.txt
	arm-none-eabi-objcopy  -O binary out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf out/$(HARDWARE_TYPE)/test.bin

step6_CLANG:
	# Generate disassembly and binary file
	llvm-objdump -S out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf > out/$(HARDWARE_TYPE)/list.txt
	llvm-objcopy  -O binary out/$(HARDWARE_TYPE)/$(PROJECT_NAME).elf out/$(HARDWARE_TYPE)/test.bin

step6_IAR:
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
	
