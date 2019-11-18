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
[LABEL] [ST]<INSTRUCTION>[CONDITION] OPS...
```

- `LABEL`: Optional, creates a "bookmark" at the next instruction for later use,
           put a space or tab in this place to not create a label, can be 
		   included on their own line
- `ST`: Optional by instruction, indicates signedness and type of operators, see
        [Signedness and Type](#signedness-and-type)
- `INSTRUCTION`: 3 letter mnemonic which refers to the instruction which will 
		         be run
- `CONDITION`: Optional, status code which must be set in `SC` register for 
               instruction to run
- `OPS...`: Operands for instruction

# Bit Pattern
32-bits per instruction encoding.

```
        MSB                                   LSB
bits:    | -- 24 -- | --- 2 --- | ---- 6 ---- |
purpose: | Operands | Condition | Instruction |
```

- Instructions: Accommodates 64 instructions
- Condition: See [Status Codes](#status-codes)
- Operands: Used for operand data, for each operand passed in there is a 
            segment of 2-bits preceding it which indicates its addressing mode 
			(see [Addressing Modes](#addressing-modes))

# Registers
16 total:

- `R0-13`: 14 general purpose registers
- `PC`: 1 dedicated program counter register
- `SC`: 1 dedicated status code register
- `LI`: 1 dedicated link register which holds jump values

Assembly syntax:

```
R0-13|PC|SC|LI
```

In the documentation you may also see the shorthand:

```
{REG}
```

Bit pattern:

- unsigned 4-bit number
- `R0-13`: 0-13
- `PC`: 14
- `SC`: 15

# Addressing Modes
Addressing modes determine how operands of instructions are interpreted.

## Register Direct
Refers to the values stored in a register.

Assembly syntax:

```
{REG}
```

- `{REG}`: Register value is stored within

Bit pattern: `00`

## Immediate
Constant value.  

Assembly syntax:

```
<VALUE>
```

- `VALUE`: Constant value, default base 10, prefix with `0x` for hex, and `b` 
           for binary
		   
Bit pattern: `01`

## Register Indirect
Register holds a memory address. Refers to value stored in this memory address.

Assembly syntax:

```
[<{REG}>]
```

- `{REG}`: Register which holds memory address

*Note: Brackets (`[`, `]`) are part of syntax, they do not indicate contents 
are optional*

Bit pattern: `10`

## Register Indirect Offset
Register holds a base memory address. Immediate value is added to base address. 
Refers to value stored in this base + offset memory address. 

Assembly syntax:

```
[<{REG}>,<OFFSET>]
```

- `{REG}`: Register which holds base memory address
- `OFFSET`: Offset to apply to base memory address

*Note: Brackets (`[`, `]`) are part of syntax, they do not indicate contents 
are optional*

Bit pattern: `11`

# Signedness and Types
Some instructions have variations based on the type of the data.  

Instruction mnemonics will be prefixed in assembly based on the type.

In the documentation you may also see the shorthand:

```
{ST}
```

which represents any of the prefixes listed below.

## Integer
Prefixes:

- `U`: Insigned integer
- `S`: 2's complement integer

## Float
Prefixes:

- `F`: 2's complement mantissa. 2's complement exponent

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
{ST}ADD|SUB|MLT|DIV <dest> <op1> <op2>
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

## Compare
Assembly syntax:

```
{ST}CMP <op1> <op2>
```

Sign and type variations.

Instructions:

- `CMP`: Compares `op1` to `op2` and sets the status code register based on 
         the result

## Jump
Assembly syntax:

```
JMP <dest>
```

No sign and type variations.

Instructions:

- `JMP`: Jump to instruction at address `dest`
