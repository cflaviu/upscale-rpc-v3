import qbs

StaticLibrary {
    name: "upscale-rpc"
    Depends { name: 'cpp' }
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++20"
    cpp.enableRtti: false
    cpp.includePaths: ["inc", "inc_dep"]
    //cpp.cxxFlags: "-fsanitize=address"
    //cpp.staticLibraries: "asan"
    files: [
        "doc/protocol.txt",
        "inc/kmx/upscale_rpc/basic_types.hpp",
        "inc/kmx/upscale_rpc/request/decoding/raw_decoder/aggregate.hpp",
        "inc/kmx/upscale_rpc/request/decoding/raw_decoder/base.hpp",
        "inc/kmx/upscale_rpc/request/decoding/raw_decoder/single.hpp",
        "inc/kmx/upscale_rpc/request/decoding/result.hpp",
        "inc/kmx/upscale_rpc/request/schema.hpp",
        "inc/kmx/upscale_rpc/request/decoding/decoder.hpp",
        "inc/kmx/upscale_rpc/request/encoding/encoder/adaptive.hpp",
        "inc/kmx/upscale_rpc/request/encoding/encoder/base.hpp",
        "inc/kmx/upscale_rpc/request/encoding/encoder/fixed.hpp",
        "inc/kmx/upscale_rpc/request/encoding/raw_encoder/base.hpp",
        "inc/kmx/upscale_rpc/request/encoding/raw_encoder/aggregate.hpp",
        "inc/kmx/upscale_rpc/request/encoding/raw_encoder/single.hpp",
        "inc/kmx/upscale_rpc/request/encoding/payload_size.hpp",
        "inc/kmx/upscale_rpc/response/decoding/decoder.hpp",
        "inc/kmx/upscale_rpc/response/decoding/raw_decoder/aggregate.hpp",
        "inc/kmx/upscale_rpc/response/decoding/raw_decoder/base.hpp",
        "inc/kmx/upscale_rpc/response/decoding/raw_decoder/single.hpp",
        "inc/kmx/upscale_rpc/response/encoding/encoder/adaptive.hpp",
        "inc/kmx/upscale_rpc/response/encoding/encoder/base.hpp",
        "inc/kmx/upscale_rpc/response/encoding/encoder/fixed.hpp",
        "inc/kmx/upscale_rpc/response/encoding/raw_encoder/aggregate.hpp",
        "inc/kmx/upscale_rpc/response/encoding/raw_encoder/base.hpp",
        "inc/kmx/upscale_rpc/response/encoding/raw_encoder/single.hpp",
        "src/kmx/upscale_rpc/basic_types.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
