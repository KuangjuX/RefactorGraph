﻿#include "common.h"

namespace refactor::communication {
    using namespace frontend;

    InferResult inferAllGather(Operator const &op, Tensors inputs) {
        EXPECT_SIZE(1) {
            return Ok(Tensors(
                op.attribute("nranks").int_(),
                Tensor::share(inputs[0]->dataType, inputs[0]->shape, extractDependency(inputs))));
        }
    }

    computation::SharedOp lowerAllGather(Operator const &op, Tensors) {
        return nullptr;
    }
}// namespace refactor::communication
