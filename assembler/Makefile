.PHONY: debug

BIN := assembler

GCC := gcc
GCC_ARGS := -Wall -g

GDB := gdb
GDB_ARGS := 

${BIN}: $(wildcard *.c)
	${GCC} ${GCC_ARGS} -o ${BIN} $(wildcard *.c)

debug:
	${GDB} ${GDB_ARGS} ${BIN}
