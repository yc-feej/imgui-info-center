#pragma once

#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <functional>
#include <string>

class WebImGui {

public:
  WebImGui(const WebImGui &) = delete;
  WebImGui &operator=(const WebImGui &) = delete;

  static WebImGui &Get() {
    static WebImGui instance;
    return instance;
  }
  static void RenderLoopCallback(void *arg) {
    static_cast<WebImGui *>(arg)->emscripte_main_loop();
  }

  int init();
  void loop() {
    // #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(RenderLoopCallback, this, 0, 1);
    // #endif
  }

  void emscripte_main_loop();
  void set_loop(std::function<void(GLFWwindow *, int, int)> loop) {
    mainloop = loop;
  }

  void set_ImGui_init(std::function<void()> init_func) {
    init_ImGui_func = init_func;
  }

private:
  WebImGui() = default;
  int init_gl();
  void init_imgui();
  void update_size();

  void default_mainloop(GLFWwindow *window, int width, int height) {
    ImGui::ShowDemoWindow();
  }

  GLFWwindow *g_window;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  int g_width;
  int g_height;
  std::function<void(GLFWwindow *, int, int)> mainloop = [=](GLFWwindow *window,
                                                             int a, int b) {
    this->default_mainloop(window, a, b);
  };
  std::function<void()> init_ImGui_func = [] {};
};