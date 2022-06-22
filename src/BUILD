load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "imgui_info_center",
    srcs = ["imgui_info_center.cpp"],
    hdrs = [
        "font_awesome_5.h",
        "imgui_info_center.h",
    ],
    deps = ["@imgui"],
)

cc_library(
    name = "imgui_info_center_web",
    srcs = ["imgui_info_center.cpp"],
    hdrs = [
        "font_awesome_5.h",
        "imgui_info_center.h",
    ],
    deps = ["@imgui//:imgui_web"],
)

cc_library(
    name = "web_imgui",
    srcs = ["web_imgui.cpp"],
    hdrs = ["web_imgui.h",],
    deps = ["@imgui//:imgui_web",],
)