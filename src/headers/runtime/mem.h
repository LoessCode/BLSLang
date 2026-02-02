//
// Created by Sid B on 30/01/26.
//


#ifndef BLSLANG_STACK_H
#define BLSLANG_STACK_H

#include <array>
#include <vector>
#include <iostream>
#include "../core/blsbyc.h"

namespace BLSVM
{
    struct View
    {
        ubyte_t const* const loc;
        const size_t size;
    };
}

namespace BLSVM
{
    inline constexpr size_t STACK_SIZE = 1024*1024*4;
    inline constexpr size_t OFFSET_VECTOR_SIZE = 1024*4;

    class Stack
    {
    private:
        std::array<ubyte_t, STACK_SIZE> _memory{};
        std::vector<std::pair<ptrdiff_t, size_t>> _elementOffsets;                  //Stores the offsets of elements within the stack and stores their sizes.
        ptrdiff_t _stackPointer;

    protected:
        [[nodiscard]] ubyte_t* get_ptr(size_t elementIndex);
        [[nodiscard]] size_t get_size(size_t elementIndex) const;

    public:
        Stack();

        void push(const ubyte_t* data, size_t size);
        void push(size_t size);
        void write(const ubyte_t* data, size_t elementIndex);
        void pop();

    };
}

namespace BLSVM
{
    class LiteralPool
    {
    private:
        std::vector<ubyte_t> _memory;
        std::vector<std::pair<ptrdiff_t, size_t>> _elementOffsets;

    protected:
        [[nodiscard]] ubyte_t const* read_data(size_t elementIndex) const;
        [[nodiscard]] size_t read_size(size_t elementIndex) const;

    public:
        explicit LiteralPool(std::istream& inputStream);
        LiteralPool() = default;

        void defer_load_lp(std::istream& inputStream);
    };
}

namespace BLSVM
{
    class CompileTimeSizePool
    {
    private:
        std::vector<size_t> _data;
    protected:
        [[nodiscard]] size_t get_size(size_t elementIndex) const;

    public:
        explicit CompileTimeSizePool(std::istream& inputStream);
        CompileTimeSizePool() = default;

        void defer_load_csz(std::istream& inputStream);
    };
}

#endif //BLSLANG_STACK_H