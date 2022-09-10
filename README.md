# vm_cpp
Simple stack based virtual machine written in C++

Instruction set:
- `PUSH byte` - pushes a byte onto the stack
- `POP` - pops the top byte from the stack
- `DUP` - duplicates the top byte of the stack
- `REV` - swaps the top two bytes of the stack
- `DEBUG` - prints the stack to the console
- `STORE` - stores a byte at the specified stack pointer
    - usage = `value [ptr] STORE`
- `LOAD` - loads a byte from a given pointer and pushes it onto the stack
- `BRANCH label` - if the top of the stack is 1, goes to specified label 
- `STACK_PTR` - pushes the current stack_ptr onto the stack
- `STACK_SIZE` - pushes the stack size onto the stack (currently only supports bytes)
- `SUM` - sums the top two bytes of the stack and pushes the result back onto the stack.
- `EQ` - compares the top two bytes of the stack and pushes the result back onto the stack
- `NOT` - compares the top of the stack. if 0 pushes 1, otherwise pushes 0
- `LESS` - compares the top two bytes of the stack and pushes the result back onto the stack.
- `SYS_CALL` - sys_call for Linux. NOT IMPLEMENTED

You can find examples usage in examples/fibonacci.casm file. 
