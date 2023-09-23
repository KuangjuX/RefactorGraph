﻿#ifndef PYTHON_FFI_IMPORT_H
#define PYTHON_FFI_IMPORT_H

#include "frontend/graph.h"
#include "functions.h"

namespace refactor::python_ffi {
    using SharedTensor = std::shared_ptr<frontend::Tensor>;
    using SharedOp = std::shared_ptr<frontend::Operator>;
    using SharedGraph = std::shared_ptr<frontend::Graph>;
    using Name = std::string;
    using NameVec = std::vector<Name>;
    using AttributeMap = std::unordered_map<Name, decltype(frontend::Attribute::value)>;

    SharedTensor makeTensor(int dataType, DimVec dims);
    SharedTensor makeTensorWithData(pybind11::array);
    SharedOp makeOp(Name opType, AttributeMap);
    SharedGraph makeGraph(
        std::unordered_map<Name, std::pair<NameVec, NameVec>> topology,
        std::unordered_map<Name, SharedOp> nodes,
        std::unordered_map<Name, SharedTensor> edges,
        NameVec inputs,
        NameVec outputs);

}// namespace refactor::python_ffi

#endif// PYTHON_FFI_IMPORT_H
