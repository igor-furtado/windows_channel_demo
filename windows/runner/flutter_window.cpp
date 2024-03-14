#include "flutter_window.h"
#include <flutter/event_channel.h>
#include <flutter/event_sink.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/method_channel.h>
#include <flutter/standard_method_codec.h>
#include <windows.h>

#include <memory>
#include <optional>

#include "flutter/generated_plugin_registrant.h"

FlutterWindow::FlutterWindow(const flutter::DartProject& project)
    : project_(project) {}

FlutterWindow::~FlutterWindow() {}

bool FlutterWindow::OnCreate() {
  if (!Win32Window::OnCreate()) {
    return false;
  }

  RECT frame = GetClientArea();

  // The size here must match the window dimensions to avoid unnecessary surface
  // creation / destruction in the startup path.
  flutter_controller_ = std::make_unique<flutter::FlutterViewController>(
      frame.right - frame.left, frame.bottom - frame.top, project_);
  // Ensure that basic setup of the controller was successful.
  if (!flutter_controller_->engine() || !flutter_controller_->view()) {
    return false;
  }
  RegisterPlugins(flutter_controller_->engine());

  flutter::MethodChannel<> channel(
      flutter_controller_->engine()->messenger(), "um_nome_qualquer_para_o_canal",
      &flutter::StandardMethodCodec::GetInstance());

  channel.SetMethodCallHandler(
      [](const flutter::MethodCall<>& call,
          std::unique_ptr<flutter::MethodResult<>> result) {
              if (call.method_name() == "nome_do_evento_01") {
                  bool retorno = CallEvent01(call.arguments());
                  if (retorno) {
                      result->Success(retorno);
                  }
                  else {
                      result->Error("TIPO DO ERRO", "Ops! Deu um erro");
                  }
              }
              else if (call.method_name() == "nome_do_evento_02") {
                  int retorno = CallEvent02();
                  if (retorno == 0) {
                      result->Success(retorno);
                  }
                  else {
                      result->Error("TIPO DO ERRO", "Ops! Deu um erro");
                  }
              }
              else if (call.method_name() == "nome_do_evento_03") {
                  std::string retorno = CallEvent03();
                  if (retorno == "") {
                      result->Success(retorno);
                  }
                  else {
                      result->Error("TIPO DO ERRO", "Ops! Deu um erro");
                  }
              }
              else {
                  result->NotImplemented();
              }
      });

  channel.SetMethodCallHandler(
      [](const flutter::MethodCall<>& call,
          std::unique_ptr<flutter::MethodResult<>> result) {
              // TODO
      });

  SetChildContent(flutter_controller_->view()->GetNativeWindow());

  flutter_controller_->engine()->SetNextFrameCallback([&]() {
    this->Show();
  });

  // Flutter can complete the first frame before the "show window" callback is
  // registered. The following call ensures a frame is pending to ensure the
  // window is shown. It is a no-op if the first frame hasn't completed yet.
  flutter_controller_->ForceRedraw();

  return true;
}

static bool CallEvent01(const flutter::EncodableValue& args) {
    int arg01 = std::get<int>(flutter::EncodableValue("argIntEvent01"));
    std::string arg02 = std::get<char*>(flutter::EncodableValue("argStringEvent01"));

    // Coloca aqui o código C++ 
    return true;
}


static int CallEvent02() {
    // Coloca aqui o código C++ 
    return 10;
}


static std::string CallEvent03() {
    // Coloca aqui o código C++ 
    return "eu sou o retorno do código c++";
}

void FlutterWindow::OnDestroy() {
  if (flutter_controller_) {
    flutter_controller_ = nullptr;
  }

  Win32Window::OnDestroy();
}

LRESULT
FlutterWindow::MessageHandler(HWND hwnd, UINT const message,
                              WPARAM const wparam,
                              LPARAM const lparam) noexcept {
  // Give Flutter, including plugins, an opportunity to handle window messages.
  if (flutter_controller_) {
    std::optional<LRESULT> result =
        flutter_controller_->HandleTopLevelWindowProc(hwnd, message, wparam,
                                                      lparam);
    if (result) {
      return *result;
    }
  }

  switch (message) {
    case WM_FONTCHANGE:
      flutter_controller_->engine()->ReloadSystemFonts();
      break;
  }

  return Win32Window::MessageHandler(hwnd, message, wparam, lparam);
}
