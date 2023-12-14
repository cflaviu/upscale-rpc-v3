#pragma once
#include <kmx/upscale_rpc/basic_types.hpp>

namespace kmx::upscale_rpc::request
{
    inline void get_call_data_size(std::size_t& call_data_size, std::size_t& max_call_data_size, const c_raw_data_vector_t& data,
                                      const alignment_t alignment = 8u) noexcept
    {
        call_data_size = 0u;
        max_call_data_size = 0u;
        for (const auto& item: data)
        {
            call_data_size += call_data_size % alignment;
            call_data_size += item.size();

            if (item.size() > max_call_data_size)
            {
                max_call_data_size = item.size();
            }
        }
    }

    enum class get_packet_size_error_t : std::uint8_t
    {
        none,
        call_data_exceeds_type,
        payload_exceeds_type,
    };

    template <typename _ContextId>
    constexpr bool get_packet_size(std::size_t& packet_size, const size_type_t packet_size_type, const size_type_t call_data_size_type,
                                   const std::size_t max_call_data_size, const c_raw_data_vector_t& data,
                                   const alignment_t alignment = 8u) noexcept
    {
        if (max_call_data_size > max_value_of(call_data_size_type))
        {
            return false;
        }

        const auto call_data_size_type_bytes = bytes(call_data_size_type);
        const auto packet_size_type_bytes = bytes(packet_size_type);
        packet_size = sizeof(primary_header);
        packet_size = align_forward(packet_size, packet_size_type_bytes);
        packet_size += packet_size_type_bytes;
        packet_size = align_forward(packet_size, sizeof(_ContextId));
        packet_size += sizeof(_ContextId);
        if (data.size() > 1u)
        {
            packet_size += sizeof(call_count_t);
            packet_size = align_forward(packet_size, sizeof(object_method_id_t));
            packet_size += data.size() * sizeof(object_method_id_t);
            packet_size = align_forward(packet_size, call_data_size_type_bytes);
            packet_size += data.size() * call_data_size_type_bytes;
            for (auto& item: data)
            {
                packet_size = align_forward(packet_size, alignment);
                packet_size += item.size();
            }
        }
        else
        {
            packet_size = align_forward(packet_size, sizeof(object_method_id_t));
            packet_size += data.size() * sizeof(object_method_id_t);
            packet_size = align_forward(packet_size, alignment);
            packet_size += data.front().size();
        }

        return packet_size <= max_value_of(packet_size_type);
    }

    //    template <typename _PayloadSize, typename _ContextId, typename _CallDataSize = _PayloadSize>
    //    constexpr get_packet_size_error_t get_packet_size(std::size_t& packet_size, const std::size_t call_data_size,
    //                                                      const std::size_t max_call_data_size, const c_raw_data_vector_t& data,
    //                                                      const alignment_t alignment = 8u) noexcept
    //    {
    //        if (max_call_data_size > std::numeric_limits<_CallDataSize>::max())
    //        {
    //            return get_packet_size_error_t::call_data_exceeds_type;
    //        }

    //        packet_size = sizeof(primary_header);
    //        packet_size = align_forward(packet_size, sizeof(_PayloadSize));
    //        packet_size += sizeof(_PayloadSize);
    //        packet_size = align_forward(packet_size, sizeof(_ContextId));
    //        packet_size += sizeof(_ContextId) + sizeof(call_count_t);
    //        packet_size = align_forward(packet_size, sizeof(object_method_id_t));
    //        packet_size += data.size() * sizeof(object_method_id_t);
    //        packet_size = align_forward(packet_size, sizeof(_CallDataSize));
    //        packet_size += data.size() * sizeof(_CallDataSize);
    //        packet_size = align_forward(packet_size, alignment);
    //        packet_size += call_data_size;
    //        return (packet_size <= std::numeric_limits<_PayloadSize>::max()) ? get_packet_size_error_t::none :
    //                                                                           get_packet_size_error_t::payload_exceeds_type;
    //    }

#if 0
    template <typename _PayloadSize, typename _ContextId = std::uint16_t, typename _CallDataSize = _PayloadSize>
    constexpr get_packet_size_error_t get_packet_size(std::size_t& packet_size, std::size_t& max_call_data_size,
                                                        const c_raw_data_vector_t& data, const alignment_t alignment = 8u) noexcept
    {
        std::size_t call_data_size;
        get_call_data_size(call_data_size, max_call_data_size);
        return get_packet_size(packet_size, call_data_size, max_call_data_size, data, alignment);
    }
#endif
}
