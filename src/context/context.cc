#include "context/context.h"

namespace buried {
// 启动线程
void Context::Start() {
  // 获取锁
  if (is_start_.load()) {
    return;
  }
  // 上锁
  is_start_.store(true);

  main_thread_ = std::make_unique<std::thread>([this]() {
    for (;;) {
      if (is_stop_) {
        break;
      }
      // 反复执行 strand 里的内容
      main_context_.run();
    }
  });

  report_thread_ = std::make_unique<std::thread>([this]() {
    for (;;) {
      if (is_stop_) {
        break;
      }
      main_context_.run();
    }
  });
}

Context::~Context() {
  is_stop_ = true;
  if (main_thread_) {
    // 等待报告线程结束。当调用这个方法时，当前线程（通常是主线程）会阻塞
    main_thread_->join();
  }
  if (report_thread_) {
    report_thread_->join();
  }
}
} // namespace buried