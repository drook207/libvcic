# =============================================================================
# Build switches — all user-facing options for the libvcic project. Include this module before
# add_subdirectory() calls.
# =============================================================================

# --- What to build -----------------------------------------------------------
option(VCIC_BUILD_GUI "Build the GUI application" OFF)
option(VCIC_BUILD_TESTS "Build unit tests" ON)
option(VCIC_BUILD_BENCHMARKS "Build microbenchmarks" OFF)
option(VCIC_BUILD_EXAMPLES "Build example applications" OFF)

# --- Code quality tools ------------------------------------------------------
option(VCIC_ENABLE_CLANG_TIDY "Run clang-tidy during compilation" OFF)
option(VCIC_WARNINGS_AS_ERRORS "Treat all compiler warnings as errors" OFF)

# --- Instrumentation ---------------------------------------------------------
option(VCIC_ENABLE_SANITIZERS "Enable AddressSanitizer + UndefinedBehaviorSanitizer" OFF)
option(VCIC_ENABLE_COVERAGE "Enable gcov/lcov code-coverage instrumentation" OFF)
option(VCIC_ENABLE_IPO "Enable interprocedural (link-time) optimisation" OFF)

# =============================================================================
# Implement options that affect the global build environment immediately. (Per-target options are
# applied inside each subdirectory.)
# =============================================================================

# --- Interprocedural optimisation --------------------------------------------
if(VCIC_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT _vcic_ipo_ok OUTPUT _vcic_ipo_out)
    if(_vcic_ipo_ok)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    else()
        message(WARNING "VCIC: IPO requested but not supported — ${_vcic_ipo_out}")
        set(VCIC_ENABLE_IPO
            OFF
            CACHE BOOL "" FORCE)
    endif()
    unset(_vcic_ipo_ok)
    unset(_vcic_ipo_out)
endif()

# --- clang-tidy --------------------------------------------------------------
if(VCIC_ENABLE_CLANG_TIDY)
    find_program(VCIC_CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
    set(CMAKE_CXX_CLANG_TIDY "${VCIC_CLANG_TIDY_EXE}"
                             "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
endif()

# --- Sanitizers --------------------------------------------------------------
if(VCIC_ENABLE_SANITIZERS)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(WARNING "VCIC: sanitizers are only supported with GCC and Clang")
        set(VCIC_ENABLE_SANITIZERS
            OFF
            CACHE BOOL "" FORCE)
    else()
        add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

# --- Coverage ----------------------------------------------------------------
if(VCIC_ENABLE_COVERAGE)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(WARNING "VCIC: coverage is only supported with GCC and Clang")
        set(VCIC_ENABLE_COVERAGE
            OFF
            CACHE BOOL "" FORCE)
    else()
        add_compile_options(--coverage -O0 -g)
        add_link_options(--coverage)
    endif()
endif()

# --- Warnings as errors ------------------------------------------------------
if(VCIC_WARNINGS_AS_ERRORS)
    if(MSVC)
        add_compile_options(/WX)
    else()
        add_compile_options(-Werror)
    endif()
endif()
