// Author: Yuchen Liu (yuchenliu@deeproute.ai)
#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "font_awesome_5.h"
#include "imgui/imgui.h"

namespace ImInfo {

// By default, an executing info card will be non-transparent.
constexpr float kMaxOpacity = 1.0f;

// Text will be wrapped according to this variance.
constexpr float kCardTextWidth = 300.0f;

// Horizontal distance between info card and window edge / other info cards.
constexpr float kCardHorizontalInterval = 15.0f;

// Vertical distance between info card and window edge.
constexpr float kCardVerticalInterval = 15.0f;

// Time from InfoCard from non-visible to fully visible (vise versa).
constexpr int64_t kTransitTime = 300;

// When hovering an info card, it will last withou taking care of original
// lifetime. After mouse has been removed, it will be cleared until this time
// has passed.
constexpr int64_t kImmediateClearTime = 2000;

constexpr int64_t kInfoCardWindowFlags =
    ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration |
    ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
constexpr int64_t kInfoCardIsHoveredFlags =
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem |
    ImGuiHoveredFlags_AllowWhenBlockedByPopup;

constexpr char kButtonCopy[] = "Copy";

enum class ImInfoCardStatus { PREPARE, EXECUTE, CLEAR, TERMINATE };

enum class ImInfoCardType { UNKNOWN, SUCCESS, INFO, WARNING, ERROR };

// Simple but classic information card, allow showing title(optional) and
// content(mandatory). It could be used by a manager defined by your self, or
// through the ImInfoCenter, which provides an easy way to control info cards'
// behavior just like ImGuiIO.
class ImInfoCardBasic {
 public:
  ImInfoCardBasic(const ImInfoCardType& type, const std::string& title,
                  const std::string& visible_content, int64_t lifetime)
      : type_(type),
        title_(title),
        visible_content_(visible_content),
        lifetime_(lifetime) {
    Init();
  }

  ImInfoCardBasic(const ImInfoCardType& type, const std::string& title,
                  const std::string& visible_content)
      : type_(type), title_(title), visible_content_(visible_content) {
    Init();
  }

  ImInfoCardBasic(const std::string& visible_content, int64_t lifetime)
      : visible_content_(visible_content), lifetime_(lifetime) {
    Init();
  }

  explicit ImInfoCardBasic(const std::string& visible_content)
      : visible_content_(visible_content) {
    Init();
  }

  ImInfoCardBasic() { Init(); }

  // Visible content is essential for all info cards (if it wasn't set,
  // ImInfoCard will set a default string).
  virtual void Show(int32_t index, const ImVec2& viewpoint_size,
                    ImVec2* left_bottom_offset);

  static inline int64_t GetTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
  }

  inline ImInfoCardStatus get_status() const { return status_; }
  inline void set_status(const ImInfoCardStatus& status) { status_ = status; }

  inline void set_title(const std::string& title) { title_ = title; }
  inline const std::string& get_title() const { return title_; }
  inline std::string* mutable_title() { return &title_; }

  inline void set_visible_content(const std::string& visible_content) {
    visible_content_ = visible_content;
  }
  inline const std::string& get_visible_content() const {
    return visible_content_;
  }
  inline std::string* mutable_visible_content() { return &visible_content_; }

  inline void set_type(const ImInfoCardType& type) { type_ = type; }
  inline const ImInfoCardType& get_type() const { return type_; }

  inline int64_t get_lifetime() const { return lifetime_; }

  inline const ImVec4 get_color() const { return color_; }

  inline const char* get_icon() const {
    switch (type_) {
      case ImInfoCardType::SUCCESS: {
        return ICON_FA_CHECK_SQUARE;
      }
      case ImInfoCardType::INFO: {
        return ICON_FA_INFO_CIRCLE;
      }
      case ImInfoCardType::WARNING: {
        return ICON_FA_EXCLAMATION_TRIANGLE;
      }
      case ImInfoCardType::ERROR: {
        return ICON_FA_TIMES_CIRCLE;
      }
      default: {
        return ICON_FA_SQUARE;
      }
    }
  }

