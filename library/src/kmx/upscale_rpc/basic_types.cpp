// Upscale RPC library
// Copyright (C) 2022 Flaviu C.
#include <cstring>
#include <kmx/upscale_rpc/basic_types.hpp>

namespace kmx::upscale_rpc
{
    bool same_data(const c_raw_data_t& lhs, const c_raw_data_t& rhs) noexcept
    {
        return std::memcmp(lhs.data(), rhs.data(), std::min(lhs.size(), rhs.size())) == 0;
    }
}
