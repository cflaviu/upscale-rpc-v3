#pragma once
#include <kmx/upscale_rpc/basic_types.hpp>

namespace kmx::upscale_rpc::request::decoding
{
    struct result
    {
        object_method_id_vector_t methods {};
        c_raw_data_vector_t call_data {};
        std::uint32_t context {};
    };
}
