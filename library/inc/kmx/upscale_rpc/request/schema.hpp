#pragma once
#include <kmx/upscale_rpc/basic_types.hpp>

namespace kmx::upscale_rpc::request
{
    enum class schema_t : std::uint8_t
    {
        single_0, // <1o:conext-id><1o:payload-size> 1 1
        single_1, // <1o:conext-id><2o:payload-size> 1 2 / 2 1
        single_2, // <2o:conext-id><1o:payload-size> 2 1 / 1 2
        single_3, // <2o:conext-id><2o:payload-size> 2 2
        single_4, // <2o:conext-id><4o:payload-size> 2 4 / 4 2
        single_5, // <4o:conext-id><1o:payload-size> 4 1 / 1 4
        single_6, // <4o:conext-id><2o:payload-size> 4 2 / 2 4
        single_7, // <4o:conext-id><4o:payload-size> 4 4 / 4 4

        aggregate_0,  // <1o:conext-id><1o:payload-size><1o:call-count><1o:call-data-size> 1 1 1
        aggregate_1,  // <1o:conext-id><2o:payload-size><1o:call-count><2o:call-data-size> 1 2 2 / 2 1 1
        aggregate_2,  // <1o:conext-id><4o:payload-size><1o:call-count><2o:call-data-size> 1 4 2 / 4 1 2
        aggregate_3,  // <1o:conext-id><4o:payload-size><1o:call-count><4o:call-data-size> 1 4 4 / 4 1 4
        aggregate_4,  // <2o:conext-id><2o:payload-size><1o:call-count><2o:call-data-size> 2 2 2 / 2 2 2
        aggregate_5,  // <2o:conext-id><4o:payload-size><1o:call-count><2o:call-data-size> 2 4 2 / 4 2 2
        aggregate_6,  // <2o:conext-id><4o:payload-size><1o:call-count><4o:call-data-size> 2 4 4 / 4 2 4
        aggregate_7,  // <4o:conext-id><1o:payload-size><1o:call-count><1o:call-data-size> 4 1 1 / 1 4 1
        aggregate_8,  // <4o:conext-id><2o:payload-size><1o:call-count><2o:call-data-size> 4 2 2 / 2 4 2
        aggregate_9,  // <4o:conext-id><4o:payload-size><1o:call-count><2o:call-data-size> 4 4 2 / 4 4 2
        aggregate_10, // <4o:conext-id><4o:payload-size><1o:call-count><4o:call-data-size> 4 4 4 / 4 4 4
    };

    constexpr std::optional<schema_t> get_single_schema(const size_type_t context_id_size, const size_type_t payload_size) noexcept
    {
        switch (context_id_size)
        {
            case size_type_t::_1_byte:
                switch (payload_size)
                {
                    case size_type_t::_1_byte:
                        return schema_t::single_0;
                    case size_type_t::_2_bytes:
                        return schema_t::single_1;
                    default:;
                }
                break;
            case size_type_t::_2_bytes:
                switch (payload_size)
                {
                    case size_type_t::_1_byte:
                        return schema_t::single_2;
                    case size_type_t::_2_bytes:
                        return schema_t::single_3;
                    case size_type_t::_4_bytes:
                        return schema_t::single_4;
                    default:;
                }
                break;
            case size_type_t::_4_bytes:
                switch (payload_size)
                {
                    case size_type_t::_1_byte:
                        return schema_t::single_5;
                    case size_type_t::_2_bytes:
                        return schema_t::single_6;
                    case size_type_t::_4_bytes:
                        return schema_t::single_7;
                    default:;
                }
                break;
            default:;
        }

        return {};
    }

    constexpr std::optional<schema_t> get_aggregate_schema(const size_type_t context_id_size, const size_type_t payload_size,
                                                           const size_type_t call_data_size) noexcept
    {
        switch (context_id_size)
        {
            case size_type_t::_1_byte:
                switch (payload_size)
                {
                    case size_type_t::_1_byte:
                        switch (call_data_size)
                        {
                            case size_type_t::_1_byte:
                                return schema_t::aggregate_0;
                            default:;
                        }
                        break;
                    case size_type_t::_2_bytes:
                        switch (call_data_size)
                        {
                            case size_type_t::_2_bytes:
                                return schema_t::aggregate_1;
                            default:;
                        }
                        break;
                    case size_type_t::_4_bytes:
                        switch (call_data_size)
                        {
                            case size_type_t::_2_bytes:
                                return schema_t::aggregate_2;
                            case size_type_t::_4_bytes:
                                return schema_t::aggregate_3;
                            default:;
                        }
                        break;
                    default:;
                }
                break;
            case size_type_t::_2_bytes:
                switch (payload_size)
                {
                    case size_type_t::_2_bytes:
                        switch (call_data_size)
                        {
                            case size_type_t::_2_bytes:
                                return schema_t::aggregate_4;
                            default:;
                        }
                        break;
                    case size_type_t::_4_bytes:
                        switch (call_data_size)
                        {
                            case size_type_t::_2_bytes:
                                return schema_t::aggregate_5;
                            case size_type_t::_4_bytes:
                                return schema_t::aggregate_6;
                            default:;
                        }
                        break;
                    default:;
                }
                break;
            case size_type_t::_4_bytes:
                switch (payload_size)
                {
                    case size_type_t::_1_byte:
                        switch (call_data_size)
                        {
                            case size_type_t::_1_byte:
                                return schema_t::aggregate_7;
                            default:;
                        }
                        break;
                    case size_type_t::_2_bytes:
                        switch (call_data_size)
                        {
                            case size_type_t::_2_bytes:
                                return schema_t::aggregate_8;
                            default:;
                        }
                        break;
                    case size_type_t::_4_bytes:
                        switch (call_data_size)
                        {
                            case size_type_t::_2_bytes:
                                return schema_t::aggregate_9;
                            case size_type_t::_4_bytes:
                                return schema_t::aggregate_10;
                            default:;
                        }
                        break;
                    default:;
                }
                break;
            default:;
        }

        return {};
    }
}
