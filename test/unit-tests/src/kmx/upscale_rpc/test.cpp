#include <catch2/catch.hpp>
#include <kmx/upscale_rpc/request/decoding/decoder.hpp>
#include <kmx/upscale_rpc/request/encoding/encoder/adaptive.hpp>
#include <kmx/upscale_rpc/request/encoding/encoder/fixed.hpp>

namespace kmx::upscale_rpc::request
{
    using buffer_t = std::vector<std::uint8_t>;
    using decoder_t = decoding::decoder;

#if 1
    TEST_CASE("encode-decode single uint16")
    {
        using context_id_t = std::uint16_t;
        using encoder_t = encoding::encoder::adaptive<context_id_t>;

        buffer_t encoded_data {};

        const object_method_id_vector_t methods {object_method_id_t {1u, 3u}};
        const buffer_t b1(300u, std::uint8_t(0xAu));
        const c_raw_data_vector_t call_data {to_cspan(b1)};
        const context_id_t context_id = 10u;

        {

            encoder_t encoder {};
            encoder(methods, call_data, context_id);

            REQUIRE(encoder.schema() == request::schema_t::single_3);

            auto data = encoder.data();
            REQUIRE(data.size() == 308u);

            encoded_data.assign(data.begin(), data.end());
        }

        {
            decoder_t decoder {};
            decoding::result result {};
            const c_raw_data_t input(encoded_data.data(), encoded_data.size());
            decoder(input, result);
            REQUIRE(result.call_data.size() == methods.size());
            REQUIRE(result.methods.size() == methods.size());
            REQUIRE(result.methods == methods);

            for (std::size_t i = 0; i != call_data.size(); ++i)
            {
                REQUIRE(same_data(result.call_data[i], call_data[i]));
            }
        }
    }

    TEST_CASE("encode-decode multiple uint16")
    {
        using context_id_t = std::uint16_t;
        using encoder_t = encoding::encoder::adaptive<context_id_t>;

        buffer_t encoded_data {};

        const object_method_id_vector_t methods {object_method_id_t {1u, 3u}, object_method_id_t {1u, 10u}, object_method_id_t {1u, 15u}};
        const buffer_t b1(300u, std::uint8_t(0xAu));
        const buffer_t b2(700u, std::uint8_t(0xBu));
        const buffer_t b3(500u, std::uint8_t(0xCu));
        const c_raw_data_vector_t call_data {to_cspan(b1), to_cspan(b2), to_cspan(b3)};
        const context_id_t context_id = 10u;

        {

            encoder_t encoder {};
            encoder(methods, call_data, context_id);

            REQUIRE(encoder.schema() == request::schema_t::aggregate_4);

            auto data = encoder.data();
            REQUIRE(data.size() == 1532u);

            encoded_data.assign(data.begin(), data.end());
        }

        {
            decoder_t decoder {};
            decoding::result result {};
            const c_raw_data_t input(encoded_data.data(), encoded_data.size());
            decoder(input, result);
            REQUIRE(result.call_data.size() == methods.size());
            REQUIRE(result.methods.size() == methods.size());
            REQUIRE(result.methods == methods);
            REQUIRE(same_data(result.call_data[0u], call_data[0u]));
            REQUIRE(same_data(result.call_data[1u], call_data[1u]));
            REQUIRE(same_data(result.call_data[2u], call_data[2u]));
        }
    }

    TEST_CASE("encode-decode uint8")
    {
        using context_id_t = std::uint8_t;
        using encoder_t = encoding::encoder::adaptive<context_id_t>;

        buffer_t encoded_data {};

        const object_method_id_vector_t methods {object_method_id_t {1u, 3u}, object_method_id_t {1u, 10u}, object_method_id_t {1u, 15u}};
        const buffer_t b1(20u, std::uint8_t(0xAu));
        const buffer_t b2(50u, std::uint8_t(0xBu));
        const buffer_t b3(30u, std::uint8_t(0xCu));
        const c_raw_data_vector_t call_data {to_cspan(b1), to_cspan(b2), to_cspan(b3)};
        const context_id_t context_id = 10u;

        {

            encoder_t encoder {};
            encoder(methods, call_data, context_id);

            REQUIRE(encoder.schema() == request::schema_t::aggregate_0);

            auto data = encoder.data();
            REQUIRE(data.size() == 126u);

            encoded_data.assign(data.begin(), data.end());
        }

        {
            decoder_t decoder {};
            decoding::result result {};
            const c_raw_data_t input(encoded_data.data(), encoded_data.size());
            decoder(input, result);
            REQUIRE(result.call_data.size() == methods.size());
            REQUIRE(result.methods.size() == methods.size());
            REQUIRE(result.methods == methods);
            REQUIRE(same_data(result.call_data[0u], call_data[0u]));
            REQUIRE(same_data(result.call_data[1u], call_data[1u]));
            REQUIRE(same_data(result.call_data[2u], call_data[2u]));
        }
    }

    TEST_CASE("encode-decode uint8 2")
    {
        using context_id_t = std::uint8_t;
        using encoder_t = encoding::encoder::adaptive<context_id_t>;

        buffer_t encoded_data {};

        const buffer_t b01(10u, std::uint8_t(0x1u));
        const buffer_t b02(10u, std::uint8_t(0x2u));
        const buffer_t b03(10u, std::uint8_t(0x3u));
        const buffer_t b04(10u, std::uint8_t(0x4u));
        const buffer_t b05(10u, std::uint8_t(0x5u));
        const buffer_t b06(10u, std::uint8_t(0x6u));
        const buffer_t b07(10u, std::uint8_t(0x7u));
        const buffer_t b08(10u, std::uint8_t(0x8u));
        const buffer_t b09(10u, std::uint8_t(0x9u));
        const buffer_t b10(10u, std::uint8_t(0xAu));
        const buffer_t b11(10u, std::uint8_t(0xBu));
        const buffer_t b12(10u, std::uint8_t(0xCu));
        const c_raw_data_vector_t call_data {to_cspan(b01), to_cspan(b02), to_cspan(b03), to_cspan(b04), to_cspan(b05), to_cspan(b06),
                                             to_cspan(b07), to_cspan(b08), to_cspan(b09), to_cspan(b10), to_cspan(b11), to_cspan(b12)};
        object_method_id_vector_t methods {};
        for (std::size_t i {}; i != call_data.size(); ++i)
        {
            methods.emplace_back(0u, i);
        }

        const context_id_t context_id = 10u;

        {

            encoder_t encoder {};
            encoder(methods, call_data, context_id);

            REQUIRE(encoder.schema() == request::schema_t::aggregate_0);

            auto data = encoder.data();
            REQUIRE(data.size() == 226u);

            encoded_data.assign(data.begin(), data.end());
        }

        {
            decoder_t decoder {};
            decoding::result result {};
            const c_raw_data_t input(encoded_data.data(), encoded_data.size());
            decoder(input, result);
            REQUIRE(result.call_data.size() == methods.size());
            REQUIRE(result.methods.size() == methods.size());
            REQUIRE(result.methods == methods);
            for (std::size_t i {}; i != call_data.size(); ++i)
            {
                REQUIRE(same_data(result.call_data[i], call_data[i]));
            }
        }
    }
#endif
}
