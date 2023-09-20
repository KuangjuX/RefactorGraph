﻿#include "infer.h"

namespace refactor::communication {
    using namespace computation;

    InferResult inferAllGather(Operator const &op, Tensors inputs) {
        EXPECT_SIZE(1) {
            return Ok(Tensors(
                op.attribute("nranks").int_(),
                Tensor::share(inputs[0]->dataType, inputs[0]->shape, extractDependency(inputs))));
        }
    }
}// namespace refactor::communication
