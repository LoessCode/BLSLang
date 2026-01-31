# BLSL <u>B</u>asic <u>L</u>arge-<u>S</u>ized <u>L</u>anguage
### A basic scripting language with large (n byte sized) primitives for scientific computation / experimentation. 

## <u> Build and Execution </u>


## <u> Language Characteristics </u>
- N Sized primitive types for infinite precision / size of values.
- Purely functional, no structures / classes. Supports conditionals, functions, loops.
- Fully arena allocated for performance and simplicity
- Variables store raw binary data. Operations determine how to interpret given bytes. 
    For example: two binary variables can be added as if they're ints, in which case integer addition of the binary numbers occurs. 
    Or, they can be added as strings, in which case the bytes are concatenated. They can be represented as any type for display too. 

## <u> Implementation </u>
- Register VM with custom bytecode
- Lexer-Parser-Compiler pipeline to convert textual code to bytecode through AST intermediate
- Pure reference registers, which hold references to heap / stack
- Constant Pool for literals, instructions do not support immediate values
