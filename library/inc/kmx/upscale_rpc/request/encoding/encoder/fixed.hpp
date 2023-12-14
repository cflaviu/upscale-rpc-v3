#pragma once
#include <kmx/upscale_rpc/request/encoding/encoder/base.hpp>

namespace kmx::upscale_rpc::request::encoding::encoder
{
    template <typename _PayloadSize, typename _ContextId, typename _CallDataSize>
    class fixed: public base<_ContextId>
    {
    public:
        using parent = base<_ContextId>;
        using payload_size_t = _PayloadSize;
        using context_id_t = _ContextId;
        using call_data_size_t = _CallDataSize;

        void operator()(const object_method_id_vector_t& methods, const c_raw_data_vector_t& call_data, const context_id_t context)
        {
            if (call_data.size() > 1u)
            {
                aggregate_encoder_t encoder {};
                encoder(output_buffer_, methods, call_data, context, aggregate_schema_, alignment_);
            }
            else
            {
                single_encoder_t encoder {};
                encoder(output_buffer_, methods.front(), call_data.front(), context, single_schema_, alignment_);
            }
        }

    private:
        using parent::alignment_;
        using parent::output_buffer_;
        using aggregate_encoder_t = raw_encoder::aggregate<payload_size_t, context_id_t, call_data_size_t>;
        using single_encoder_t = raw_encoder::single<payload_size_t, context_id_t>;

        static constexpr size_type_t payload_size_type_ = get_context_size<payload_size_t>();
        static constexpr size_type_t context_id_size_ = get_context_size<context_id_t>();
        static constexpr size_type_t call_data_size_type_ = get_context_size<call_data_size_t>();
        static constexpr std::optional<request::schema_t> aggregate_schema_ =
            get_aggregate_schema(context_id_size_, payload_size_type_, call_data_size_type_);
        static constexpr std::optional<request::schema_t> single_schema_ = get_single_schema(context_id_size_, payload_size_type_);
    };
}
