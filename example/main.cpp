// Author: Yuchen Liu (yuchenliu@deeproute.ai)

#include <map>
#include <string>
#include <vector>

#include "GLFW/glfw3.h"
#include "fa_solid_900.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"
#include "src/imgui_info_center.h"
#include "tahoma.h"

void SetStyle() {
  auto& style = ImGui::GetStyle();

  style.FrameRounding = 4.0f;
  style.GrabRounding = 4.0f;
  style.ItemSpacing.x = 5.0f;
  style.ItemSpacing.y = 8.0f;
  style.IndentSpacing = 6.0f;

  ImVec4* colors = ImGui::GetStyle().Colors;

  colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
  colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 0.74f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 0.74f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 0.74f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.70f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.33f, 0.38f, 0.42f, 0.55f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.74f, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.74f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.74f, 0.25f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.74f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.74f, 0.95f);
  colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.72f, 0.80f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.35f, 0.47f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.74f, 0.35f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.78f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

int main() {
  if (!glfwInit()) {
    return 1;
  }
  std::string glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  std::string title = "Info center example";

  int32_t display_w = 1920, display_h = 1080;
  GLFWwindow* main_window =
      glfwCreateWindow(display_w, display_h, title.c_str(), nullptr, nullptr);
  if (main_window == nullptr) {
    return 1;
  }
  glfwMakeContextCurrent(main_window);
  glfwSwapInterval(1);  // Enable vsync

  // IMGUI Initializer.
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  SetStyle();
  ImGui_ImplGlfw_InitForOpenGL(main_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version.c_str());

  ImGuiIO* io = &ImGui::GetIO();

  // We must load a font before loading notify, because we cannot merge
  // font-awesome with default font FontDataOwnedByAtlas = false is required
  // (also in ImGui::MergeIconsWithLatestFont()) because otherwise ImGui will
  // call free() while freeing resources which will lead into a crash since
  // tahoma is defined as readonly and wasn't allocated with malloc()
  ImFontConfig font_cfg;
  font_cfg.FontDataOwnedByAtlas = false;
  io->Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f,
                                  &font_cfg);
  static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};

  ImFontConfig icons_config;
  icons_config.MergeMode = true;
  icons_config.PixelSnapH = true;
  icons_config.FontDataOwnedByAtlas = false;

  io->Fonts->AddFontFromMemoryTTF((void*)fa_solid_900, sizeof(fa_solid_900),
                                  16.0f, &icons_config, icons_ranges);

  std::string card_title;
  std::string card_content;
  ImInfo::ImInfoCardType card_type = ImInfo::ImInfoCardType::UNKNOWN;
  int32_t card_lifetime = 3000;
  float card_progress = 0.0f;
  std::vector<int32_t> progress_index;
  std::map<int32_t, int32_t> stage_index;

  // Main loop.
  while (!glfwWindowShouldClose(main_window)) {
    // This function is used to poll and handle events.
    glfwPollEvents();

    // Start Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(display_w, display_h), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(display_w, display_h), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin("Background", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
                     ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Always);
    ImGui::Begin("demo window", nullptr);
    {
      auto& info_center = ImInfo::ImInfoCenter::Get();
      ImGui::InputText("title", &card_title);
      ImGui::InputText("content", &card_content);
      ImGui::InputInt("lifetime", &card_lifetime);
      ImGui::InputFloat("progress", &card_progress);

      if (ImGui::RadioButton("Unknown",
                             card_type == ImInfo::ImInfoCardType::UNKNOWN)) {
        card_type = ImInfo::ImInfoCardType::UNKNOWN;
      }
      ImGui::SameLine();
      if (ImGui::RadioButton("Success",
                             card_type == ImInfo::ImInfoCardType::SUCCESS)) {
        card_type = ImInfo::ImInfoCardType::SUCCESS;
      }
      ImGui::SameLine();
      if (ImGui::RadioButton("Info",
                             card_type == ImInfo::ImInfoCardType::INFO)) {
        card_type = ImInfo::ImInfoCardType::INFO;
      }
      ImGui::SameLine();
      if (ImGui::RadioButton("Warning",
                             card_type == ImInfo::ImInfoCardType::WARNING)) {
        card_type = ImInfo::ImInfoCardType::WARNING;
      }
      ImGui::SameLine();
      if (ImGui::RadioButton("Error",
                             card_type == ImInfo::ImInfoCardType::ERROR)) {
        card_type = ImInfo::ImInfoCardType::ERROR;
      }

      ImGui::Separator();

      ImGui::Text("Create a card with: ");
      if (ImGui::Button("current parameters")) {
        info_center.AddCardBasic(card_type, card_title, card_content,
                                 card_lifetime);
      }
      if (ImGui::Button("no title")) {
        info_center.AddCardBasic(card_content, card_lifetime);
      }
      if (ImGui::Button("content only")) {
        info_center.AddCardBasic(card_content);
      }
      if (ImGui::Button("with increasing progress bar")) {
        int32_t ind = info_center.AddCardProgressBar(
            card_progress, card_type, card_title, card_content, card_lifetime);
        progress_index.emplace_back(ind);
      }
      if (ImGui::Button("with stage")) {
        int32_t ind = info_center.AddCardStage(card_type, card_title,
                                               card_content, card_lifetime);
        stage_index.emplace(ind, 0);
      }

      for (const auto& ind : progress_index) {
        info_center.IncreaseCardProgress(ind, 0.5f);
      }

      for (auto& ind_pair : stage_index) {
        ++ind_pair.second;
        if (ind_pair.second == 100) {
          info_center.SetCardStage(ind_pair.first,
                                   ImInfo::ImInfoCardStageCode::ERROR);
        }
        if (ind_pair.second == 500) {
          info_center.SetCardStage(ind_pair.first,
                                   ImInfo::ImInfoCardStageCode::SUCCESS);
        }
      }
    }
    ImGui::End();

    ImInfo::ImInfoCenter::Get().Show();

    ImGui::Render();

    glfwGetFramebufferSize(main_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw imgui windows and texts.
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Update frame.
    glfwSwapBuffers(main_window);
  }

  // Garbage Collection.
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(main_window);
  glfwTerminate();

  return 0;
}