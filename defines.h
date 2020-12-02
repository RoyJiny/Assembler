#pragma once

#define MAX_AMOUNT_OF_LABELS 100
#define MAX_LABEL_SIZE 50
#define ADDRESS_SIZE 8
#define MAX_LINE_SIZE 500
#define OPCODE_SIZE 2
#define REGISTER_SIZE 1

typedef enum {
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	MUL,
	SLL,
	SRA,
	SRL,
	BEQ,
	BNE,
	BLT,
	BGT,
	BLE,
	BGE,
	JAL,
	LW,
	SW,
	RETI,
	IN,
	OUT,
	HALT
} OPcode;

typedef enum {
	ZERO,
	IMM,
	V0,
	A0,
	A1,
	T0,
	T1,
	T2,
	T3,
	S0,
	S1,
	S2,
	GP,
	SP,
	FP,
	RA
} Register;