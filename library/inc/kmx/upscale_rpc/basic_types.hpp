// Upscale RPC library
// Copyright (C) 2022 Flaviu C.
#pragma once
#ifndef PCH
    #include <array>
    #include <cstdint>
    #include <cstring>
    #include <limits>
    #include <optional>
    #include <span>
    #include <vector>
#endif

namespace kmx::upscale_rpc
{
    using offset_t = std::uint32_t;
    using object_id_t = std::uint8_t;

    using method_id_t = std::uint8_t;

    class method
    {
    public:
        using data_t = std::uint8_t;

        method() = default;
        method(const data_t item): data_(item) {}
        method(method&&) = default;
        method(const method&) = default;
        method& operator=(const method&) = default;
        method& operator=(method&&) = default;

        operator data_t() const noexcept { return data_; }

        data_t id() const noexcept { return data_ & ~ingore_result_mask; }
        void set_id(const data_t item) noexcept { data_ = (data_ & ingore_result_mask) | (item & ~ingore_result_mask); }

        bool ignore_result() const noexcept { return (data_ & ingore_result_mask) != 0u; }
        void set_ignore_result(const bool item) noexcept
        {
            if (item)
                data_ |= ingore_result_mask;
            else
                data_ &= ~ingore_result_mask;
        }

    private:
        static constexpr data_t ingore_result_mask = 128u;

        data_t data_ {};
    };

    using object_method_id_t = std::pair<object_id_t, method>;
    using object_method_id_vector_t = std::vector<object_method_id_t>;
    using c_raw_data_t = std::span<const std::uint8_t>;
    using c_raw_data_vector_t = std::vector<c_raw_data_t>;
    using raw_data_t = std::span<std::uint8_t>;
    using alignment_t = std::uint8_t;

    template <typename T>
    constexpr auto operator+(T e) noexcept //-> std::enable_if_t<std::is_enum<T>::value, std::underlying_type_t<T>>
    {
        return static_cast<std::underlying_type_t<T>>(e);
    }

    template <typename _Array>
    constexpr raw_data_t to_span(_Array& array) noexcept
    {
        return {reinterpret_cast<std::uint8_t*>(array.data()), array.size() * sizeof(typename _Array::value_type)};
    }

    template <typename _Array>
    constexpr c_raw_data_t to_cspan(_Array& array) noexcept
    {
        return {reinterpret_cast<const std::uint8_t*>(array.data()), array.size() * sizeof(typename _Array::value_type)};
    }

    template <typename T>
    constexpr T align_forward(const T offset, const std::uint8_t alignment) noexcept
    {
        return (offset + (alignment - 1u)) & -alignment;
    }

    template <typename T>
    constexpr T* align_forward(T* const offset, const std::uint8_t alignment) noexcept
    {
        return reinterpret_cast<T*>((reinterpret_cast<std::size_t>(offset) + (alignment - 1u)) & -alignment);
    }

    template <typename T>
    constexpr T& as_ref(auto* p) noexcept
    {
        return *reinterpret_cast<T*>(p);
    }

    template <typename T>
    constexpr const T& as_cref(auto* p) noexcept
    {
        return *reinterpret_cast<const T*>(p);
    }

    template <typename T>
    constexpr T* as_ptr(auto* p) noexcept
    {
        return reinterpret_cast<T*>(p);
    }

    template <typename T>
    constexpr const T* as_cptr(auto* p) noexcept
    {
        return reinterpret_cast<const T*>(p);
    }

    enum class size_type_t : std::uint8_t
    {
        _1_byte,
        _2_bytes,
        _4_bytes,
        _8_bytes,
    };

    template <typename _ContextId>
    constexpr size_type_t get_context_size() noexcept;

    template <>
    constexpr size_type_t get_context_size<std::uint8_t>() noexcept
    {
        return size_type_t::_1_byte;
    }

    template <>
    constexpr size_type_t get_context_size<std::uint16_t>() noexcept
    {
        return size_type_t::_2_bytes;
    }

    template <>
    constexpr size_type_t get_context_size<std::uint32_t>() noexcept
    {
        return size_type_t::_4_bytes;
    }

    template <>
    constexpr size_type_t get_context_size<std::uint64_t>() noexcept
    {
        return size_type_t::_8_bytes;
    }

    static constexpr std::array<std::size_t, 4u> max_values {
        std::numeric_limits<std::uint8_t>::max(),
        std::numeric_limits<std::uint16_t>::max(),
        std::numeric_limits<std::uint32_t>::max(),
        std::numeric_limits<std::uint64_t>::max(),
    };

    constexpr std::size_t max_value_of(const size_type_t size_type) noexcept
    {
        return max_values[+size_type];
    }

    bool same_data(const c_raw_data_t& lhs, const c_raw_data_t& rhs) noexcept;

    constexpr size_type_t size_type_of(const offset_t offset) noexcept
    {
        const auto item = std::lower_bound(max_values.begin(), max_values.end(), offset);
        return item != max_values.end() ? static_cast<size_type_t>(std::distance(max_values.begin(), item)) : size_type_t::_8_bytes;
    }

    constexpr std::uint8_t bytes(const size_type_t size_type) noexcept
    {
        return static_cast<std::uint8_t>(1u << +size_type);
    }

    constexpr std::uint8_t offset_bytes(const offset_t offset) noexcept
    {
        return bytes(size_type_of(offset));
    }

    enum class action_t : std::uint8_t
    {
        request,
        request_cancel,
        response,
    };

    using schema_t = std::uint8_t;
    using call_count_t = std::uint8_t;

    union primary_header
    {
        using value_t = std::uint8_t;

        value_t data {};
        struct
        {
            value_t action : 3, encoding_scheme : 5;
        } fields;

        constexpr primary_header() noexcept = default;
        constexpr primary_header(const action_t action, const std::uint8_t encoding_scheme) noexcept
        {
            fields.action = +action;
            fields.encoding_scheme = encoding_scheme & 0b11111;
        }

        action_t action() const noexcept { return static_cast<action_t>(fields.action); }
        std::uint8_t encoding_scheme() const noexcept { return static_cast<std::uint8_t>(fields.encoding_scheme); }
    };
}
