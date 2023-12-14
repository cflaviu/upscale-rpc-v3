#pragma once
#include <kmx/upscale_rpc/basic_types.hpp>
#include <kmx/upscale_rpc/request/decoding/result.hpp>

namespace kmx::upscale_rpc::request::decoding::raw_decoder
{
    template <typename _PayloadSize, typename _ContextId>
    class base
    {
    public:
        using context_id_t = _ContextId;
        using payload_size_t = _PayloadSize;

    protected:
        void setup(const c_raw_data_t& input_buffer, const alignment_t alignment)
        {
            begin_ = input_buffer.data();
            ptr_ = input_buffer.data() + sizeof(primary_header);
            end_ = input_buffer.data() + input_buffer.size();
            alignment_ = alignment;
        }

        template <typename T>
        void padding() noexcept
        {
            ptr_ = align_forward(ptr_, sizeof(T));
        }

        void alignment_padding() noexcept { ptr_ = align_forward(ptr_, alignment_); }

        void set_payload_size()
        {
            padding<payload_size_t>();
            payload_size_ = as_cref<payload_size_t>(ptr_);
            ptr_ += sizeof(payload_size_t);
            payload_ptr_ = ptr_;
        }

        void set_context_id(result& output) noexcept
        {
            padding<context_id_t>();
            output.context = as_cref<context_id_t>(ptr_);
            ptr_ += sizeof(context_id_t);
        }

        const std::uint8_t* payload_ptr_ {};
        const std::uint8_t* begin_ {};
        const std::uint8_t* ptr_ {};
        const std::uint8_t* end_ {};
        payload_size_t payload_size_ {};
        alignment_t alignment_ {};
    };
}
