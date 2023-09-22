﻿#ifndef FRONTEND_OPERATOR_H
#define FRONTEND_OPERATOR_H

#include "infer.h"
#include "lower.h"
#include "tensor.h"
#include <memory>
#include <variant>
#include <vector>

namespace refactor::frontend {

    using Int = long long;
    using Ints = std::vector<long long>;
    using Float = double;
    using Floats = std::vector<double>;
    using String = std::string;
    using Strings = std::vector<std::string>;
    using Tensor_ = std::shared_ptr<Tensor>;
    using Tensors = std::vector<std::shared_ptr<Tensor>>;

    struct Attribute {
        std::variant<Int, Ints, Float, Floats, String, Strings, Tensor_, Tensors> value;

        bool operator==(Attribute const &) const;
        bool operator!=(Attribute const &) const;

        Int const &int_() const;
        Ints const &ints() const;
        Float const &float_() const;
        Floats const &floats() const;
        String const &string() const;
        Strings const &strings() const;
        Tensor_ const &tensor() const;
        Tensors const &tensors() const;
    };
    using Attributes = std::unordered_map<std::string, Attribute>;

    struct OpType {
        size_t id;

        bool operator==(OpType const &) const;
        bool operator!=(OpType const &) const;

        static void register_(const char *, InferFn, LowerFn);
        static OpType parse(std::string);
        static std::optional<OpType> tryParse(const char *);

        std::string_view name() const;
        bool is(std::string_view) const;
    };

    struct Operator {
        OpType opType;
        Attributes attributes;

        bool operator==(Operator const &) const;
        bool operator!=(Operator const &) const;

        Attribute const &attribute(const char *) const;
        Attribute const &attribute(const char *, Attribute const &default_) const;

        InferResult infer(Tensors) const;
        computation::SharedOp lower(Tensors) const;
    };

    struct Node {
        Operator op;
        std::string name;
    };

}// namespace refactor::frontend

#endif// FRONTEND_OPERATOR_H
