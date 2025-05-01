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

PROJECT_NAME   = coremark-pro
HARDWARE_TYPE  = MPS2_CM7_DP

#TEST_LIST = core            \
#  cjpeg-rose7-preset        \
#  linear_alg-mid-100x100-sp \
#  loops-all-mid-10k-sp      \
#  nnet_test                 \
#  parser-125k               \
#  radix2-big-64k            \
#  sha-test                  \
#  zip-test

# Exclude zip-test - zip lib contains K&R C (not modern C standard)
# This does not work with IAR compiler
TEST_LIST = core            \
  cjpeg-rose7-preset        \
  linear_alg-mid-100x100-sp \
  loops-all-mid-10k-sp      \
  nnet_test                 \
  parser-125k               \
  radix2-big-64k            \
  sha-test
#  zip-test

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
	for this_test in $(TEST_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $$this_test+$(HARDWARE_TYPE) --packs --toolchain AC6  ;\
	done
	make step3_AC6

gcc: GCC

GCC:
	cpackget update-index
	for this_test in $(TEST_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $$this_test+$(HARDWARE_TYPE) --packs --toolchain GCC  ;\
	done
	make step3_GCC

clang: CLANG

CLANG:
	cpackget update-index
	for this_test in $(TEST_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $$this_test+$(HARDWARE_TYPE) --packs --toolchain CLANG  ;\
	done
	make step3_CLANG

iar: IAR

IAR:
	cpackget update-index
	for this_test in $(TEST_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $$this_test+$(HARDWARE_TYPE) --packs --toolchain IAR  ;\
	done
	make step3_IAR

step1:
	# Optional. If local index file get outdated, you need to run this
	cpackget update-index
	

step2:
	# Build project with Command Line Interface
	for this_test in $(TEST_LIST) ; do \
		cbuild $(CSOLUTION_FILE) $(CSOLUTION_OPTIONS) --context $$this_test+$(HARDWARE_TYPE) --packs --toolchain $(TOOLCHAIN)  ;\
	done

step3: step3_$(TOOLCHAIN)

step3_AC6:
	# Generate disassembly and binary file
	for this_test in $(TEST_LIST) ; do \
	 fromelf -c -d -e -s out/$$this_test/$(HARDWARE_TYPE)/$$this_test.axf --output out/$$this_test/$(HARDWARE_TYPE)/list.txt ;\
	 fromelf --bin --output out/$$this_test/$(HARDWARE_TYPE)/test.bin out/$$this_test/$(HARDWARE_TYPE)/$$this_test.axf ;\
	done

step3_GCC:
	# Generate disassembly and binary file
	for this_test in $(TEST_LIST) ; do \
	 arm-none-eabi-objdump -S out/$$this_test/$(HARDWARE_TYPE)/$$this_test.elf > out/$$this_test/$(HARDWARE_TYPE)/list.txt ;\
	 arm-none-eabi-objcopy  -O binary out/$$this_test/$(HARDWARE_TYPE)/$$this_test.elf out/$$this_test/$(HARDWARE_TYPE)/test.bin ;\
	done

step3_CLANG:
	# Generate disassembly and binary file
	for this_test in $(TEST_LIST) ; do \
	 llvm-objdump -S out/$$this_test/$(HARDWARE_TYPE)/$$this_test.elf > out/$$this_test/$(HARDWARE_TYPE)/list.txt ;\
	 llvm-objcopy  -O binary out/$$this_test/$(HARDWARE_TYPE)/$$this_test.elf out/$$this_test/$(HARDWARE_TYPE)/test.bin ;\
	done

step3_IAR:
	# Generate disassembly and binary file
	for this_test in $(TEST_LIST) ; do \
	  ielfdumparm --all --source out/$$this_test/$(HARDWARE_TYPE)/$$this_test.out --output out/$$this_test/$(HARDWARE_TYPE)/list.txt ;\
	  ielftool --bin out/$$this_test/$(HARDWARE_TYPE)/$$this_test.out out/$$this_test/$(HARDWARE_TYPE)/test.bin ;\
	done

clean:
	@test -f ?.cbuild-idx.yml || rm -rf *.cbuild-idx.yml
	@test -f ?.cbuild-pack.yml || rm -rf *.cbuild-pack.yml
	@rm -rf proj_*/RTE
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
	@if [ -d proj_core/RTE ] ; then \
	  rm -rf proj_core/RTE ; \
	fi
	@test -f proj_core/?.cbuild.yml                      || rm -rf proj_core/*.cbuild.yml
	@test -f proj_core/?.cprj                            || rm -rf proj_core/*.cprj
	@test -f proj_cjpeg-rose7-preset/?.cbuild.yml        || rm -rf proj_cjpeg-rose7-preset/*.cbuild.yml
	@test -f proj_cjpeg-rose7-preset/?.cprj              || rm -rf proj_cjpeg-rose7-preset/*.cprj
	@test -f proj_linear_alg-mid-100x100-sp/?.cbuild.yml || rm -rf proj_linear_alg-mid-100x100-sp/*.cbuild.yml
	@test -f proj_linear_alg-mid-100x100-sp/?.cprj       || rm -rf proj_linear_alg-mid-100x100-sp/*.cprj
	@test -f proj_loops-all-mid-10k-sp/?.cbuild.yml      || rm -rf proj_loops-all-mid-10k-sp/*.cbuild.yml
	@test -f proj_loops-all-mid-10k-sp/?.cprj            || rm -rf proj_loops-all-mid-10k-sp/*.cprj
	@test -f proj_nnet_test/?.cbuild.yml                 || rm -rf proj_nnet_test/*.cbuild.yml
	@test -f proj_nnet_test/?.cprj                       || rm -rf proj_nnet_test/*.cprj
	@test -f proj_parser-125k/?.cbuild.yml               || rm -rf proj_parser-125k/*.cbuild.yml
	@test -f proj_parser-125k/?.cprj                     || rm -rf proj_parser-125k/*.cprj
	@test -f proj_radix2-big-64k/?.cbuild.yml            || rm -rf proj_radix2-big-64k/*.cbuild.yml
	@test -f proj_radix2-big-64k/?.cprj                  || rm -rf proj_radix2-big-64k/*.cprj
	@test -f proj_sha-test/?.cbuild.yml                  || rm -rf proj_sha-test/*.cbuild.yml
	@test -f proj_sha-test/?.cprj                        || rm -rf proj_sha-test/*.cprj
	@test -f proj_zip-test/?.cbuild.yml                  || rm -rf proj_zip-test/*.cbuild.yml
	@test -f proj_zip-test/?.cprj                        || rm -rf proj_zip-test/*.cprj
	
