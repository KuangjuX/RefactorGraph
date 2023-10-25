﻿#ifndef KERNEL_BINARY_CUDA_HH
#define KERNEL_BINARY_CUDA_HH

#include "kernel/collectors/simple_binary.h"
#include "kernel/tensor.h"

namespace refactor::kernel {

    struct BinaryCuda final : public Kernel {
        DataType dataType;
        SimpleBinaryType opType;
        size_t size;
        bool constB;

        BinaryCuda(SimpleBinaryType, DataType, size_t, bool) noexcept;

        static KernelBox build(SimpleBinaryType, Tensor const &, Tensor const &) noexcept;
        static size_t typeId() noexcept;

        size_t kernelTypeId() const noexcept final;
        std::string_view description() const noexcept final;
#ifdef USE_CUDA
        Routine lower() const noexcept final;
#endif
    };

}// namespace refactor::kernel

#endif// KERNEL_BINARY_CUDA_HH
