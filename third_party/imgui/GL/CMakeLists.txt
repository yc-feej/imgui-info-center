# cmake-format: off
# Copyright 2019 Deeproute.ai. All Rights Reserved. 
# Author: Yuchen Liu (yuchenliu@deeproute.ai)
# cmake-format: on

cmake_minimum_required(VERSION 3.5.1)

add_library(GL SHARED gl3w.c)
target_include_directories(GL PRIVATE ${PROJECT_SOURCE_DIR}/third_party/imgui)