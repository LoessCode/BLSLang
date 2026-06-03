//
// Created by Sid B on 06/01/26.
//

/*  Note, integers are stored from LSB to MSB left to right, to simplify operations on them.
 *
 */

#ifndef BLSLANG_BLSBYC_H
#define BLSLANG_BLSBYC_H


#include <cstdint>
#include <cstddef>

#include "blsl.h"


namespace BLSVM_N
{
    using ubyte_t = uint8_t;
    using ulongbyte_t = uint16_t;

    inline constexpr ulongbyte_t UNSIGNED_BYTE_MASK = 0x00FF;

    using sbyte_t = uint8_t;
    using slongbyte_t = int16_t;

    namespace Bytecode
    {
        using section_t = uint8_t;

        enum class Section: uint8_t
        {
            COMPILE_TIME_SIZES,
            LITERALS,
            INSTRUCTIONS,
        };

        using instHeader_t = uint64_t;
        using opcode_t = uint8_t;
        using optype_t = uint8_t;
        using operand_t = uint64_t;
        using flag_t = uint32_t;

        struct InstructionHeader
        {
            opcode_t opcode = 0;
            flag_t flags = 0;

            optype_t typeA = 0;
            optype_t typeB = 0;
            optype_t typeC = 0;
        };

        struct Instruction
        {
            InstructionHeader header;

            operand_t a = 0;
            operand_t b = 0;
            operand_t c = 0;
        };

        inline constexpr instHeader_t OPCODE_MASK = 0xFF00000000000000;
        inline constexpr instHeader_t TYPE_A_MASK = 0x00FF000000000000;
        inline constexpr instHeader_t TYPE_B_MASK = 0x0000FF0000000000;
        inline constexpr instHeader_t TYPE_C_MASK = 0x000000FF00000000;
        inline constexpr instHeader_t FLAGBT_MASK = 0x00000000FFFFFFFF;

        inline constexpr uint8_t OPCODE_SHIFT = 56;
        inline constexpr uint8_t TYPE_A_SHIFT = 48;
        inline constexpr uint8_t TYPE_B_SHIFT = 40;
        inline constexpr uint8_t TYPE_C_SHIFT = 32;
        inline constexpr uint8_t FLAGBT_SHIFT = 0;

        enum class OpCode : opcode_t
        {
            EMPTY = 0,

            SET,                                                                                                        // For assignment of a variable to an r-value;

            UNSIGNED_ADD,
            UNSIGNED_SUB,
            UNSIGNED_MUL,
            UNSIGNED_DIV,

            ADD,
            SUB,
            MUL,
            DIV,

            ADD_SCI,
            SUB_SCI,
            MUL_SCI,
            DIV_SCI,

            ALLOC_STACK,
            ALLOC_HEAP,

            CLING_STACK,              // This will tell a register to cling to a value from the stack/heap
            CLING_HEAP,
            JUMP,

            ARG_DENOTE,         // This will denote a register as an argument to be used in the current call frame.

            DEBUG_DUMP,         // Dumps value to the console.
        };

        // We will define these when necessary. But we have 32 possible flags.
        // Not an enum class to allow us to use as bitfield
        enum Flag : flag_t
        {
            FLAG1  = 0b00000000000000000000000000000001,
            FLAG2  = 0b00000000000000000000000000000010,
            FLAG3  = 0b00000000000000000000000000000100,
            FLAG4  = 0b00000000000000000000000000001000,
            FLAG5  = 0b00000000000000000000000000010000,
            FLAG6  = 0b00000000000000000000000000100000,
            FLAG7  = 0b00000000000000000000000001000000,
            FLAG8  = 0b00000000000000000000000010000000,
            FLAG9  = 0b00000000000000000000000100000000,
            FLAG10 = 0b00000000000000000000001000000000,
            FLAG11 = 0b00000000000000000000010000000000,
            FLAG12 = 0b00000000000000000000100000000000,
            FLAG13 = 0b00000000000000000001000000000000,
            FLAG14 = 0b00000000000000000010000000000000,
            FLAG15 = 0b00000000000000000100000000000000,
            FLAG16 = 0b00000000000000001000000000000000,
            FLAG17 = 0b00000000000000010000000000000000,
            FLAG18 = 0b00000000000000100000000000000000,
            FLAG19 = 0b00000000000001000000000000000000,
            FLAG20 = 0b00000000000010000000000000000000,
            FLAG21 = 0b00000000000100000000000000000000,
            FLAG22 = 0b00000000001000000000000000000000,
            FLAG23 = 0b00000000010000000000000000000000,
            FLAG24 = 0b00000000100000000000000000000000,
            FLAG25 = 0b00000001000000000000000000000000,
            FLAG26 = 0b00000010000000000000000000000000,
            FLAG27 = 0b00000100000000000000000000000000,
            FLAG28 = 0b00001000000000000000000000000000,
            FLAG29 = 0b00010000000000000000000000000000,
            FLAG30 = 0b00100000000000000000000000000000,
            FLAG31 = 0b01000000000000000000000000000000,
            FLAG32 = 0b10000000000000000000000000000000,
        };

