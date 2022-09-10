#pragma once

enum INSTR {
    PUSH,
    POP,
    DUP,
    REV,
    DEBUG,
    STORE,
    LOAD,
    BRANCH,
    STACK_PTR,
    STACK_SIZE,
    SUM,
    EQ,
    NOT,
    LESS,
    SYS_CALL
};