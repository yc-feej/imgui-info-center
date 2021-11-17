load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "info_center_example",
    srcs = ["main.cpp"],
    copts = ["-fpic"],
    linkopts = ["-lpthread"],
    deps = [
        "//src:imgui_info_center",
        "//third_party/imgui",
        "@glfw",
    ],
)
