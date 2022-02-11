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
