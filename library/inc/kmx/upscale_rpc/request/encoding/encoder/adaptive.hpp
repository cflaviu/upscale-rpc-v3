#pragma once
#include <kmx/upscale_rpc/request/encoding/encoder/base.hpp>

namespace kmx::upscale_rpc::request::encoding::encoder
{
    template <typename _ContextId>
    class adaptive: public base<_ContextId>
    {
    public:
        using parent = base<_ContextId>;
        using typename parent::context_id_t;

        void operator()(const object_method_id_vector_t& methods, const c_raw_data_vector_t& call_data, const context_id_t context)
        {
            std::size_t packet_size;
            const auto schema = select_schema(call_data, packet_size);
            if (schema)
            {
                schema_ = *schema;
                output_buffer_.resize(packet_size);
                const raw_data_t output_buffer_span {output_buffer_.data(), packet_size};
                switch (*schema)
                {
                    using enum request::schema_t;
                    case single_0:
                    {
                        raw_encoder::single<std::uint8_t, std::uint8_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_0, alignment_);
                        break;
                    }
                    case single_1:
                    {
                        raw_encoder::single<std::uint16_t, std::uint8_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_1, alignment_);
                        break;
                    }
                    case single_2:
                    {
                        raw_encoder::single<std::uint8_t, std::uint16_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_2, alignment_);
                        break;
                    }
                    case single_3:
                    {
                        raw_encoder::single<std::uint16_t, std::uint16_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_3, alignment_);
                        break;
                    }
                    case single_4:
                    {
                        raw_encoder::single<std::uint32_t, std::uint16_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_4, alignment_);
                        break;
                    }
                    case single_5:
                    {
                        raw_encoder::single<std::uint8_t, std::uint32_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_5, alignment_);
                        break;
                    }
                    case single_6:
                    {
                        raw_encoder::single<std::uint16_t, std::uint32_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_6, alignment_);
                        break;
                    }
                    case single_7:
                    {
                        raw_encoder::single<std::uint32_t, std::uint32_t> item {};
                        item(output_buffer_span, methods.front(), call_data.front(), context, schema_t::single_7, alignment_);
                        break;
                    }
                    case aggregate_0:
                    {
                        raw_encoder::aggregate<std::uint8_t, std::uint8_t, std::uint8_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_0, alignment_);
                        break;
                    }
                    case aggregate_1:
                    {
                        raw_encoder::aggregate<std::uint16_t, std::uint8_t, std::uint8_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_1, alignment_);
                        break;
                    }
                    case aggregate_2:
                    {
                        raw_encoder::aggregate<std::uint32_t, std::uint8_t, std::uint16_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_2, alignment_);
                        break;
                    }
                    case aggregate_3:
                    {
                        raw_encoder::aggregate<std::uint32_t, std::uint8_t, std::uint32_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_3, alignment_);
                        break;
                    }
                    case aggregate_4:
                    {
                        raw_encoder::aggregate<std::uint16_t, std::uint16_t, std::uint16_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_4, alignment_);
                        break;
                    }
                    case aggregate_5:
                    {
                        raw_encoder::aggregate<std::uint32_t, std::uint16_t, std::uint16_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_5, alignment_);
                        break;
                    }
                    case aggregate_6:
                    {
                        raw_encoder::aggregate<std::uint32_t, std::uint16_t, std::uint32_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_6, alignment_);
                        break;
                    }
                    case aggregate_7:
                    {
                        raw_encoder::aggregate<std::uint8_t, std::uint32_t, std::uint8_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_7, alignment_);
                        break;
                    }
                    case aggregate_8:
                    {
                        raw_encoder::aggregate<std::uint16_t, std::uint32_t, std::uint16_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_8, alignment_);
                        break;
                    }
                    case aggregate_9:
                    {
                        raw_encoder::aggregate<std::uint32_t, std::uint32_t, std::uint16_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_9, alignment_);
                        break;
                    }
                    case aggregate_10:
                    {
                        raw_encoder::aggregate<std::uint32_t, std::uint32_t, std::uint32_t> item {};
                        item(output_buffer_span, methods, call_data, context, schema_t::aggregate_10, alignment_);
                        break;
                    }
                }
            }
        }

    private:
        using parent::alignment_;
        using parent::output_buffer_;
        using parent::schema_;

        std::optional<request::schema_t> select_schema(const c_raw_data_vector_t& call_data, std::size_t& packet_size) const
        {
            std::size_t call_data_size, max_call_data_size;
            get_call_data_size(call_data_size, max_call_data_size, call_data, alignment_);

            auto packet_size_type = size_type_of(call_data_size);
            auto call_data_size_type = size_type_of(max_call_data_size);

            std::optional<request::schema_t> result {};
            if (get_packet_size<context_id_t>(packet_size, packet_size_type, call_data_size_type, max_call_data_size, call_data,
                                              alignment_))
            {
                const auto last_packet_size_type = size_type_of(packet_size);
                if (last_packet_size_type != packet_size_type)
                {
                    get_packet_size<context_id_t>(packet_size, last_packet_size_type, call_data_size_type, max_call_data_size, call_data,
                                                  alignment_);
                    packet_size_type = size_type_of(packet_size);
                }

                const auto context_id_size = get_context_size<context_id_t>();
                result = call_data.size() > 1u ? get_aggregate_schema(context_id_size, packet_size_type, call_data_size_type) :
                                                 get_single_schema(context_id_size, packet_size_type);
            }

            return result;
        }
    };
}
