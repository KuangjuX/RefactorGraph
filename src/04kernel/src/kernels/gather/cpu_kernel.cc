#include "cpu_kernel.hh"
#include <execution>

namespace refactor::kernel {
    using K = GatherCpu;

    K::GatherCpu(GatherInfo info_) noexcept
        : Kernel(), info(std::move(info_)) {}

    auto K::build(GatherInfo info) noexcept -> KernelBox {
        return std::make_unique<K>(std::move(info));
    }

    auto K::typeId() noexcept -> size_t {
        static uint8_t ID = 1;
        return reinterpret_cast<size_t>(&ID);
    }

    auto K::kernelTypeId() const noexcept -> size_t { return typeId(); }
    auto K::description() const noexcept -> std::string_view {
        return "Performing gather using CPU";
    }

    Routine K::lower() const noexcept {
        using namespace runtime;

        return [info = this->info](Resources &, void const **inputs, void **outputs) {
            auto data = reinterpret_cast<uint8_t const *>(inputs[0]);
            auto output = reinterpret_cast<uint8_t *>(outputs[0]);
            auto policy = std::execution::par_unseq;
            std::for_each_n(policy, natural_t(0), info.prefix, [&](auto i) {
                std::for_each_n(policy, natural_t(0), info.midSizeO, [&](auto j) {
                    auto k = info.index(inputs[1], j);
                    std::memcpy(info.postfix * (i * info.midSizeO + j) + output,
                                info.postfix * (i * info.midSizeI + k) + data,
                                info.postfix);
                });
            });
        };
    }

}// namespace refactor::kernel
