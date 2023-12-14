#pragma once
#include <kmx/upscale_rpc/request/encoding/raw_encoder/base.hpp>

namespace kmx::upscale_rpc::request::encoding::raw_encoder
{
    template <typename _PayloadSize, typename _ContextId>
    class single: public base<_PayloadSize>
    {
    public:
        using parent = base<_PayloadSize>;
        using context_id_t = _ContextId;

        void operator()(const raw_data_t& output_buffer, const object_method_id_t method, const c_raw_data_t& call_data,
                        const context_id_t context, const schema_t schema, const alignment_t alignment)
        {
            setup(output_buffer, alignment);
            set_primary_header(schema);
            set_payload_size_context_id_call_count(context);
            set_object_methods(method);
            set_call_data(call_data, alignment);
        }

    private:
        using parent::padding;
        using parent::payload_ptr_;
        using parent::payload_size_;
        using parent::ptr_;
        using parent::set_payload_size;
        using parent::set_primary_header;
        using parent::setup;
        using typename parent::payload_size_t;

        void set_payload_size_context_id_call_count(const context_id_t context)
        {
            parent::template padding<payload_size_t>();
            payload_size_ = as_ptr<payload_size_t>(ptr_);
            ptr_ += sizeof(payload_size_t);
            payload_ptr_ = ptr_;

            parent::template padding<context_id_t>();
            as_ref<context_id_t>(ptr_) = context;
            ptr_ += sizeof(context_id_t);
        }

        void set_object_methods(const object_method_id_t method)
        {
            parent::template padding<object_method_id_t>();
            std::memcpy(ptr_, reinterpret_cast<const void*>(&method), sizeof(object_method_id_t));
            ptr_ += sizeof(object_method_id_t);
        }

        void set_call_data(const c_raw_data_t& call_data, const alignment_t alignment)
        {
            padding(alignment);
            std::memcpy(ptr_, call_data.data(), call_data.size());
            ptr_ += call_data.size();

            set_payload_size();
        }
    };
}
