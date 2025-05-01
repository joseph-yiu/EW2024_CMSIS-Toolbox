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
HARDWARE_LIST  = MPS2_CM0 \
 MPS2_CM0plus    \
 MPS2_CM3        \
 MPS2_CM4        \
 MPS2_CM4_FP     \
 MPS2_CM7        \
 MPS2_CM7_SP     \
 MPS2_CM7_DP     \
 MPS2_CM23       \
 MPS2_CM33       \
 MPS2_CM33_FP    \
 MPS3-Corstone-300 \
 MPS3-Corstone-310

CSOLUTION_FILE = $(PROJECT_NAME).csolution.yml

CSOLUTION_OPTIONS =

CFG_UPDATE_RTE = 1

ifeq ($(CFG_UPDATE_RTE),1)
  CSOLUTION_OPTIONS += --update-rte
endif

# TOOLCHAIN = AC6/GCC/CLANG/IAR
TOOLCHAIN = AC6

all: step1 step2 step3 

ac6: AC6

AC6:
	cpackget update-index
	for this_hardware in $(HARDWARE_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $(PROJECT_NAME)+$$this_hardware --packs --toolchain AC6  ;\
	done
	make step3_AC6

gcc: GCC

GCC:
	cpackget update-index
	for this_hardware in $(HARDWARE_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $(PROJECT_NAME)+$$this_hardware --packs --toolchain GCC  ;\
	done
	make step3_GCC

clang: CLANG

CLANG:
	cpackget update-index
	for this_hardware in $(HARDWARE_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $(PROJECT_NAME)+$$this_hardware --packs --toolchain CLANG  ;\
	done
	make step6=3_CLANG

iar: IAR

IAR:
	cpackget update-index
	for this_hardware in $(HARDWARE_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $(PROJECT_NAME)+$$this_hardware --packs --toolchain IAR  ;\
	done
	make step3_IAR

step1:
	# Optional. If local index file get outdated, you need to run this
	cpackget update-index
	
step2:
	# Build project with Command Line Interface
	for this_hardware in $(HARDWARE_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $(PROJECT_NAME)+$$this_hardware --packs --toolchain $(TOOLCHAIN)  ;\
	done

step3: step3_$(TOOLCHAIN)

step3_AC6:
	# Generate disassembly and binary file
	for this_hardware in $(HARDWARE_LIST) ; do \
	 fromelf -c -d -e -s out/$$this_hardware/$(PROJECT_NAME).axf --output out/$$this_hardware/list.txt ;\
	 fromelf --bin --output out/$$this_hardware/test.bin out/$$this_hardware/$(PROJECT_NAME).axf ;\
	done

step3_GCC:
	# Generate disassembly and binary file
	for this_hardware in $(HARDWARE_LIST) ; do \
	 arm-none-eabi-objdump -S out/$$this_hardware/$(PROJECT_NAME).elf > out/$$this_hardware/list.txt ;\
	 arm-none-eabi-objcopy  -O binary out/$$this_hardware/$(PROJECT_NAME).elf out/$$this_hardware/test.bin ;\
	done

step3_CLANG:
	# Generate disassembly and binary file
	for this_hardware in $(HARDWARE_LIST) ; do \
	 llvm-objdump -S out/$$this_hardware/$(PROJECT_NAME).elf > out/$$this_hardware/list.txt ;\
	 llvm-objcopy  -O binary out/$$this_hardware/$(PROJECT_NAME).elf out/$$this_hardware/test.bin ;\
	done

step3_IAR:
	# Generate disassembly and binary file
	for this_hardware in $(HARDWARE_LIST) ; do \
	  ielfdumparm --all --source out/$$this_hardware/$(PROJECT_NAME).out --output out/$$this_hardware/list.txt ;\
	  ielftool --bin out/$$this_hardware/$(PROJECT_NAME).out out/$$this_hardware/test.bin ;\
	done


clean:
	@test -f ?.cbuild-idx.yml || rm -rf *.cbuild-idx.yml
	@test -f ?.cbuild-pack.yml || rm -rf *.cbuild-pack.yml
	@test -f ?.cbuild.yml || rm -rf *.cbuild.yml
	@test -f ?.cprj || rm -rf *.cprj
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
	