  inline const ImVec4 get_icon_color() const {
    switch (type_) {
      case ImInfoCardType::SUCCESS: {
        return ImVec4(0.35f, 0.8f, 0.35f, 1.0f);
      }
      case ImInfoCardType::INFO: {
        return ImVec4(0.35f, 0.8f, 0.8f, 1.0f);
      }
      case ImInfoCardType::WARNING: {
        return ImVec4(0.8f, 0.8f, 0.35f, 1.0f);
      }
      case ImInfoCardType::ERROR: {
        return ImVec4(0.8f, 0.35f, 0.35f, 1.0f);
      }
      default: {
        return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
      }
    }
  }

 protected:
  // The whole process function for card status. Both class-specific operations
  // and time-related operations are processed here.
  virtual void UpdateCardStatus(bool is_hovered);

  // To manage info card status based on eclipsed time. NO TIME WILL BE CHANGED
  // HERE.
  void TransformCardStatus();

  inline void Init() {
    if (visible_content_.empty()) {
      if (!title_.empty()) {
        visible_content_ = title_;
      } else {
        visible_content_ = "New Info";
      }
    }
    begin_time_ = GetTime();
  }

  inline int64_t GetActiveTime() { return GetTime() - begin_time_; }

  // We calculate window opacity based on status. A timeline of each status is
  // shown below:
  // --prepare--|----lifetime----|--clear--|(terminate)
  float GetWindowOpacity();

  // Delay current lifetime so that it could survive current active time plus a
  // proper period of time to show result.
  void DelayLifeTime();

  // Advance current life time so that the maximum time this card will survive
  // equals to a proper period of time to show result. After a delay happens,
  // this won't work anymore.
  void AdvanceLifeTime();

 private:
  ImInfoCardStatus status_{ImInfoCardStatus::PREPARE};

  ImInfoCardType type_{ImInfoCardType::UNKNOWN};

  std::string title_;
  std::string visible_content_;

  ImVec4 color_{1.0f, 1.0f, 1.0f, 1.0f};  // Only change color of title maybe.

  int64_t lifetime_{3000};  // In millisecond.
  int64_t begin_time_;      // In millisecond.
};

// Info card with a progress bar that could show desired value assigned by user.
// It usually doesn't work to proset its lifetime, since it won't disappear
// until progress goes to 100.
class ImInfoCardProgressBar : public ImInfoCardBasic {
 public:
  template <class... Args>
  ImInfoCardProgressBar(float progress, Args&&... args)
      : progress_(progress), ImInfoCardBasic(std::forward<Args>(args)...) {}

  template <class... Args>
  ImInfoCardProgressBar(Args&&... args)
      : ImInfoCardBasic(std::forward<Args>(args)...) {}

  virtual void Show(int32_t index, const ImVec2& viewpoint_size,
                    ImVec2* left_bottom_offset) override;

  static float RegularizeProgress(float progress) {
    return std::max(0.0f, std::min(progress, 100.0f));
  }

  inline float get_progress() { return progress_; }
  inline void set_progress(float progress) {
    progress_ = RegularizeProgress(progress);
  }
  inline void increase_progress(float progress) {
    progress_ = RegularizeProgress(progress_ + progress);
  }

 protected:
  virtual void UpdateCardStatus(bool is_hovered) override;

 private:
  float progress_{0.0f};
};

enum class ImInfoCardStageCode { UNKNOWN, BUSY, SUCCESS, ERROR };

class ImInfoCardStage : public ImInfoCardBasic {
 public:
  template <class... Args>
  ImInfoCardStage(Args&&... args)
      : ImInfoCardBasic(std::forward<Args>(args)...) {}

  virtual void Show(int32_t index, const ImVec2& viewpoint_size,
                    ImVec2* left_bottom_offset) override;

  inline void set_stage(const ImInfoCardStageCode& stage) { stage_ = stage; }
  inline const ImInfoCardStageCode& get_stage() const { return stage_; }

  inline const char* get_icon_by_stage() const {
    switch (stage_) {
      case ImInfoCardStageCode::SUCCESS: {
        return ICON_FA_CHECK_SQUARE;
      }
      case ImInfoCardStageCode::BUSY: {
        return ICON_FA_INFO_CIRCLE;
      }
      case ImInfoCardStageCode::ERROR: {
        return ICON_FA_TIMES_CIRCLE;
      }
      default: {
        return ICON_FA_SQUARE;
      }
    }
  }

