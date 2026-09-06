cmake_minimum_required(VERSION 3.22)

project(ALFI_ASM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ALFI_ARCH "x86_64" CACHE STRING "Target architecture")
set_property(CACHE ALFI_ARCH PROPERTY STRINGS x86_64 rv64gv)

set(ALFI_COMPILER "gcc" CACHE STRING "Compiler")
set_property(CACHE ALFI_COMPILER PROPERTY STRINGS gcc clang)

set(ALFI_PROFILE "O3" CACHE STRING "Optimization profile")
set_property(CACHE ALFI_PROFILE PROPERTY STRINGS O0 O2 O3 Ofast)

option(ALFI_OPENMP "Enable OpenMP" OFF)


if(ALFI_ARCH STREQUAL "x86_64")
	set(ARCH_FLAGS
		-march=x86-64
	)
elseif(ALFI_ARCH STREQUAL "rv64gv")
	set(ARCH_FLAGS
		-march=rv64gv
		-mabi=lp64d
	)

	if(ALFI_COMPILER STREQUAL "clang")
		list(APPEND ARCH_FLAGS
			--target=riscv64-linux-gnu
		)
	endif()
else()
	message(FATAL_ERROR "Unsupported ALFI_ARCH: ${ALFI_ARCH}")
endif()


if(ALFI_PROFILE STREQUAL "O0")
	set(OPT_FLAGS
		-O0
	)
elseif(ALFI_PROFILE STREQUAL "O2")
	set(OPT_FLAGS
		-O2
	)
elseif(ALFI_PROFILE STREQUAL "O3")
	set(OPT_FLAGS
		-O3
	)
elseif(ALFI_PROFILE STREQUAL "Ofast")
	set(OPT_FLAGS
		-Ofast
		-fno-finite-math-only
	)
else()
	message(FATAL_ERROR "Unsupported ALFI_PROFILE: ${ALFI_PROFILE}")
endif()


set(OPENMP_FLAGS)

if(ALFI_OPENMP)
	list(APPEND OPENMP_FLAGS
		-fopenmp
	)
endif()


set(COMMON_FLAGS
	-std=c++17
	-Wall
	-Wextra
	-pedantic
	${ARCH_FLAGS}
	${OPT_FLAGS}
	${OPENMP_FLAGS}
	-I${CMAKE_SOURCE_DIR}
)


set(OPT_REMARK_FLAGS)

if(ALFI_COMPILER STREQUAL "clang")
	list(APPEND OPT_REMARK_FLAGS
		-Rpass=loop-vectorize
		-Rpass-missed=loop-vectorize
		-Rpass-analysis=loop-vectorize
		-Rpass=inline
		-Rpass-missed=inline
	)
endif()


set(GCC_OPT_FLAGS)

if(ALFI_COMPILER STREQUAL "gcc")
	list(APPEND GCC_OPT_FLAGS
		-fopt-info-vec-optimized
		-fopt-info-vec-missed
	)
endif()


set(OBJECT_FILE "${CMAKE_BINARY_DIR}/main.o")
set(ASSEMBLY_FILE "${CMAKE_BINARY_DIR}/main.s")
set(OBJDUMP_FILE "${CMAKE_BINARY_DIR}/main.objdump.s")
set(IR_FILE "${CMAKE_BINARY_DIR}/main.ll")
set(OPT_FILE "${CMAKE_BINARY_DIR}/main.opt.txt")


add_custom_command(
	OUTPUT "${OBJECT_FILE}"
	COMMAND
		${CMAKE_CXX_COMPILER}
		${COMMON_FLAGS}
		${OPT_REMARK_FLAGS}
		${GCC_OPT_FLAGS}
		-c
		"${CMAKE_SOURCE_DIR}/main.cpp"
		-o "${OBJECT_FILE}"
	DEPENDS
		"${CMAKE_SOURCE_DIR}/main.cpp"
	VERBATIM
)


if(ALFI_COMPILER STREQUAL "clang")

	add_custom_command(
		OUTPUT "${ASSEMBLY_FILE}" "${OPT_FILE}"
		COMMAND
			sh -c
			"\"${CMAKE_CXX_COMPILER}\" ${COMMON_FLAGS} \
			${OPT_REMARK_FLAGS} \
			-S \"${CMAKE_SOURCE_DIR}/main.cpp\" \
			-o \"${ASSEMBLY_FILE}\" \
			2> \"${OPT_FILE}\""
		DEPENDS
			"${CMAKE_SOURCE_DIR}/main.cpp"
		VERBATIM
	)

	add_custom_command(
		OUTPUT "${IR_FILE}"
		COMMAND
			${CMAKE_CXX_COMPILER}
			${COMMON_FLAGS}
			-S
			-emit-llvm
			"${CMAKE_SOURCE_DIR}/main.cpp"
			-o "${IR_FILE}"
		DEPENDS
			"${CMAKE_SOURCE_DIR}/main.cpp"
		VERBATIM
	)

else()

	add_custom_command(
		OUTPUT "${ASSEMBLY_FILE}"
		COMMAND
			${CMAKE_CXX_COMPILER}
			${COMMON_FLAGS}
			${GCC_OPT_FLAGS}
			-fverbose-asm
			-S
			"${CMAKE_SOURCE_DIR}/main.cpp"
			-o "${ASSEMBLY_FILE}"
		DEPENDS
			"${CMAKE_SOURCE_DIR}/main.cpp"
		VERBATIM
	)

endif()


add_custom_command(
	OUTPUT "${OBJDUMP_FILE}"
	COMMAND
		sh -c
		"\"${CMAKE_OBJDUMP}\" -d -S -C \"${OBJECT_FILE}\" > \"${OBJDUMP_FILE}\""
	DEPENDS
		"${OBJECT_FILE}"
	VERBATIM
)


if(ALFI_COMPILER STREQUAL "clang")

	add_custom_target(asm ALL
		DEPENDS
			"${OBJECT_FILE}"
			"${ASSEMBLY_FILE}"
			"${OBJDUMP_FILE}"
			"${IR_FILE}"
			"${OPT_FILE}"
	)

else()

	add_custom_target(asm ALL
		DEPENDS
			"${OBJECT_FILE}"
			"${ASSEMBLY_FILE}"
			"${OBJDUMP_FILE}"
	)

endif()