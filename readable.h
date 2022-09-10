#include <vector>
#include <algorithm>
#include <unordered_map>

void to_readable(const char instructions[], size_t size) {
    size_t instr_ptr = 0;
    while (instr_ptr < size) {
        switch (static_cast<INSTR>(instructions[instr_ptr])) {
            case PUSH:
                printf("%d ", instructions[++instr_ptr]);
                instr_ptr++;
                break;
            case POP:
                printf("POP\n");
                instr_ptr++;
                break;
            case DUP:
                printf("DUP\n");
                break;
            case STORE:
                printf("STORE\n");
                instr_ptr++;
                break;
            case LOAD:
                printf("LOAD\n");
                instr_ptr++;
                break;
            case BRANCH:
                printf("BRANCH %d\n", instructions[instr_ptr + 1]);
                instr_ptr += 2;
                break;
            case DEBUG:
                printf("DEBUG\n");
                instr_ptr++;
                break;
            case STACK_PTR:
                printf("STACK_PTR ");
                instr_ptr++;
                break;
            case STACK_SIZE:
                printf("STACK_SIZE ");
                instr_ptr++;
                break;
            case REV:
                printf("REV\n");
                instr_ptr++;
                break;
            case SUM:
                printf("SUM\n");
                instr_ptr++;
                break;
            case EQ:
                printf("EQ\n");
                instr_ptr++;
                break;
            case NOT:
                printf("NOT\n");
                instr_ptr++;
                break;
            case LESS:
                printf("LESS\n");
                instr_ptr++;
                break;
            case SYS_CALL:
                printf("SYS_CALL\n");
                instr_ptr++;
                break;
        }
    }
}

std::vector<std::string> split(std::string s, const char *del) {
    auto ind = -1;
    size_t new_ind;
    std::vector<std::string> result;
    while (true) {
        new_ind = s.find(del, ind + 1);
        if (new_ind == std::string::npos) {
            if (ind + 1 >= s.size()) {
                break;
            }
            auto substr = s.substr(ind + 1);
            if (substr != " " && !substr.empty()) {
                result.push_back(substr);
            }
            break;
        }
        auto substr = s.substr(ind + 1, new_ind - ind - 1);
        if (substr != " " && !substr.empty()) {
            result.push_back(substr);
        }
        ind = new_ind;
    }
    return result;
}

std::string remove(std::string input, std::string char_list) {
    std::stringstream ss;
    for (auto &c: input) {
        bool to_add = true;
        for (auto &removable_c: char_list) {
            if (removable_c == c) {
                to_add = false;
                break;
            }
        }
        if (!to_add) continue;
        ss << c;
    }
    return ss.str();
}

bool is_number(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::vector<char> from_readable(const char *filename) {
    std::ifstream file(filename);
    assert(file.is_open());
    std::vector<std::string> input{};
    std::string line;
    while (getline(file, line)) {
        auto ind = line.find("//");
        if (ind != std::string::npos) {
            line = line.substr(0, ind);
        }
        auto after_split = split(line, " ");
        input.insert(input.end(), after_split.begin(), after_split.end());
    }
    file.close();
    std::transform(input.begin(), input.end(), input.begin(),
                   [](auto &it) { return remove(it, "[()]"); }
    );
    std::unordered_map<std::string, size_t> map;
    for (auto i = 0, skip_counter = 0; i < input.size(); i++) {
        auto s = input[i];
        if (s.empty()) {
            skip_counter++;
            continue;
        }
        if (is_number(s)) { // it's a PUSH which takes two instructions but one token, so we decrease skip counter
            skip_counter--;
            continue;
        }
        if (s[s.size() - 1] == ':') {
            map.insert({s.substr(0, s.size() - 1), i - skip_counter});
            skip_counter++;
        }
    }

    size_t i = 0;
    std::vector<char> instructions;
    try {
        while (i < input.size()) {
            auto operand = input[i];
//            operand = remove(operand, "[()]");
            if (operand.empty()) continue;
            if (operand == "POP") {
                instructions.push_back(BRANCH);
                i++;
            } else if (operand == "DEBUG") {
                instructions.push_back(DEBUG);
                i++;
            } else if (operand == "STORE") {
                instructions.push_back(STORE);
                i++;
            } else if (operand == "LOAD") {
                instructions.push_back(LOAD);
                i++;
            } else if (operand == "BRANCH") {
                instructions.push_back(BRANCH);
                instructions.push_back(map.at(input[++i]));
                i++;
            } else if (operand == "SUM") {
                instructions.push_back(SUM);
                i++;
            } else if (operand == "LESS") {
                instructions.push_back(LESS);
                i++;
            } else if (operand[operand.size() - 1] == ':') {
                i++;
            } else {
                instructions.push_back(PUSH);
                instructions.push_back(std::stoi(operand));
                i++;
            }
        }
    } catch (std::invalid_argument &argument) {
        std::cout << "ERROR! " << argument.what() << "\n" << input[i] << "\nINSTRUCTIONS DEBUG:";
        to_readable(reinterpret_cast<char *>(instructions.data()), instructions.size());
    }
    return instructions;
}
