set(ARCH "aarch64")
set(CPUVAR aarch64le)

set(QNX_HOST "$ENV{QNX_HOST}")
set(QNX_TARGET "$ENV{QNX_TARGET}")

message(STATUS "using QNX_HOST ${QNX_HOST}")
message(STATUS "using QNX_TARGET ${QNX_TARGET}")
message(STATUS "using CPUVAR ${CPUVAR}")
message(STATUS "using ARCH ${ARCH}")

set(QNX TRUE)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SYSTEM_NAME QNX)

set(CMAKE_C_COMPILER ${QNX_HOST}/usr/bin/qcc)
set(CMAKE_CXX_COMPILER ${QNX_HOST}/usr/bin/q++)

set(CMAKE_SYSTEM_PROCESSOR "${CPUVAR}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Vgcc_nto${CMAKE_SYSTEM_PROCESSOR} ${EXTRA_CMAKE_C_FLAGS}" CACHE STRING "c_flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Vgcc_nto${CMAKE_SYSTEM_PROCESSOR} -std=c++14 -Y_cxx -DTIXML_USE_STL ${EXTRA_CMAKE_CXX_FLAGS}" CACHE STRING "cxx_flags")

set(CMAKE_AS "${QNX_HOST}/usr/bin/nto${ARCH}-as${HOST_EXECUTABLE_SUFFIX}" CACHE PATH "assembler")
set(CMAKE_AR "${QNX_HOST}/usr/bin/nto${ARCH}-ar${HOST_EXECUTABLE_SUFFIX}" CACHE PATH "archiver")
set(CMAKE_RANLIB "${QNX_HOST}/usr/bin/nto${ARCH}-ranlib${HOST_EXECUTABLE_SUFFIX}" CACHE PATH "ranlib")
set(CMAKE_STRIP "${QNX_HOST}/usr/bin/nto${ARCH}-strip${HOST_EXECUTABLE_SUFFIX}" CACHE PATH "strip")
set(EXTRA_CMAKE_LINKER_FLAGS "${EXTRA_CMAKE_LINKER_FLAGS} -lregex")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_CMAKE_LINKER_FLAGS} -stdlib=libc++" CACHE STRING "exe_linker_flags")
set(THREADS_PTHREAD_ARG "0" CACHE STRING "Result from TRY_RUN" FORCE)
