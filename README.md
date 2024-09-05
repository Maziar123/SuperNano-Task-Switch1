# SuperNano-Task-Switch1
Goal of super-nano Multi-Platform Task Switching System (current x64 & cortex-m)

 **Build and revise are under way!**

## Overview

The Multi-Platform Task Switching System is a lightweight, efficient, and portable implementation of a cooperative multitasking system. It supports x64, Cortex-M4F, and Cortex-M7F architectures, making it suitable for a wide range of applications from desktop software to embedded systems.
We try to use **modern C++20** features, **compatibility**, and **avoid STD** or fat libs.

### Key Features

- **Cross-Platform Compatibility**: Runs on x64, Cortex-M4F, and Cortex-M7F architectures
- **Lightweight**: Minimal overhead, suitable for resource-constrained systems
- **Cooperative Multitasking**: Efficient task switching without the need for a full RTOS
- **Easy Integration**: Simple API for creating and managing tasks
- **Debuggable**: Optional debug output for development and troubleshooting
- **Modern Build System**: Uses CMake for easy compilation across different platforms

## Architecture

The system consists of the following key components:

1. **Task**: Base class for defining individual tasks
2. **TaskManager**: Manages task creation, scheduling, and switching
3. **Platform-Specific Implementations**: Separate implementations for x64, Cortex-M4F, and Cortex-M7F

### File Structure

```
project_root/
├── CMakeLists.txt
├── include/
│   └── task_system.hpp
├── src/
│   ├── task_system.cpp
│   ├── task_system_x64.cpp
│   ├── task_system_cortex_m4f.cpp
│   ├── task_system_cortex_m7f.cpp
│   └── main.cpp
└── linker_script.ld (for ARM builds)
```

## Setup and Installation

### Prerequisites

- CMake (version 3.15 or higher)
- For x64: A modern C++ compiler (GCC, Clang, or MSVC)
- For ARM: arm-none-eabi-gcc toolchain

### Installation Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/task-switching-system.git
   cd task-switching-system
   ```

2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

3. Configure the project using CMake (see Build Process for platform-specific commands)

4. Build the project:
   ```bash
   cmake --build .
   ```

5. (Optional) Install the built binaries:
   ```bash
   cmake --install .
   ```

## Build Process

### For x64 Platforms

```bash
cmake ..
cmake --build .
```

### For Cortex-M4F

```bash
cmake -DCMAKE_SYSTEM_NAME=Generic -DCMAKE_SYSTEM_PROCESSOR=arm -DARM_CPU=cortex-m4f -DCMAKE_TOOLCHAIN_FILE=path/to/arm-none-eabi-gcc.cmake ..
cmake --build .
```

### For Cortex-M7F

```bash
cmake -DCMAKE_SYSTEM_NAME=Generic -DCMAKE_SYSTEM_PROCESSOR=arm -DARM_CPU=cortex-m7f -DCMAKE_TOOLCHAIN_FILE=path/to/arm-none-eabi-gcc.cmake ..
cmake --build .
```

### Enabling Debug Output

Add `-DENABLE_DEBUG=ON` to your CMake configuration command to enable debug output.

## Usage

### Creating a Task

1. Include the necessary header:
   ```cpp
   #include "task_system.hpp"
   ```

2. Define your task by inheriting from the `Task` class:
   ```cpp
   class MyTask : public Task {
   public:
       MyTask() : Task(1) {} // 1 is the task ID

       void run() override {
           while (true) {
               // Your task logic here
               TaskManager::yield();
           }
       }
   };
   ```

3. Create an instance of your task:
   ```cpp
   MyTask myTask;
   ```

### Setting Up the Task Manager

In your main function:

```cpp
int main() {
    TaskManager taskManager;
    taskManager.add_task(&myTask);
    taskManager.start();
    return 0;
}
```

### Yielding Control

Within your task's `run()` method, use `TaskManager::yield()` to cooperatively give up control:

```cpp
TaskManager::yield();
```

## Debugging

When compiled with `-DENABLE_DEBUG=ON`, the system will output debug information. You can add your own debug statements using the `DEBUG_PRINT` macro:

```cpp
DEBUG_PRINT("Task %u is running", task_id);
```

## Performance Considerations

- The system uses cooperative multitasking, so tasks must yield voluntarily.
- On ARM platforms, context switching is optimized using assembly code.
- Avoid long-running operations without yielding to ensure responsive task switching.

## Troubleshooting

1. **Compilation Errors on ARM**: Ensure you're using the correct toolchain file and have the arm-none-eabi-gcc toolchain installed.

2. **Tasks Not Switching**: Check that your tasks are calling `TaskManager::yield()` regularly.

3. **Unexpected Behavior on ARM**: Verify that the linker script is correct for your specific microcontroller.

4. **Debug Output Not Showing**: Confirm that you've built with `-DENABLE_DEBUG=ON`.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.



## License

This project is licensed under the MIT License - see the LICENSE file for details.
