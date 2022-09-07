#pragma once

void read(const char *filename, char instructions[], size_t &size) {
    std::ifstream input;
    input.open(filename, std::ios::binary);
    assert(input.is_open());
    input.seekg(0, std::ios::end);
    assert(input.tellg() < size);
    size = input.tellg();
    input.seekg(0, std::ios::beg);
    input.read(instructions, size);
}

void write(const char *filename, char instructions[], size_t size) {
    std::ofstream output(filename, std::ios::binary);
    assert(output.is_open());
    output.write(instructions, size);
}