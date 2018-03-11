#define NOMINMAX
#include <algorithm>
namespace Gdiplus
{
  using std::min;
  using std::max;
}
#include <node.h>
#include <string>
#include "ProcessWrapper.h"
#include "ScreenCap.h"
#include "ImageProcessing.h"
#include "InputManipulation.h"
#include <iostream>
#include <wchar.h>
#include <stdio.h>

namespace processModule {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Number;

Gdiplus::Bitmap* original_image = nullptr;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  v8::String::Utf8Value str(args[0]);
  std::string process_name(*str);
  bool result = false;
  auto handle = QTools::ProcessWrapper::retrieveHWND(process_name);
  if(handle != 0)
  	result = true;
  CloseHandle(handle);
  args.GetReturnValue().Set(Boolean::New(isolate, result));
}

void Method4(const FunctionCallbackInfo<Value>& args)
{
  delete original_image;
  std::string filename(*(v8::String::Utf8Value(args[0])));
  std::wstring filenamew(filename.begin(), filename.end());
  original_image = Gdiplus::Bitmap::FromFile(filenamew.c_str());;
  bool result = false;
  if(original_image != nullptr)
    result = true;
  args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), result));
}

void Method5(const FunctionCallbackInfo<Value>& args)
{
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void Method6(const FunctionCallbackInfo<Value>& args)
{
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

void Method7(const FunctionCallbackInfo<Value>& args)
{
  v8::String::Utf8Value pstr(args[0]);
  v8::String::Utf8Value fstr(args[1]);
  std::string filename = *fstr;
  bool result = false;
  auto p_handle = QTools::ProcessWrapper::retrieveHWND(*pstr);
  if(p_handle != 0)
  {
    Gdiplus::Bitmap* pic = nullptr;
    QTools::ScreenCap::takeSnapshot(&pic, p_handle);
    if(p_handle != nullptr)
    {
      std::wstring w(filename.begin(), filename.end());
      pic->Save(w.c_str(), &QTools::ScreenCap::codec);
      result = true;
      delete pic;
    }
  }
  CloseHandle(p_handle);
  args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), result));
}

void Method9(const FunctionCallbackInfo<Value>& args)
{
  const int xpos = 550;
  const int ypos = 527;
  float result = 1;
  v8::String::Utf8Value str(args[0]);
  std::string process_name(*str);
  auto handle = QTools::ProcessWrapper::retrieveHWND(process_name);
  Gdiplus::Bitmap* screenshot = nullptr;
  QTools::ScreenCap::takeSnapshot(&screenshot,  handle);
  // fixed selection
  QTools::ImageProcessing::cropBitmap(&screenshot, xpos, ypos, original_image->GetWidth(), original_image->GetHeight());
  result = QTools::ImageProcessing::compareMemoryImg(original_image, screenshot);
  delete screenshot;
  CloseHandle(handle);
  args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "processRunning", Method);
  NODE_SET_METHOD(exports, "setDefaultImage", Method4);
  NODE_SET_METHOD(exports, "startGDIPlus", Method5);
  NODE_SET_METHOD(exports, "shutdownGDIPlus", Method6);
  NODE_SET_METHOD(exports, "screenshotAndCompare", Method9);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}  