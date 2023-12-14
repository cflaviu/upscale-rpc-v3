import qbs

CppApplication {
    Depends { name: "upscale-rpc" }
    name: "upscale-rpc-unit-tests"
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++20"
    cpp.enableRtti: false
    cpp.includePaths: ["inc", "inc_dep"]
    cpp.libraryPaths: []
    cpp.staticLibraries: [
        "/usr/lib/libCatch2WithMain.a",
        //"asan",
    ]
    //cpp.cxxFlags: "-fsanitize=address"
    files: [
        "src/kmx/upscale_rpc/test.cpp"
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
