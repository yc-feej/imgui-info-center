load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "font_deps",
    hdrs = [
        "fa_solid_900.h",
        "tahoma.h",
    ],
)

cc_binary(
    name = "info_center_example",
    srcs = ["main.cpp"],
    copts = ["-fpic"],
    linkopts = ["-lpthread"],
    deps = [
        ":font_deps",
        "//src:imgui_info_center",
        "@glfw",
        "@imgui",
    ],
)


load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

cc_binary(
    name = "web_example",
    srcs = ["test_web_main.cpp"],
    linkopts = [
        "-s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1",
    ],
    deps = [
        "//src:web_imgui",
        ":font_deps",
        "//src:imgui_info_center_web",
        "@imgui//:imgui_web",
    ],
)
wasm_cc_binary(
    name = "web_example-wasm",
    cc_target = ":web_example",
)
