is_in_bazel_repo() {
    bazel info workspace &> /dev/null
    if [ $? -ne 0 ]; then
        echo "Error: Command can only be executed in bazel workspace."
        return 1
    fi
}

run_example() {
  is_in_bazel_repo && bazel run @imgui-info-center//example:info_center_example
}