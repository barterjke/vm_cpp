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

Fibonacci exampel:
```
0       // count
11      // terms
0       // n1
1       // n2

1 BRANCH before_loop

loop:
    [2] LOAD
    [3] LOAD
    SUM                             // n1 + n2
    (3 LOAD) [2] STORE              // n1 = n2
    [3] STORE                       // n2 = nth
    ([0] LOAD 1 SUM) [0] STORE      // count += 1

before_loop:
    0 LOAD 1 LOAD
    LESS // count < terms
    BRANCH loop
DEBUG
```
