#include "iostream"
#include "sstream"
#include "cstring"
#include "fstream"
#include "cassert"

#include "INSTR.h"
#include "IO.h"
#include "readable.h"

void execute(const char instructions[], size_t size) {
    size_t instr_ptr = 0;
    size_t stack_ptr = 0;
    char stack[100];
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
            case STORE:
                stack[instructions[instr_ptr + 1]] = instructions[instr_ptr + 2];
                instr_ptr += 3;
                break;
            case LOAD:
                stack[stack_ptr++] = stack[instructions[instr_ptr + 1]];
                instr_ptr += 2;
            case BRANCH:
                if (instructions[instr_ptr + 1] == 1) {
                    instr_ptr = instructions[instr_ptr + 2];
                } else {
                    instr_ptr += 3;
                }
                break;
            case DEBUG:
                std::cout << "[";
                for (auto i = 0; i < stack_ptr; i++) {
                    std::cout << (int) stack[i] << " ";
                }
                std::cout << "]\n";
                instr_ptr++;
                break;
        }
    }
}


int main() {
    char instructions[100];
    size_t size = 100;
    read("../myfile.bin", instructions, size);
    to_readable(instructions, size);
    return 0;
}

