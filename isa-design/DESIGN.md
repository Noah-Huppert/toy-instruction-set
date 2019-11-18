# Toy Instruction Set Architecture
Design of ISA.

# Table Of Contents
- [Data](#data)
- [Assembly Syntax](#assembly-syntax)
- [Bit Pattern](#bit-pattern)
- [Registers](#registers)
- [Addressing Modes](#addressing-modes)
- [Signedness and Types](#signedness-and-types)
- [Status Codes](#status-codes)
- [Operations](#operations)

# Data
Parameters of numbers.

## Size
All numbers are 32-bits independent of signedness or type.

## Representation
Binary.

## Endianness
Big-endian:

```
Most significant bit
|
v
X X X X
      ^
	  |
	  Least significant bit
```

# Assembly Syntax
Each line is interpreted as a new instruction.  
Blank lines, or lines with labels perform no operations.  

Each line follows the format:

```
[LABEL] [SIGNEDNESS][TYPE]<INSTRUCTION>[CONDITION] OPS...
```

- `LABEL`: Optional, creates a "bookmark" at the next instruction for later use,
           put a space or tab in this place to not create a label, can be 
		   included on their own line
- `SIGNEDNESS`: Optional by instruction, indicates signedness of operators, `S` 
                for signed, `U` for unsigned
- `TYPE`: Optional by instruction, indicates type of operators, `I` for integer,
          `F` for float
- `INSTRUCTION`: 3 letter mnemonic which refers to the instruction which will 
		         be run
- `CONDITION`: Optional, status code which must be set in `SC` register for 
               instruction to run
- `OPS...`: Operands for instruction

# Bit Pattern
32-bits per instruction encoding.

```
        LSB                                   MSB
bits:    | ---- 6 ---- |  --- 2 --- | -- 24 -- |
purpose: | Instruction |  Condition | Operands |
```

- Instructions: Accommodates 64 instructions
- Condition: See [Status Codes](#status-codes)
- Operands: Used for operands

# Registers
14 general purpose registers (`R0-R13`).  

1 dedicated program counter register (`PC`).  

1 dedicated status code register (`SC`).

Assembly syntax:

```
R0-13|PC|SC
```

In the documentation you may also see the shorthand:

```
{REG}
```

which refers to the longer form assembly syntax above.

# Addressing Modes
Addressing modes determine how operands of instructions are interpreted.

## Register Direct
Refers to the values stored in a register.

Assembly syntax:

```
{REG}
```

- `{REG}`: Register value is stored within

## Immediate
Constant value.  

Assembly syntax:

```
<VALUE>
```

- `VALUE`: Constant value, default base 10, prefix with `0x` for hex, and `b` 
           for binary

## Register Indirect
Register holds a memory address. Refers to value stored in this memory address.

Assembly syntax:

```
[<{REG}>]
```

- `{REG}`: Register which holds memory address

*Note: Brackets (`[`, `]`) are part of syntax, they are not indicate contents 
are optional*

## Register Indirect Offset
Register holds a base memory address. Immediate value is added to base address. 
Refers to value stored in this base + offset memory address. 

Assembly syntax:

```
[<{REG}>,<OFFSET>]
```

- `{REG}`: Register which holds base memory address
- `OFFSET`: Offset to apply to base memory address

*Note: Brackets (`[`, `]`) are part of syntax, they are not indicate contents 
are optional*

# Signedness and Types
Some instructions have variations based on the type of the data.  

Instruction mnemonics will be prefixed in assembly based on the type.

## Integer
- `U`: 16-bit unsigned integer
- `S`: 2's complement 16-bit integer

## Float
`F`: 2's complement 16-bit mantissa. 2's complement 16-bit exponent.

# Status Codes
Indicate the status of a previous operation.

Represented by 2-bits.

Statuses:

- `00`: Not equal
- `01`: Equal
- `10`: Greater than
- `11`: Less than

# Operations
## Data
Assembly syntax:

```
LOD|STR <dest> <src>
```

No sign or type variations.

Instructions:

- `LOD`: Load `src` into `dest`
- `STR`: Store `src` into `dest`

## Arithmetic
Assembly syntax:

```
ADD|SUB|MLT|DIV <dest> <op1> <op2>
```

Sign and type variations.

Instructions:

- `ADD`: Store `op1 + op2` in `dest`
- `SUB`: Store `op1 - op2` in `dest`
- `MLT`: Store `op1 x op2` in `dest`
- `DIV`: Store `op1 / op2` in `dest`

## Shift
Assembly syntax:

```
LSH,RSH <dest> <src> <n>
```

Sign and type variations.

Instructions:

- `LSH`: Store `src` left shifted by `n` bits
- `RSH`: Store `src` rotate shifted by `n` bits
