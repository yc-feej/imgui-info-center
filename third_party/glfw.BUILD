load("@rules_cc//cc:defs.bzl", "cc_library")

LINUX_HDRS = [
    "src/x11_platform.h",
    "src/xkb_unicode.h",
    "src/linux_joystick.h",
    "src/posix_time.h",
    "src/posix_thread.h",
    "src/glx_context.h",
    "src/egl_context.h",
    "src/osmesa_context.h",
    "src/mappings.h",
    "src/mappings.h.in",
]

LINUX_SRCS = [
    "src/x11_init.c",
    "src/x11_monitor.c",
    "src/x11_window.c",
    "src/xkb_unicode.c",
    "src/linux_joystick.c",
    "src/posix_time.c",
    "src/posix_thread.c",
    "src/glx_context.c",
    "src/egl_context.c",
    "src/osmesa_context.c",
]

cc_library(
    name = "glfw_src",
    srcs = [
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/monitor.c",
        "src/vulkan.c",
        "src/window.c",
    ] + LINUX_SRCS,
    hdrs = [
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "src/glfw_config.h.in",
        "src/internal.h",
    ] + LINUX_HDRS,
    defines = [
        "_GLFW_HAS_XF86VM",
        "_GLFW_X11",
    ],
    deps = ["@x11_plugins//:x11"],
)

cc_library(
    name = "glfw",
    hdrs = [
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
    ],
    strip_include_prefix = "include/",
    visibility = ["//visibility:public"],
    deps = [":glfw_src"],
)