        instHeader_t make_instruction_header(                                      // Makes Instruction
        opcode_t opcode = static_cast<opcode_t>(OpCode::EMPTY),
        optype_t typeA=0,
        optype_t typeB=0,
        optype_t typeC=0,
        flag_t flags=0
        );

    }


    namespace Bytecode
    {
        inline opcode_t extract_opcode(const instHeader_t &instHeader)
        {
            return static_cast<Bytecode::opcode_t>((instHeader & Bytecode::OPCODE_MASK) >> Bytecode::OPCODE_SHIFT);
        }

        inline operand_t extract_optype_A(const instHeader_t &instHeader)
        {
            return static_cast<Bytecode::opcode_t>((instHeader & Bytecode::TYPE_A_MASK) >> Bytecode::TYPE_A_SHIFT);
        }

        inline operand_t extract_optype_B(const instHeader_t &instHeader)
        {
            return static_cast<Bytecode::opcode_t>((instHeader & Bytecode::TYPE_B_MASK) >> Bytecode::TYPE_B_SHIFT);
        }

        inline operand_t extract_optype_C(const instHeader_t &instHeader)
        {
            return static_cast<Bytecode::opcode_t>((instHeader & Bytecode::TYPE_C_MASK) >> Bytecode::TYPE_C_SHIFT);
        }

        inline flag_t extract_flag(const instHeader_t &instHeader)
        {
            return static_cast<Bytecode::opcode_t>((instHeader & Bytecode::FLAGBT_MASK) >> Bytecode::FLAGBT_SHIFT);
        }

        inline InstructionHeader decode_instruction_header(const instHeader_t& instHeader)
        {
            InstructionHeader instructionHeaderStruct{};
            instructionHeaderStruct.opcode = Bytecode::extract_opcode(instHeader);
            instructionHeaderStruct.typeA = Bytecode::extract_optype_A(instHeader);
            instructionHeaderStruct.typeB = Bytecode::extract_optype_B(instHeader);
            instructionHeaderStruct.typeC = Bytecode::extract_optype_C(instHeader);
            instructionHeaderStruct.flags = Bytecode::extract_flag(instHeader);
            return instructionHeaderStruct;
        }
    }

}



namespace BLSVM_N
{
    using reginfo_t = uint16_t;

    using regtype_t = uint8_t;
    using regflag_t = uint8_t;

    inline constexpr reginfo_t REGISTER_TYPE_MASK = 0xFF00;
    inline constexpr reginfo_t REGISTER_FLAG_MASK = 0x00FF;

    inline constexpr uint8_t REGISTER_TYPE_SHIFT = 8;
    inline constexpr uint8_t REGISTER_FLAG_SHIFT = 0;

    enum class RegisterType: regtype_t
    {
        ITR,            // Internal
        ARG,            // Argument
        RTN,            // Return
        SCI,            // Sci i.e. float
        GNR,            // General
        SCR,            // Scratch
    };

    inline constexpr size_t REG_COUNT_ITR = 16;
    inline constexpr size_t REG_COUNT_ARG = 32;
    inline constexpr size_t REG_COUNT_RTN = 32;
    inline constexpr size_t REG_COUNT_SCI = 64;
    inline constexpr size_t REG_COUNT_GNR = 128;
    inline constexpr size_t REG_COUNT_SCR = 128;



