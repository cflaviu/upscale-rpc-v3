#pragma once
#include <kmx/upscale_rpc/request/decoding/raw_decoder/base.hpp>
#include <stdexcept>

namespace kmx::upscale_rpc::request::decoding::raw_decoder
{
    template <typename _PayloadSize, typename _ContextId>
    class single: public base<_PayloadSize, _ContextId>
    {
    public:
        using parent = base<_PayloadSize, _ContextId>;

        void operator()(const c_raw_data_t input_buffer, const alignment_t alignment, result& output)
        {
            setup(input_buffer, alignment);
            set_payload_size();
            check_payload_size();
            set_context_id(output);
            set_object_method(output);
            set_call_data(output);
        }

    private:
        using parent::alignment_;
        using parent::alignment_padding;
        using parent::begin_;
        using parent::end_;
        using parent::padding;
        using parent::payload_ptr_;
        using parent::payload_size_;
        using parent::ptr_;
        using parent::set_context_id;
        using parent::set_payload_size;
        using parent::setup;
        using typename parent::context_id_t;

        void check_payload_size()
        {
            const auto dist = std::distance(ptr_, end_);
            if (payload_size_ != dist)
            {
                throw std::runtime_error("payload size mismatch");
            }

            const offset_t min_size = sizeof(context_id_t) + sizeof(object_method_id_t);
            if (payload_size_ < min_size)
            {
                throw std::runtime_error("payload incomplete");
            }
        }

        void set_object_method(result& output)
        {
            parent::template padding<object_method_id_t>();
            output.methods.resize(1u);
            output.methods.front() = as_cref<object_method_id_t>(ptr_);
            ptr_ += sizeof(object_method_id_t);
        }

        void set_call_data(result& output)
        {
            alignment_padding();
            const auto dist = std::distance(payload_ptr_, ptr_);
            const auto data_size = payload_size_ - dist;
            if (ptr_ + data_size > end_)
            {
                throw std::runtime_error("wrong payload size");
            }

            output.call_data.resize(1u);
            auto& item = output.call_data.front();
            item = c_raw_data_t {ptr_, static_cast<std::size_t>(data_size)};
        }
    };
}
