#pragma once
#include <kmx/upscale_rpc/basic_types.hpp>

namespace kmx::upscale_rpc::response::encoding::raw_encoder
{
    template <typename _PayloadSize>
    class base
    {
    public:
        using payload_size_t = _PayloadSize;

    protected:
        void setup(const raw_data_t& output_buffer, const alignment_t alignment)
        {
            if (alignment != 4u && alignment != 8u)
                throw std::runtime_error("unsupported alignment");

            begin_ = output_buffer.data();
            ptr_ = output_buffer.data();
            end_ = output_buffer.data() + output_buffer.size();
        }

        void set_primary_header(const schema_t schema) noexcept
        {
            as_ref<primary_header>(ptr_) = primary_header(action_t::request, +schema);
            ptr_ += sizeof(primary_header);
        }

        template <typename T>
        void padding() noexcept
        {
            ptr_ = align_forward(ptr_, sizeof(T));
        }

        void padding(const alignment_t alignment) noexcept { ptr_ = align_forward(ptr_, alignment); }

        void set_payload_size()
        {
            const auto payload_size = std::distance(payload_ptr_, ptr_);
            if (payload_size <= std::numeric_limits<payload_size_t>::max())
                *payload_size_ = static_cast<payload_size_t>(payload_size);
            else
                throw std::runtime_error("payload size type too small");
        }

        payload_size_t* payload_size_ {};
        std::uint8_t* begin_ {};
        std::uint8_t* ptr_ {};
        std::uint8_t* end_ {};
        std::uint8_t* payload_ptr_ {};
    };
}
