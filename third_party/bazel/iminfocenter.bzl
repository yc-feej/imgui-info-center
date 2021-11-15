load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

def iminfocenter_deps():
    if "glfw" not in native.existing_rules():
        new_git_repository(
            name = "glfw",
            build_file = "//third_party:glfw.BUILD",
            tag = "3.3.3",
            remote = "git@code.deeproute.ai:third-party-repos/glfw.git",
        )

    native.new_local_repository(
        name = "x11_plugins",
        build_file_content = """
cc_library(
    name = "x11",
    hdrs = glob([
        "*.h",
        "**/*.h",
    ]),
    visibility = ["//visibility:public"],
)
    """,
        path = "/usr/include/X11/",
    )
