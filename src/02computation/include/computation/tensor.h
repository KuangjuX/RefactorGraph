﻿#ifndef COMPUTATION_TENSOR_H
#define COMPUTATION_TENSOR_H

#include "absl/container/inlined_vector.h"
#include "common/data_type.h"
#include <unordered_set>
#include <variant>

namespace refactor::computation {

    struct DimVariableInternal {
        std::string name;
        std::optional<int64_t> value;

        explicit DimVariableInternal(
            std::string,
            std::optional<int64_t> = std::nullopt);
    };

    using DimVariable = std::shared_ptr<DimVariableInternal>;

    struct DimExpr {
        std::variant<int64_t, DimVariable> expr;

        bool operator==(DimExpr const &) const;
        bool operator!=(DimExpr const &) const;

        explicit DimExpr(int64_t);
        explicit DimExpr(std::string);
        explicit DimExpr(DimVariable);
        bool isValue() const;
        bool isVariable() const;
        bool hasValue() const;
        int64_t value() const;
        DimVariable variable() const;
    };

    using Shape = absl::InlinedVector<DimExpr, 4>;

    std::string shapeFormat(Shape const &);

    /// @brief 内存块。
    struct Blob {
        /// @brief ! NOTICE 指针必须非空。
        void *ptr;

        explicit Blob(void *);
        Blob(Blob const &) = delete;
        Blob(Blob &&) = delete;

        ~Blob();
    };

    /// @brief 张量边。
    struct Tensor {
        common::DataType dataType;
        Shape shape;
        std::shared_ptr<Blob> data;

        std::unordered_set<DimVariable> depVariables;

        Tensor(common::DataType, Shape, std::shared_ptr<Blob>, std::unordered_set<DimVariable>);
        static std::shared_ptr<Tensor> share(
            common::DataType,
            Shape,
            std::unordered_set<DimVariable>,
            std::shared_ptr<Blob> = nullptr);

        bool hasData() const;
        size_t elementsSize() const;
        size_t bytesSize() const;

        void *malloc();
        void free();
    };

    struct Edge {
        std::shared_ptr<Tensor> tensor;
        std::string name;
    };

}// namespace refactor::computation

#endif// COMPUTATION_TENSOR_H
