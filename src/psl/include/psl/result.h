#pragma once

#include <optional>
#include <stdexcept>
#include <string>

namespace psl {
class ResultNoValueError : public std::runtime_error {
public:
    ResultNoValueError()
        : std::runtime_error(
              "Couldn't get value! Result type contains error!") {}
};

class ResultHasValueError : public std::runtime_error {
public:
    ResultHasValueError()
        : std::runtime_error(
              "Couldn't get error! Result type contains value!") {}
};

template <typename T>
class Result {
public:
    Result(const T &value) noexcept : value_(value) {}

    Result(T &&value) noexcept : value_(std::move(value)) {}

    Result(const std::string &error_message) noexcept
        : error_message_(error_message) {}

    Result(std::string &&error_message) noexcept
        : error_message_(std::move(error_message)) {}

    Result(const char *error_message) noexcept
        : error_message_(error_message) {}

    bool is_error() noexcept { return !value_.has_value(); }

    T get() {
        if (is_error()) {
            throw ResultNoValueError {};
        }
        return std::move(*value_);
    }

    T operator*() {
        if (is_error()) {
            throw ResultNoValueError {};
        }
        return std::move(*value_);
    }

    std::string error() {
        if (!is_error()) {
            throw ResultHasValueError {};
        }
        return error_message_;
    }

private:
    std::optional<T> value_;
    std::string error_message_;
};

}  // namespace psl