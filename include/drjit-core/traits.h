/*
    drjit/traits.h -- C++ type traits for analyzing variable types

    This file provides helper traits that are needed by the C++ array
    wrappers defined in in 'drjit/jitvar.h'.

    Copyright (c) 2021 Wenzel Jakob <wenzel.jakob@epfl.ch>

    All rights reserved. Use of this source code is governed by a BSD-style
    license that can be found in the LICENSE file.
*/

#pragma once

#include <drjit-core/jit.h>
#include <type_traits>

#if !defined(NAMESPACE_BEGIN)
#  define NAMESPACE_BEGIN(name) namespace name {
#endif

#if !defined(NAMESPACE_END)
#  define NAMESPACE_END(name) }
#endif

NAMESPACE_BEGIN(drjit)

struct half;

NAMESPACE_BEGIN(detail)

// Type traits that can be legally overwritten within Dr.Jit
template <typename T> struct is_signed : std::is_signed<T> { };
template <typename T> constexpr bool is_signed_v = is_signed<T>::value;
template <typename T> struct is_unsigned : std::is_unsigned<T> { };
template <typename T> constexpr bool is_unsigned_v = is_unsigned<T>::value;
template <typename T> struct is_floating_point : std::is_floating_point<T> { };
template <typename T> constexpr bool is_floating_point_v = is_floating_point<T>::value;
template <typename T> struct is_arithmetic : std::is_arithmetic<T> { };
template <typename T> constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
template <typename T> struct is_integral : std::is_integral<T> { };
template <typename T> constexpr bool is_integral_v = is_integral<T>::value;
template <typename T> struct is_scalar : std::is_scalar<T> { };
template <typename T> constexpr bool is_scalar_v = is_scalar<T>::value;

NAMESPACE_END(detail)

template <bool Value> using enable_if_t = typename std::enable_if<Value, int>::type;

template <typename T, typename = int> struct var_type {
    static constexpr VarType value = VarType::Void;
};

template <typename T> struct var_type<T, enable_if_t<detail::is_integral_v<T> && sizeof(T) == 1>> {
    static constexpr VarType value =
        std::is_signed<T>::value ? VarType::Int8 : VarType::UInt8;
};

template <typename T> struct var_type<T, enable_if_t<detail::is_integral_v<T> && sizeof(T) == 2>> {
    static constexpr VarType value =
        std::is_signed<T>::value ? VarType::Int16 : VarType::UInt16;
};

template <typename T> struct var_type<T, enable_if_t<detail::is_integral_v<T> && sizeof(T) == 4>> {
    static constexpr VarType value =
        std::is_signed<T>::value ? VarType::Int32 : VarType::UInt32;
};

template <typename T> struct var_type<T, enable_if_t<detail::is_integral_v<T> && sizeof(T) == 8>> {
    static constexpr VarType value =
        std::is_signed<T>::value ? VarType::Int64 : VarType::UInt64;
};

template <typename T> struct var_type<T, enable_if_t<std::is_enum<T>::value>> {
    static constexpr VarType value = var_type<std::underlying_type_t<T>>::value;
};

template <typename T> struct var_type<T, enable_if_t<detail::is_floating_point_v<T> && sizeof(T) == 2>> {
    static constexpr VarType value = VarType::Float16;
};

template <typename T> struct var_type<T, enable_if_t<std::is_pointer_v<T>>> {
    static constexpr VarType value = VarType::UInt32;
};

template <> struct var_type<float> {
    static constexpr VarType value = VarType::Float32;
};

template <> struct var_type<double> {
    static constexpr VarType value = VarType::Float64;
};

template <> struct var_type<bool> {
    static constexpr VarType value = VarType::Bool;
};

#if __cplusplus >= 201703L || (defined(_MSVC_LANG) && _MSVC_LANG > 201402)
   template <typename T> constexpr VarType type_v = var_type<T>::value;
#endif

NAMESPACE_END(drjit)