    // Not Enum Class to allow us to use as bitfield.
    enum RegisterFlag: regflag_t
    {
        REG_FLAG_WRITABLE = 0b00000001,
        REG_FLAG_PRE_CALL_WRITABLE = 0b00000010,
        REG_FLAG_POST_CALL_WRITEABLE = 0b00000100,
        REG_FLAG_SPECIAL_WRITEABLE = 0b00001000,

        REG_FLAG5 = 0b00010000,
        REG_FLAG6 = 0b00100000,
        REG_FLAG7 = 0b01000000,
        REG_FLAG8 = 0b10000000,
    };

    struct RegisterInfo
    {
        RegisterType type;
        regflag_t flags;
        size_t count;
    };

    struct Register
    {
        ubyte_t* loc;               // Location of data in register
        size_t size;                // Size of value stored
        reginfo_t info;             // Info about this register
    };

    inline constexpr size_t REGISTER_COUNT = REG_COUNT_ITR + REG_COUNT_ARG + REG_COUNT_RTN + REG_COUNT_SCI + REG_COUNT_GNR + REG_COUNT_SCR;

}

namespace BLSVM_N
{
    inline reginfo_t make_reginfo(regtype_t type, regflag_t flags)
    {
        reginfo_t reginfo = 0;

        reginfo |= (static_cast<reginfo_t>(type) << REGISTER_TYPE_SHIFT) & REGISTER_TYPE_MASK;
        reginfo |= (static_cast<reginfo_t>(flags) << REGISTER_FLAG_SHIFT) & REGISTER_FLAG_MASK;

        return reginfo;
    }

    inline const std::unordered_map<RegisterType, RegisterInfo> REGISTER_INFO = {
        {
            RegisterType::ITR,
            {
                RegisterType::ITR,
                RegisterFlag::REG_FLAG_SPECIAL_WRITEABLE,
                REG_COUNT_ITR
            }
        },
        {
            RegisterType::ARG,
            {
                RegisterType::ARG,
                RegisterFlag::REG_FLAG_PRE_CALL_WRITABLE,
                REG_COUNT_ARG
            }
        },
        {
            RegisterType::RTN,
            {
                RegisterType::RTN,
                RegisterFlag::REG_FLAG_POST_CALL_WRITEABLE,
                REG_COUNT_RTN
            }
        },
        {
            RegisterType::SCI,
            {
                RegisterType::SCI,
                RegisterFlag::REG_FLAG_WRITABLE,
                REG_COUNT_SCI
            }
        },
        {
            RegisterType::GNR,
            {
                RegisterType::GNR,
                RegisterFlag::REG_FLAG_WRITABLE,
                REG_COUNT_GNR
            }
        },
        {
            RegisterType::SCR,
            {
                RegisterType::SCR,
                RegisterFlag::REG_FLAG_WRITABLE,
                REG_COUNT_SCR
            }
        },
    };
}

namespace BLSVM
{

    using ubyte_t = uint8_t;
    using ulongbyte_t = uint16_t;

    inline constexpr ulongbyte_t UNSIGNED_BYTE_MASK = 0x00FF;

    using sbyte_t = uint8_t;
    using slongbyte_t = int16_t;


    namespace Bytecode
    {
        using section_t = uint8_t;

        enum class Section: uint8_t
        {
            COMPILE_TIME_SIZES,
            LITERALS,
            INSTRUCTIONS,
        };


        using instruction_t = uint64_t;
        using opcode_t = uint8_t;
        using operand_t = uint16_t;
        using flag_t = uint8_t;

        struct Instruction
        {
            opcode_t opcode = 0;
            operand_t a = 0;
            operand_t b = 0;
            operand_t c = 0;
            flag_t flags = 0;
        };

        inline constexpr instruction_t OPCODE_MASK = 0xFF00000000000000;
        inline constexpr instruction_t OPND_A_MASK = 0x00FFFF0000000000;
        inline constexpr instruction_t OPND_B_MASK = 0x000000FFFF000000;
        inline constexpr instruction_t OPND_C_MASK = 0x0000000000FFFF00;
        inline constexpr instruction_t FLAGBT_MASK = 0x00000000000000FF;

        inline constexpr operand_t OPND_TYPE_MASK = 0b1000'0000'0000'0000;                      //Tells the VM whether this points to a register (1) or constant pool (0).

