#include "task_system.hpp"

void TaskManager::yield() {
    // Trigger PendSV for context switch
    *((volatile uint32_t*)0xE000ED04) = 0x10000000;
}

void TaskManager::switch_context(void* current_sp) {
    uint32_t* sp = static_cast<uint32_t*>(current_sp);
    
    // Save current context
    tasks[current_task]->get_stack_ptr()[15] = sp[6]; // PC
    tasks[current_task]->get_stack_ptr()[14] = sp[5]; // LR
    for (int i = 0; i < 8; ++i) {
        tasks[current_task]->get_stack_ptr()[i] = sp[i];
    }

    // Switch to next task
    uint32_t prev_task = current_task;
    current_task = (current_task + 1) % task_count;
    DEBUG_PRINT("Switching from Task %u to Task %u", tasks[prev_task]->get_id(), tasks[current_task]->get_id());

    // Load next context
    for (int i = 0; i < 8; ++i) {
        sp[i] = tasks[current_task]->get_stack_ptr()[i];
    }
    sp[5] = tasks[current_task]->get_stack_ptr()[14]; // LR
    sp[6] = tasks[current_task]->get_stack_ptr()[15]; // PC
}

extern "C" void PendSV_Handler() {
    // Context switching will be handled by the assembly code
}

// Assembly function for context switching
__asm void switch_context_asm() {
    IMPORT task_manager
    PUSH {R4-R11, LR}
    MOV R0, SP
    BL task_manager.switch_context
    POP {R4-R11, PC}
}