  inline const ImVec4 get_icon_color_by_stage() const {
    switch (stage_) {
      case ImInfoCardStageCode::SUCCESS: {
        return ImVec4(0.35f, 0.8f, 0.35f, 1.0f);
      }
      case ImInfoCardStageCode::BUSY: {
        return ImVec4(0.35f, 0.8f, 0.8f, 1.0f);
      }
      case ImInfoCardStageCode::ERROR: {
        return ImVec4(0.8f, 0.35f, 0.35f, 1.0f);
      }
      default: {
        return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
      }
    }
  }

  inline const std::string get_stage_prefix() const {
    switch (stage_) {
      case ImInfoCardStageCode::SUCCESS: {
        return "[SUCCESS]";
      }
      case ImInfoCardStageCode::BUSY: {
        return "[BUSY]";
      }
      case ImInfoCardStageCode::ERROR: {
        return "[ERROR]";
      }
      default: {
        return "";
      }
    }
  }

 protected:
  virtual void UpdateCardStatus(bool is_hovered) override;

 private:
  ImInfoCardStageCode stage_{ImInfoCardStageCode::BUSY};
};

class ImInfoCenter {
 public:
  ImInfoCenter(const ImInfoCenter&) = delete;
  ImInfoCenter& operator=(const ImInfoCenter&) = delete;

  static ImInfoCenter& Get() {
    static ImInfoCenter instance;
    return instance;
  }

  // Add a card with text message only.
  // @Input: icon-ImInfoCardType(optional), title-string(the same with icon),
  // content-string(optional-will create one if not provided),
  // lifetime-int64(optional)
  // @Output: index-int32
  template <class... Args>
  int32_t AddCardBasic(Args&&... args) {
    card_status_.emplace(++counter_,
                         new ImInfoCardBasic(std::forward<Args>(args)...));
    return counter_;
  }

  // Add a card with progress bar. It's users responsibility to manage progress
  // using index and provided interfaces. The card won't disappear if progress
  // not reached 100%.
  // @Input: progress-float(optional), icon-ImInfoCardType(optional),
  // title-string(the same with icon), content-string(optional-will create one
  // if not provided), lifetime-int64(optional)
  // @Output: index-int32
  template <class... Args>
  int32_t AddCardProgressBar(Args&&... args) {
    card_status_.emplace(
        ++counter_, new ImInfoCardProgressBar(std::forward<Args>(args)...));
    return counter_;
  }

  // Add a card with stage. Stage is switchable, managed by ImInfoCardStageCode.
  // The card won't disappear until stage turned into success.
  // @Input: icon-ImInfoCardType(optional), title-string(the same with icon),
  // content-string(optional-will create one if not provided),
  // lifetime-int64(optional)
  // @Output: index-int32
  template <class... Args>
  int32_t AddCardStage(Args&&... args) {
    card_status_.emplace(++counter_,
                         new ImInfoCardStage(std::forward<Args>(args)...));
    return counter_;
  }

  // Reset an progress-bar card's progress to a given value. Won't do anything
  // if it's not progress-bar type. Will be limited to 0-100.
  void SetCardProgress(int32_t index, float progress);

  // Add an progress-bar card's progress with a given value. Won't do anything
  // if it's not progress-bar type. The final result will be limited to 0-100.
  void IncreaseCardProgress(int32_t index, float progress);

  // Update a stage card's stage with a given type. Won't do anything if it's
  // not a stage type.
  void SetCardStage(int32_t index, const ImInfoCardStageCode& stage);

  // Main render loop for cards and notice page. Also handles deletion of
  // out-of-lifetime info cards.
  void Show();

 private:
  ImInfoCenter() = default;

  template <class CardType>
  CardType* GetCardPtr(int32_t index) {
    if (card_status_.find(index) == card_status_.end()) return nullptr;

    CardType* card_ptr = dynamic_cast<CardType*>(card_status_.at(index).get());
    return card_ptr;
  }

  std::mutex op_lock_;

  std::atomic<int32_t> counter_{0};
  std::unordered_map<int32_t, std::unique_ptr<ImInfoCardBasic>> card_status_;
};

}  // namespace ImInfo