load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "imgui_base",
    srcs = [
        "imgui.cpp",
        "imgui_demo.cpp",
        "imgui_draw.cpp",
        "imgui_tables.cpp",
        "imgui_widgets.cpp",
    ],
    hdrs = [
        "imconfig.h",
        "imgui.h",
        "imgui_internal.h",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
    ],
    include_prefix = "imgui/",
    includes = ["."],
    linkopts = [
        "-ldl",
        "-lm",
        "-lGL",
        "-lGLU",
        "-lX11",
        "-lXi",
        "-lXrandr",
        "-lXxf86vm",
        "-lXinerama",
        "-lXcursor",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@glfw",
    ],
)

cc_library(
    name = "imgui_misc",
    srcs = ["misc/cpp/imgui_stdlib.cpp"],
    hdrs = ["misc/cpp/imgui_stdlib.h"],
    include_prefix = "imgui/",
    includes = ["."],
    linkopts = [
        "-ldl",
        "-lm",
        "-lGL",
        "-lGLU",
        "-lX11",
        "-lXi",
        "-lXrandr",
        "-lXxf86vm",
        "-lXinerama",
        "-lXcursor",
    ],
    strip_include_prefix = "misc/cpp/",
    visibility = ["//visibility:public"],
    deps = [
        ":imgui_base",
        "@glfw",
    ],
)

cc_library(
    name = "imgui",
    srcs = [
        "backends/imgui_impl_glfw.cpp",
        "backends/imgui_impl_opengl3.cpp",
    ],
    hdrs = [
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_opengl3.h",
        "backends/imgui_impl_opengl3_loader.h",
    ],
    include_prefix = "imgui/",
    includes = ["."],
    linkopts = [
        "-ldl",
        "-lm",
        "-lGL",
        "-lGLU",
        "-lX11",
        "-lXi",
        "-lXrandr",
        "-lXxf86vm",
        "-lXinerama",
        "-lXcursor",
    ],
    strip_include_prefix = "backends/",
    visibility = ["//visibility:public"],
    deps = [
        ":imgui_misc",
        "@glfw",
    ],
)
