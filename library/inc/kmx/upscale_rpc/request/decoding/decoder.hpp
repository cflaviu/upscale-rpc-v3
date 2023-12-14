#pragma once
#include <kmx/upscale_rpc/request/decoding/raw_decoder/aggregate.hpp>
#include <kmx/upscale_rpc/request/decoding/raw_decoder/single.hpp>
#include <kmx/upscale_rpc/request/decoding/result.hpp>
#include <kmx/upscale_rpc/request/schema.hpp>

namespace kmx::upscale_rpc::request::decoding
{
    class decoder
    {
    public:
        request::schema_t schema() const noexcept { return schema_; }

        void operator()(const c_raw_data_t& input_buffer, result& output, const alignment_t alignment = 8u)
        {
            const primary_header& header = as_cref<primary_header>(input_buffer.data());
            schema_ = static_cast<request::schema_t>(header.encoding_scheme());
            switch (schema_)
            {
                using enum request::schema_t;
                case single_0:
                {
                    raw_decoder::single<std::uint8_t, std::uint8_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case single_1:
                {
                    raw_decoder::single<std::uint16_t, std::uint8_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case single_2:
                {
                    raw_decoder::single<std::uint8_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case single_3:
                {
                    raw_decoder::single<std::uint16_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case single_4:
                {
                    raw_decoder::single<std::uint32_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case single_5:
                {
                    raw_decoder::single<std::uint8_t, std::uint32_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case single_6:
                {
                    raw_decoder::single<std::uint16_t, std::uint32_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case single_7:
                {
                    raw_decoder::single<std::uint32_t, std::uint32_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_0:
                {
                    raw_decoder::aggregate<std::uint8_t, std::uint8_t, std::uint8_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_1:
                {
                    raw_decoder::aggregate<std::uint16_t, std::uint8_t, std::uint8_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_2:
                {
                    raw_decoder::aggregate<std::uint32_t, std::uint8_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_3:
                {
                    raw_decoder::aggregate<std::uint32_t, std::uint8_t, std::uint32_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_4:
                {
                    raw_decoder::aggregate<std::uint16_t, std::uint16_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_5:
                {
                    raw_decoder::aggregate<std::uint32_t, std::uint16_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_6:
                {
                    raw_decoder::aggregate<std::uint32_t, std::uint16_t, std::uint32_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_7:
                {
                    raw_decoder::aggregate<std::uint8_t, std::uint32_t, std::uint8_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_8:
                {
                    raw_decoder::aggregate<std::uint16_t, std::uint32_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_9:
                {
                    raw_decoder::aggregate<std::uint32_t, std::uint32_t, std::uint16_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
                case aggregate_10:
                {
                    raw_decoder::aggregate<std::uint32_t, std::uint32_t, std::uint32_t> item {};
                    item(input_buffer, alignment, output);
                    break;
                }
            }
        }

    private:
        request::schema_t schema_ {};
    };
}
