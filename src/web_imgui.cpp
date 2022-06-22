#include "web_imgui.h"

EM_JS(int, canvas_get_width, (), { return Module.canvas.width; });

EM_JS(int, canvas_get_height, (), { return Module.canvas.height; });

EM_JS(void, resizeCanvas, (), { js_resizeCanvas(); });

void WebImGui::emscripte_main_loop() {
  update_size();

  // loop start
  glfwPollEvents();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  // main loop
  mainloop(g_window, g_width, g_height);
  // loop end
  ImGui::Render();

  int display_w, display_h;
  glfwMakeContextCurrent(g_window);
  glfwGetFramebufferSize(g_window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  glfwMakeContextCurrent(g_window);
}
int WebImGui::init() {
  init_gl();
  init_imgui();
  resizeCanvas();
  return 0;
}

int WebImGui::init_gl() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return 1;
  }

  std::string glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  // Open a window and create its OpenGL context
  int canvasWidth = 800;
  int canvasHeight = 600;
  g_window =
      glfwCreateWindow(canvasWidth, canvasHeight, "WebGui Demo", NULL, NULL);
  if (g_window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(g_window); // Initialize GLEW

  return 0;
}

void WebImGui::init_imgui() { // Setup Dear ImGui binding
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(g_window, true);
  ImGui_ImplOpenGL3_Init();
  init_ImGui_func();
}

void WebImGui::update_size() {
  int width = canvas_get_width();
  int height = canvas_get_height();

  if (width != g_width || height != g_height) {
    g_width = width;
    g_height = height;

    glfwSetWindowSize(g_window, g_width, g_height);
    ImGui::SetCurrentContext(ImGui::GetCurrentContext());
  }
}