#pragma once
#include <kmx/upscale_rpc/basic_types.hpp>
#include <kmx/upscale_rpc/request/encoding/payload_size.hpp>
#include <kmx/upscale_rpc/request/encoding/raw_encoder/aggregate.hpp>
#include <kmx/upscale_rpc/request/encoding/raw_encoder/single.hpp>
#include <kmx/upscale_rpc/request/schema.hpp>

namespace kmx::upscale_rpc::request::encoding::encoder
{
    template <typename _ContextId>
    class base
    {
    public:
        using context_id_t = _ContextId;
        using buffer_t = std::vector<std::uint8_t>;

        schema_t schema() const noexcept { return schema_; }

        alignment_t alignment() const noexcept { return alignment_; }
        void set_alignment(const alignment_t item) { alignment_ = item; }

        c_raw_data_t data() const noexcept { return {output_buffer_.data(), output_buffer_.size()}; }

    protected:
        buffer_t output_buffer_ {};
        schema_t schema_ {};
        alignment_t alignment_ {8u};
    };
}
