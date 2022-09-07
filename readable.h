#include <vector>

void to_readable(const char instructions[], size_t size) {
    size_t instr_ptr = 0;
    while (instr_ptr < size) {
        switch (static_cast<INSTR>(instructions[instr_ptr])) {
            case PUSH:
                printf("PUSH %d\n", instructions[++instr_ptr]);
                instr_ptr++;
                break;
            case POP:
                printf("POP\n");
                instr_ptr++;
                break;
            case STORE:
                printf("STORE [%d] %d\n", instructions[instr_ptr + 1], instructions[instr_ptr + 2]);
                instr_ptr += 3;
                break;
            case LOAD:
                printf("LOAD %d\n", instructions[instr_ptr + 1]);
                instr_ptr += 2;
            case BRANCH:
                printf("BRANCH %d : %d\n", instructions[instr_ptr + 1], instructions[instr_ptr + 2]);
                instr_ptr += 3;
                break;
            case DEBUG:
                printf("DEBUG\n");
                instr_ptr++;
                break;
            default:;
        }
    }
}

void from_readable(std::vector <std::string> &input) {
    size_t i = 0;
    std::vector<char> instructions;
    while (i < input.size()) {
        auto operand = input[i];
        if (operand == "PUSH") {
            instructions.push_back(PUSH);
            instructions.push_back(std::stoi(input[i + 1]));
            i += 2;
        } else if (operand == "POP") {
            instructions.push_back(BRANCH);
            i++;
        } else if (operand == "DEBUG") {
            instructions.push_back(DEBUG);
            i++;
        } else if (operand == "STORE") {
            instructions.push_back(STORE);
            assert(input[i + 1] == "[");
            instructions.push_back(std::stoi(input[i + 2]));
            assert(input[i + 3] == "]");
            instructions.push_back(std::stoi(input[i + 4]));
            i += 5;
        } else if (operand == "LOAD") {
            instructions.push_back(LOAD);
            instructions.push_back(std::stoi(input[i + 1]));
            i += 2;
        } else if (operand == "BRANCH") {
            instructions.push_back(BRANCH);
            instructions.push_back(std::stoi(input[i + 1]));
            assert(input[i + 2] == ":");
            instructions.push_back(std::stoi(input[i + 3]));
            i += 4;
        }
    }
}
