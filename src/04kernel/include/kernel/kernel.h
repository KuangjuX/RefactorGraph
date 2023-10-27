﻿#ifndef KERNEL_KERNEL_H
#define KERNEL_KERNEL_H

#include "runtime/stream.h"
#include <memory>
#include <string_view>

namespace refactor::kernel {
    using runtime::Routine;

    class Kernel {
    public:
        virtual ~Kernel() = default;
        virtual size_t kernelTypeId() const = 0;
        virtual std::string_view description() const = 0;
        virtual Routine lower() const;
    };

    using KernelBox = std::unique_ptr<Kernel>;

}// namespace refactor::kernel

#endif// KERNEL_KERNEL_H
