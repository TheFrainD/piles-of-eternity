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
struct Ok {
    Ok(const T &value) noexcept : value(value) {}
    Ok(T &&value) noexcept : value(std::move(value)) {}

    T value;
};

template <typename T>
struct Err {
    Err(const T &value) noexcept : value(value) {}
    Err(T &&value) noexcept : value(std::move(value)) {}

    T value;
};

template <typename T, typename E = std::string>
class Result {
public:
    Result(Ok<T> &&ok) noexcept : value_(std::move(ok.value)) {}
    Result(Err<E> &&err) noexcept : error_(std::move(err.value)) {}

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

    E error() {
        if (!is_error()) {
            throw ResultHasValueError {};
        }
        return std::move(error_);
    }

private:
    std::optional<T> value_;
    E error_;
};

}  // namespace psl