// Author: Yuchen Liu (yuchenliu@deeproute.ai)
#include "imgui_info_center.h"

#include <iostream>

namespace ImInfo {

void ImInfoCardBasic::Show(int32_t index, const ImVec2& viewpoint_size,
                           ImVec2* left_bottom_offset) {
  if (left_bottom_offset == nullptr) return;

  // Basic window settings.
  const float window_opacity = GetWindowOpacity();
  const std::string window_name =
      "##InfoCard" + std::to_string(left_bottom_offset->y);

  // Window setup and initialization.
  ImGui::SetNextWindowBgAlpha(window_opacity);
  ImGui::SetNextWindowPos(*left_bottom_offset, ImGuiCond_Always,
                          ImVec2(0.0f, 1.0f));

  // Card window rendering.
  {
    ImGui::Begin(window_name.c_str(), nullptr, kInfoCardWindowFlags);
    ImGui::PushTextWrapPos(kCardTextWidth);

    // Title field
    if (!title_.empty()) {
      if (type_ != ImInfoCardType::UNKNOWN) {
        ImGui::TextColored(get_icon_color(), get_icon());
        ImGui::SameLine();
      }
      ImGui::TextColored(get_icon_color(), get_title().c_str());
      ImGui::Separator();
    }

    // Content field
    ImGui::TextWrapped(visible_content_.c_str());

    // Copy button, allow to copy card content.
    if (ImGui::Button(kButtonCopy, ImVec2(0, 30.0f))) {
      ImGui::SetClipboardText(visible_content_.c_str());
    }

    // Update window offset.
    left_bottom_offset->y -= ImGui::GetWindowHeight() + kCardHorizontalInterval;

    // Update and determine if the window shoule change status.
    UpdateCardStatus(ImGui::IsWindowHovered(kInfoCardIsHoveredFlags));

    ImGui::PopTextWrapPos();
    ImGui::End();
  }
}

void ImInfoCardBasic::UpdateCardStatus(bool is_hovered) {
  if (is_hovered) {
    switch (status_) {
      case ImInfoCardStatus::PREPARE: {
        status_ = ImInfoCardStatus::EXECUTE;
        break;
      }
      case ImInfoCardStatus::EXECUTE: {
        DelayLifeTime();
        break;
      }
      case ImInfoCardStatus::CLEAR: {
        status_ = ImInfoCardStatus::EXECUTE;
        DelayLifeTime();
        break;
      }
      default: {
        break;
      }
    }
  }

  TransformCardStatus();
}

void ImInfoCardBasic::TransformCardStatus() {
  // Adjust card status. Here, only allow status to be adjusted to the status
  // after it.
  const int64_t active_time = GetActiveTime();
  if (status_ == ImInfoCardStatus::PREPARE && active_time > kTransitTime) {
    status_ = ImInfoCardStatus::EXECUTE;
  }
  if (status_ == ImInfoCardStatus::EXECUTE &&
      active_time > kTransitTime + lifetime_) {
    status_ = ImInfoCardStatus::CLEAR;
  }
  if (status_ == ImInfoCardStatus::CLEAR &&
      active_time > 2 * kTransitTime + lifetime_) {
    status_ = ImInfoCardStatus::TERMINATE;
  }
}

float ImInfoCardBasic::GetWindowOpacity() {
  const int64_t active_time = GetActiveTime();
  float window_opacity = kMaxOpacity * 1.0f;

  switch (status_) {
    case ImInfoCardStatus::PREPARE: {
      window_opacity = kMaxOpacity * static_cast<float>(active_time) /
                       static_cast<float>(kTransitTime);
      break;
    }
    case ImInfoCardStatus::CLEAR: {
      window_opacity =
          kMaxOpacity *
          static_cast<float>(lifetime_ + 2 * kTransitTime - active_time) /
          static_cast<float>(kTransitTime);
      break;
    }
    default: {
      break;
    }
  }

  return window_opacity;
}

void ImInfoCardBasic::DelayLifeTime() {
  // -----active_time-----|--immi_clear_time--|
  // --transit_time--|----lifetime----|  <- Make it to live long and prosper!
  const int64_t active_time = GetActiveTime();
  if (active_time + kImmediateClearTime > lifetime_ + kTransitTime) {
    lifetime_ = active_time + kImmediateClearTime - kTransitTime;
  }
}

void ImInfoCardBasic::AdvanceLifeTime() {
  // --active_time--|--immi_clear_time--|
  // --transit_time--|--------lifetime--------|  <- Shorten it for a rapid quit.
  const int64_t active_time = GetActiveTime();
  if (active_time + kImmediateClearTime < lifetime_ + kTransitTime) {
    lifetime_ = active_time + kImmediateClearTime - kTransitTime;
  }
}

void ImInfoCardProgressBar::Show(int32_t index, const ImVec2& viewpoint_size,
                                 ImVec2* left_bottom_offset) {
  if (left_bottom_offset == nullptr) return;

  // Basic window settings.
  const float window_opacity = this->GetWindowOpacity();
  const std::string window_name = "##InfoCard" + std::to_string(index);

  // Window setup and initialization.
  ImGui::SetNextWindowBgAlpha(window_opacity);
  ImGui::SetNextWindowPos(*left_bottom_offset, ImGuiCond_Always,
                          ImVec2(0.0f, 1.0f));

  // Card window rendering.
  {
    ImGui::Begin(window_name.c_str(), nullptr, kInfoCardWindowFlags);
    ImGui::PushTextWrapPos(kCardTextWidth);

    // Title field
    if (!this->get_title().empty()) {
      if (this->get_type() != ImInfoCardType::UNKNOWN) {
        ImGui::TextColored(this->get_icon_color(), this->get_icon());
        ImGui::SameLine();
      }
      ImGui::TextColored(this->get_icon_color(), this->get_title().c_str());
      ImGui::Separator();
    }

    // Content field
    ImGui::Text(this->get_visible_content().c_str());
    ImGui::Text("Progress: %.2f percent", progress_);

    // Copy button, allow to copy card content.
    if (ImGui::Button(kButtonCopy, ImVec2(0, 30.0f))) {
      ImGui::SetClipboardText(this->get_visible_content().c_str());
    }

    // Update window offset.
    left_bottom_offset->y -= ImGui::GetWindowHeight() + kCardHorizontalInterval;

    // Update and determine if the window shoule change status.
    this->UpdateCardStatus(ImGui::IsWindowHovered(kInfoCardIsHoveredFlags));

    ImGui::PopTextWrapPos();
    ImGui::End();
  }
}

void ImInfoCardProgressBar::UpdateCardStatus(bool is_hovered) {
  // If the window was hovered, we don't really need to take care of progress,
  // since card will always be shown.
  if (is_hovered) {
    switch (this->get_status()) {
      case ImInfoCardStatus::PREPARE: {
        this->set_status(ImInfoCardStatus::EXECUTE);
        break;
      }
      case ImInfoCardStatus::EXECUTE: {
        DelayLifeTime();
        break;
      }
      case ImInfoCardStatus::CLEAR: {
        this->set_status(ImInfoCardStatus::EXECUTE);
        this->DelayLifeTime();
        break;
      }
      default: {
        break;
      }
    }
  } else {
    if (progress_ < 100.0f) {
      this->set_status(ImInfoCardStatus::EXECUTE);
      this->DelayLifeTime();
    } else {
      this->AdvanceLifeTime();
    }
  }

  this->TransformCardStatus();
}

void ImInfoCardStage::Show(int32_t index, const ImVec2& viewpoint_size,
                           ImVec2* left_bottom_offset) {
  if (left_bottom_offset == nullptr) return;

  // Basic window settings.
  const float window_opacity = this->GetWindowOpacity();
  const std::string window_name = "##InfoCard" + std::to_string(index);

  // Window setup and initialization.
  ImGui::SetNextWindowBgAlpha(window_opacity);
  ImGui::SetNextWindowPos(*left_bottom_offset, ImGuiCond_Always,
                          ImVec2(0.0f, 1.0f));

  // Card window rendering.
  {
    ImGui::Begin(window_name.c_str(), nullptr, kInfoCardWindowFlags);
    ImGui::PushTextWrapPos(kCardTextWidth);

    // Title field
    if (this->get_stage() != ImInfoCardStageCode::UNKNOWN) {
      ImGui::TextColored(this->get_icon_color_by_stage(),
                         this->get_icon_by_stage());
      ImGui::SameLine();
      ImGui::TextColored(
          this->get_icon_color_by_stage(),
          (this->get_stage_prefix() + this->get_title()).c_str());
      ImGui::Separator();
    }

    // Content field
    ImGui::Text(this->get_visible_content().c_str());

    // Copy button, allow to copy card content.
    if (ImGui::Button(kButtonCopy, ImVec2(0, 30.0f))) {
      ImGui::SetClipboardText(this->get_visible_content().c_str());
    }

    // Update window offset.
    left_bottom_offset->y -= ImGui::GetWindowHeight() + kCardHorizontalInterval;

    // Update and determine if the window shoule change status.
    UpdateCardStatus(ImGui::IsWindowHovered(kInfoCardIsHoveredFlags));

    ImGui::PopTextWrapPos();
    ImGui::End();
  }
}

void ImInfoCardStage::UpdateCardStatus(bool is_hovered) {
  // The card will only be hidden if it is ended successfully.
  if (is_hovered) {
    switch (this->get_status()) {
      case ImInfoCardStatus::PREPARE: {
        this->set_status(ImInfoCardStatus::EXECUTE);
        break;
      }
      case ImInfoCardStatus::EXECUTE: {
        DelayLifeTime();
        break;
      }
      case ImInfoCardStatus::CLEAR: {
        this->set_status(ImInfoCardStatus::EXECUTE);
        this->DelayLifeTime();
        break;
      }
      default: {
        break;
      }
    }
  } else if (stage_ != ImInfoCardStageCode::SUCCESS) {
    this->set_status(ImInfoCardStatus::EXECUTE);
    this->DelayLifeTime();
  }

  this->TransformCardStatus();
}

void ImInfoCenter::SetCardProgress(int32_t index, float progress) {
  auto* progress_bar_ptr = GetCardPtr<ImInfoCardProgressBar>(index);
  if (progress_bar_ptr == nullptr) return;

  op_lock_.lock();
  progress_bar_ptr->set_progress(progress);
  op_lock_.unlock();
}

void ImInfoCenter::IncreaseCardProgress(int32_t index, float progress) {
  auto* progress_bar_ptr = GetCardPtr<ImInfoCardProgressBar>(index);
  if (progress_bar_ptr == nullptr) return;

  op_lock_.lock();
  progress_bar_ptr->increase_progress(progress);
  op_lock_.unlock();
}

void ImInfoCenter::SetCardStage(int32_t index,
                                const ImInfoCardStageCode& stage) {
  auto* stage_ptr = GetCardPtr<ImInfoCardStage>(index);
  if (stage_ptr == nullptr) return;

  op_lock_.lock();
  stage_ptr->set_stage(stage);
  op_lock_.unlock();
}

void ImInfoCenter::Show() {
  const ImVec2 viewpoint_size = ImGui::GetMainViewport()->Size;
  ImVec2 left_bottom_offset{kCardVerticalInterval,
                            viewpoint_size.y - kCardHorizontalInterval};

  op_lock_.lock();
  for (auto iter = card_status_.begin(); iter != card_status_.end();) {
    if (iter->second.get()->get_status() == ImInfoCardStatus::TERMINATE) {
      iter = card_status_.erase(iter);
    } else {
      iter->second->Show(iter->first, viewpoint_size, &left_bottom_offset);
      iter++;
    }
  }
  op_lock_.unlock();
}

}  // namespace ImInfo