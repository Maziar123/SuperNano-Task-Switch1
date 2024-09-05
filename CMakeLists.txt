cmake_minimum_required(VERSION 3.15)
project(TaskSwitchingSystem VERSION 1.0.0 LANGUAGES CXX ASM)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the main executable
add_executable(task_system
    src/task_system.cpp
    src/main.cpp
)

# Common include directories
target_include_directories(task_system PRIVATE include)

# Debug option
option(ENABLE_DEBUG "Enable debug output" OFF)
if(ENABLE_DEBUG)
    target_compile_definitions(task_system PRIVATE IS_DEBUG)
endif()

# Platform-specific configurations
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # x64 configuration
    target_sources(task_system PRIVATE src/task_system_x64.cpp)
    target_compile_definitions(task_system PRIVATE PLATFORM_X64)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Generic" AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    # ARM configuration
    if(NOT DEFINED ARM_CPU)
        message(FATAL_ERROR "ARM_CPU must be defined. Use -DARM_CPU=cortex-m4f or -DARM_CPU=cortex-m7f")
    endif()

    if(ARM_CPU STREQUAL "cortex-m4f")
        target_sources(task_system PRIVATE src/task_system_cortex_m4f.cpp)
        target_compile_definitions(task_system PRIVATE PLATFORM_CORTEX_M4F)
        set(CPU_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
    elseif(ARM_CPU STREQUAL "cortex-m7f")
        target_sources(task_system PRIVATE src/task_system_cortex_m7f.cpp)
        target_compile_definitions(task_system PRIVATE PLATFORM_CORTEX_M7F)
        set(CPU_FLAGS "-mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16")
    else()
        message(FATAL_ERROR "Unsupported ARM_CPU: ${ARM_CPU}")
    endif()

    target_compile_options(task_system PRIVATE ${CPU_FLAGS})
    target_link_options(task_system PRIVATE ${CPU_FLAGS})

    # ARM-specific linker script
    set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker_script.ld")
    target_link_options(task_system PRIVATE -T${LINKER_SCRIPT})

    # Embedded specific options
    target_compile_options(task_system PRIVATE
        -fno-exceptions
        -fno-rtti
        -fno-use-cxa-atexit
        -fno-threadsafe-statics
    )
    target_link_options(task_system PRIVATE
        -nostartfiles
        -specs=nano.specs
        -specs=nosys.specs
        -Wl,--gc-sections
    )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Install rules
install(TARGETS task_system
    RUNTIME DESTINATION bin
)

# Enable testing
enable_testing()

# Add a simple test
add_test(NAME task_system_test COMMAND task_system)
