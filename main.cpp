#include "iostream"
#include "sstream"
#include "cstring"
#include "fstream"
#include "cassert"
#ifdef __linux__
#include <sys/syscall.h>
#elif _WIN32
// windows code goes here
#endif

#include <unistd.h>

#include "INSTR.h"
#include "IO.h"
#include "readable.h"


void execute(char stack[], const size_t STACK_LIMIT, const char instructions[],  size_t size) {
    size_t instr_ptr = 0;
    size_t stack_ptr = 0;
    while (instr_ptr < size) {
        switch (static_cast<INSTR>(instructions[instr_ptr])) {
            case PUSH:
                stack[stack_ptr++] = instructions[++instr_ptr];
                instr_ptr++;
                break;
            case POP:
                stack_ptr--;
                instr_ptr++;
                break;
            case DUP:
                stack[stack_ptr++] = stack[stack_ptr - 1];
                instr_ptr++;
                break;
            case REV:
                std::swap(stack[stack_ptr - 1], stack[stack_ptr - 2]);
                instr_ptr++;
                break;
            case STORE:
                stack[stack[stack_ptr - 1]] = stack[stack_ptr - 2];
                stack_ptr -= 2;
                instr_ptr++;
                break;
            case LOAD:
                stack[stack_ptr - 1] = stack[stack[stack_ptr - 1]];
                instr_ptr++;
                break;
            case BRANCH:
                if (stack[stack_ptr - 1] == 1) {
                    instr_ptr = instructions[instr_ptr + 1];
                } else {
                    instr_ptr += 2;
                }
                stack_ptr--;
                break;
            case DEBUG:
                std::cout << "[";
                for (auto i = 0; i < stack_ptr; i++) {
                    std::cout << (int) stack[i] << " ";
                }
                std::cout << "]\n";
                instr_ptr++;
                break;
            case STACK_PTR:
                stack[stack_ptr++] = stack_ptr;
                instr_ptr++;
                break;
            case STACK_SIZE:
                stack[stack_ptr++] = STACK_LIMIT;
                instr_ptr++;
                break;
            case SUM:
                stack[stack_ptr - 2] = stack[stack_ptr - 1] + stack[stack_ptr - 2];
                stack_ptr--;
                instr_ptr++;
                break;
            case EQ:
                stack[stack_ptr - 2] = stack[stack_ptr - 1] == stack[stack_ptr - 2];
                stack_ptr--;
                instr_ptr++;
                break;
            case NOT:
                stack[stack_ptr - 1] = stack[stack_ptr - 1] == 0 ? 1 : 0;
                instr_ptr++;
                break;
            case LESS:
                stack[stack_ptr - 2] = stack[stack_ptr - 2] < stack[stack_ptr - 1];
                stack_ptr--;
                instr_ptr++;
                break;
            case SYS_CALL:
                throw -1;
        }
    }
}


int main() {
    const size_t STACK_LIMIT = 100;
    char stack[STACK_LIMIT];
    auto instructions_vec = from_readable("../examples/fibonacci.casm");
    auto instructions = reinterpret_cast<char *>(instructions_vec.data());
//    to_readable(instructions, instructions_vec.size());
    execute(stack, STACK_LIMIT, instructions, instructions_vec.size());
    return 0;
}

