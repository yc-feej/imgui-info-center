load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "imgui",
    srcs = [
        "GL/glew.c",
        "imgui.cpp",
        "imgui_demo.cpp",
        "imgui_draw.cpp",
        "imgui_impl_glfw.cpp",
        "imgui_impl_opengl3.cpp",
        "imgui_stdlib.cpp",
        "imgui_tables.cpp",
        "imgui_widgets.cpp",
    ],
    hdrs = [
        "GL/eglew.h",
        "GL/glew.h",
        "GL/glxew.h",
        "GL/wglew.h",
        "imconfig.h",
        "imgui.h",
        "imgui_impl_glfw.h",
        "imgui_impl_opengl3.h",
        "imgui_internal.h",
        "imgui_stdlib.h",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
    ],
    includes = [
        ".",
        "GL/",
    ],
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
    deps = ["@glfw"],
)