        inline constexpr uint8_t OPCODE_SHIFT = 56;
        inline constexpr uint8_t OPND_A_SHIFT = 40;
        inline constexpr uint8_t OPND_B_SHIFT = 24;
        inline constexpr uint8_t OPND_C_SHIFT = 8;
        inline constexpr uint8_t FLAGBT_SHIFT = 0;

        inline constexpr uint8_t OPND_T_SHIFT = 15;

        enum class OpCode : opcode_t
        {
            EMPTY = 0,

            SET,                                                                                                        // For assignment of a variable to an r-value;

            UNSIGNED_ADD,
            UNSIGNED_SUB,
            UNSIGNED_MUL,
            UNSIGNED_DIV,

            ADD,
            SUB,
            MUL,
            DIV,

            ADD_SCI,
            SUB_SCI,
            MUL_SCI,
            DIV_SCI,

            ALLOC_STACK,
            ALLOC_HEAP,

            CLING_STACK,              // This will tell a register to cling to a value from the stack/heap
            CLING_HEAP,
            JUMP,

            ARG_DENOTE,         // This will denote a register as an argument to be used in the current call frame.

            DEBUG_DUMP,         // Dumps value to the console.
        };

        //We will define these when necessary. But we have eight possible flags.
        enum class Flag : flag_t
        {
            FLAG1 = 0b00000001,
            FLAG2 = 0b00000010,
            FLAG3 = 0b00000100,
            FLAG4 = 0b00001000,
            FLAG5 = 0b00010000,
            FLAG6 = 0b00100000,
            FLAG7 = 0b01000000,
            FLAG8 = 0b10000000,
        };

        instruction_t make_instruction(                                      // Makes Instruction
            opcode_t opcode = static_cast<opcode_t>(OpCode::EMPTY),
            operand_t a=0,
            operand_t b=0,
            operand_t c=0,
            flag_t flags=0
        );

        bool is_register(operand_t operand);                                 // Checks if the operand is a register or a constant pool reference
        inline void set_register_flag(operand_t& operand, bool value);              // Sets the register flag in the operand.

        opcode_t decode_opcode(const instruction_t& instruction);
        operand_t decode_operand_A(const instruction_t& instruction);
        operand_t decode_operand_B(const instruction_t& instruction);
        operand_t decode_operand_C(const instruction_t& instruction);
        flag_t decode_flag(const instruction_t& instruction);

        Instruction decode_instruction(const instruction_t& instruction);


    }


    namespace Bytecode
    {
        struct ConstEntry
        {
            size_t size;                                                            // Printed out as sizeof(size_t) characters followed by size characters.
            ubyte_t* data;
        };
    }

}


namespace BLSVM
{
    using reginfo_t = uint16_t;

    using regtype_t = uint8_t;
    using regflag_t = uint8_t;

    inline constexpr reginfo_t REGISTER_TYPE_MASK = 0xFF00;
    inline constexpr reginfo_t REGISTER_FLAG_MASK = 0x00FF;

    inline constexpr uint8_t REGISTER_TYPE_SHIFT = 8;
    inline constexpr uint8_t REGISTER_FLAG_SHIFT = 0;

    enum class RegisterType: regtype_t
    {
        INTERNAL,
        ARGS,
        RETURNS,
        SCI,
        GENERAL,
        SCRATCH,
    };

    // Not Enum Class to allow us to use as bitfield.
    enum RegisterFlag: regflag_t
    {
        REG_FLAG_WRITABLE = 0b00000001,
        REG_FLAG_PRE_CALL_WRITABLE = 0b00000010,
        REG_FLAG_POST_CALL_WRITEABLE = 0b00000100,
        REG_FLAG_SPECIAL_WRITEABLE = 0b00001000,
    };

    struct RegisterInfo
    {
        RegisterType type;
        regflag_t flags;
        size_t count;
    };

    inline reginfo_t make_reginfo(regtype_t type, regflag_t flags);

    struct Register
    {
        ubyte_t* loc;
        size_t size;
        reginfo_t info;
    };

    inline constexpr size_t REGISTER_COUNT = 256+128;
    extern const std::vector<RegisterInfo> REGISTER_INFO;
};


#endif //BLSLANG_BLSBYC_H
