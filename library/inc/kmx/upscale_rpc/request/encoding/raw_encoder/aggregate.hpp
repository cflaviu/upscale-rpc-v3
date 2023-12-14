#pragma once
#include <kmx/upscale_rpc/request/encoding/raw_encoder/base.hpp>

namespace kmx::upscale_rpc::request::encoding::raw_encoder
{
    template <typename _PayloadSize, typename _ContextId, typename _CallDataSize>
    class aggregate: public base<_PayloadSize>
    {
    public:
        using parent = base<_PayloadSize>;
        using context_id_t = _ContextId;
        using call_data_size_t = _CallDataSize;

        void operator()(const raw_data_t& output_buffer, const object_method_id_vector_t& methods, const c_raw_data_vector_t& call_data,
                        const context_id_t context, const schema_t schema, const alignment_t alignment)
        {
            if (methods.size() != call_data.size())
                throw std::runtime_error("methods - call data mismatch");

            setup(output_buffer, alignment);
            set_primary_header(schema);
            link_payload_size();
            set_context_id(context);
            set_call_count(methods);
            set_object_methods(methods);
            set_call_data_sizes(call_data);
            set_call_data(call_data, alignment);
        }

    private:
        using parent::payload_ptr_;
        using parent::payload_size_;
        using parent::ptr_;
        using parent::set_payload_size;
        using parent::set_primary_header;
        using parent::setup;
        using typename parent::payload_size_t;

        void link_payload_size()
        {
            parent::template padding<payload_size_t>();
            payload_size_ = as_ptr<payload_size_t>(ptr_);
            ptr_ += sizeof(payload_size_t);
            payload_ptr_ = ptr_;
        }

        void set_context_id(const context_id_t context)
        {
            parent::template padding<context_id_t>();
            as_ref<context_id_t>(ptr_) = context;
            ptr_ += sizeof(context_id_t);
        }

        void set_call_count(const object_method_id_vector_t& methods)
        {
            // no padding
            as_ref<call_count_t>(ptr_) = static_cast<call_count_t>(methods.size());
            ptr_ += sizeof(call_count_t);
        }

        void set_object_methods(const object_method_id_vector_t& methods)
        {
            parent::template padding<object_method_id_t>();
            const auto bytes = sizeof(object_method_id_t) * methods.size();
            std::memcpy(ptr_, methods.data(), bytes);
            ptr_ += bytes;
        }

        void set_call_data_sizes(const c_raw_data_vector_t& call_data_items)
        {
            parent::template padding<call_data_size_t>();
            for (auto& call_data: call_data_items)
            {
                as_ref<call_data_size_t>(ptr_) = static_cast<call_data_size_t>(call_data.size());
                ptr_ += sizeof(call_data_size_t);
            }
        }

        void set_call_data(const c_raw_data_vector_t& call_data_items, const alignment_t alignment)
        {
            for (auto& call_data: call_data_items)
            {
                parent::padding(alignment);
                std::memcpy(ptr_, call_data.data(), call_data.size());
                ptr_ += call_data.size();
            }

            set_payload_size();
        }
    };
}
