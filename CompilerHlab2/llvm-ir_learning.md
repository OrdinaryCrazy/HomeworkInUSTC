# learn-llvm-ir

#### LLVM identifiers come in two basic types: global and local. Global identifiers (functions, global variables) begin with the '@' character. Local identifiers (register names, types) begin with the '%' character. Additionally, there are three different formats for identifiers, for different purposes:

* Named values are represented as a string of characters with their prefix. For example, %foo, @DivisionByZero, %a.really.long.identifier. The actual regular expression used is ‘[%@][-a-zA-Z$._][-a-zA-Z$._0-9]*’. Identifiers that require other characters in their names can be surrounded with quotes. Special characters may be escaped using "\xx" where xx is the ASCII code for the character in hexadecimal. In this way, any character can be used in a name value, even quotes themselves. The "\01" prefix can be used on global values to suppress mangling.
*  Unnamed values are represented as an unsigned numeric value with their prefix. For example, %12, @2, %44.
* Constants, which are described in the section Constants below.

* %2：第二个未命名的局部变量

#### Attribute groups are groups of attributes that are referenced by objects within the IR. They are important for keeping .ll files readable, because a lot of functions will use the same set of attributes. In the degenerative case of a .ll file that corresponds to a single .c file, the single attribute group will capture the important command line flags used to build that file. An attribute group is a module-level object. To use an attribute group, an object references the attribute group’s ID (e.g. #37). An object may refer to more than one attribute group. In that situation, the attributes from the different groups are merged. Here is an example of attribute groups for a function that should always be inlined, has a stack alignment of 4, and which shouldn’t use SSE instructions:

```
; Target-independent attributes:
attributes #0 = { alwaysinline alignstack=4 }

; Target-dependent attributes:
attributes #1 = { "no-sse" }

; Function @f has attributes: alwaysinline, alignstack=4, and "no-sse".
define void @f() #0 #1 { ... }
```

#### The ‘`alloca`’ instruction allocates memory on the stack frame of the currently executing function, to be automatically released when this function returns to its caller. The object is always allocated in the address space for allocas indicated in the datalayout.

The ‘`alloca`’ instruction allocates `sizeof(<type>)*NumElements` bytes of memory on the runtime stack, returning a pointer of the appropriate type to the program. If “NumElements” is specified, it is the number of elements allocated, otherwise “NumElements” is defaulted to be one. If a constant alignment is specified, the value result of the allocation is guaranteed to be aligned to at least that boundary. The alignment may not be greater than `1 << 29`. If not specified, or if zero, the target can choose to align the allocation on any convenient boundary compatible with the type.

***align***:边界对齐

#### The ‘`icmp`’ instruction returns a boolean value or a vector of boolean values based on comparison of its two integer, integer vector, pointer, or pointer vector operands. The ‘`icmp`’ instruction takes three operands. The first operand is the condition code indicating the kind of comparison to perform. It is not a value, just a keyword. The possible condition codes are:

1. `eq`: equal
2. `ne`: not equal
3. `ugt`: unsigned greater than
4. `uge`: unsigned greater or equal
5. `ult`: unsigned less than
6. `ule`: unsigned less or equal
7. `sgt`: signed greater than
8. `sge`: signed greater or equal
9. `slt`: signed less than
10. `sle`: signed less or equal

#### A function definition contains a list of basic blocks, forming the CFG (Control Flow Graph) for the function. Each basic block may optionally start with a label (giving the basic block a symbol table entry), contains a list of instructions, and ends with a [terminator](http://llvm.org/docs/LangRef.html#terminators)instruction (such as a branch or function return). If an explicit label is not provided, a block is assigned an implicit numbered label, using the next value from the same counter as used for unnamed temporaries ([see above](http://llvm.org/docs/LangRef.html#identifiers)). For example, if a function entry block does not have an explicit label, it will be assigned label “%0”, then the first unnamed temporary in that block will be “%1”, etc.

















