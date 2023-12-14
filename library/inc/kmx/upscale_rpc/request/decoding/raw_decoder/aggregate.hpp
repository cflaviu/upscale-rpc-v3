#pragma once
#include <kmx/upscale_rpc/request/decoding/raw_decoder/base.hpp>
#include <stdexcept>

namespace kmx::upscale_rpc::request::decoding::raw_decoder
{
    template <typename _PayloadSize, typename _ContextId, typename _CallDataSize>
    class aggregate: public base<_PayloadSize, _ContextId>
    {
    public:
        using parent = base<_PayloadSize, _ContextId>;
        using call_data_size_t = _CallDataSize;

        void operator()(const c_raw_data_t& input_buffer, const alignment_t alignment, result& output)
        {
            setup(input_buffer, alignment);
            set_payload_size();
            check_payload_size();
            set_context_id(output);
            set_call_count(output);
            set_object_methods(output);
            set_call_data_sizes(output);
            set_call_data(output);
        }

    private:
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
            if (payload_size_ != std::distance(ptr_, end_))
            {
                throw std::runtime_error("payload size mismatch");
            }

            const offset_t min_size =
                sizeof(context_id_t) + sizeof(call_count_t) + 2u * sizeof(object_method_id_t) + 2u * sizeof(call_data_size_t);
            if (payload_size_ < min_size)
            {
                throw std::runtime_error("payload incomplete");
            }
        }

        void set_call_count(result& output)
        {
            const auto count = as_cref<call_count_t>(ptr_);
            output.call_data.resize(count);
            output.methods.resize(count);
            ptr_ += sizeof(call_count_t);
        }

        void set_object_methods(result& output)
        {
            parent::template padding<object_method_id_t>();
            const auto bytes = sizeof(object_method_id_t) * output.methods.size();
            std::memcpy(reinterpret_cast<std::uint8_t*>(output.methods.data()), ptr_, bytes);
            ptr_ += bytes;
        }

        void set_call_data_sizes(result& output) noexcept
        {
            parent::template padding<call_data_size_t>();
            for (auto& item: output.call_data)
            {
                item = c_raw_data_t(static_cast<const std::uint8_t*>(nullptr), as_cref<call_data_size_t>(ptr_));
                ptr_ += sizeof(call_data_size_t);
            }
        }

        void set_call_data(result& output)
        {
            for (auto& item: output.call_data)
            {
                alignment_padding();
                const auto size = item.size();
                item = {ptr_, size};
                ptr_ += size;
            }

            const auto dist = std::distance(payload_ptr_, ptr_);
            if (payload_size_ != dist)
            {
                throw std::runtime_error("wrong payload size");
            }
        }
    };
}
