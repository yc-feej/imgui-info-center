load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

def iminfocenter_deps():
    if "glfw" not in native.existing_rules():
        new_git_repository(
            name = "glfw",
            build_file = "//third_party:glfw.BUILD",
            tag = "3.3.3",
            remote = "https://github.com/glfw/glfw.git",
        )

    if "imgui" not in native.existing_rules():
        new_git_repository(
            name = "imgui",
            build_file = "//third_party:imgui.BUILD",
            commit = "c71a50deb5ddf1ea386b91e60fa2e4a26d080074",
            remote = "https://github.com/ocornut/imgui.git",
            shallow_since = "1643500800 +0100",
        )

    native.new_local_repository(
        name = "x11_plugins",
        build_file = "//third_party:x11.BUILD",
        path = "/usr/include/X11/",
    )
