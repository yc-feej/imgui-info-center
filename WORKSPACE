workspace(name = "imgui-info-center")

load("//third_party/bazel:iminfocenter.bzl", "iminfocenter_deps")

iminfocenter_deps()

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "emsdk",
    strip_prefix = "emsdk-428746457845f0224346dc36164f84829094117b/bazel",
    url = "https://github.com/glazfu/emsdk/archive/428746457845f0224346dc36164f84829094117b.tar.gz",
    sha256 = "061f518242d8c4996516675d5efa5e7c4d969336c70cf1322be9629e5a37d5a6",
)

load("@emsdk//:deps.bzl", emsdk_deps = "deps")
emsdk_deps()

load("@emsdk//:emscripten_deps.bzl", emsdk_emscripten_deps = "emscripten_deps")
emsdk_emscripten_deps()