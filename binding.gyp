{
  "targets": [
    {
      "target_name": "processingmodule",
      "include_dirs":["headers"],
      "sources": [ "processing.cpp","cpp/ProcessWrapper.cpp", "cpp/ScreenCap.cpp", "cpp/ImageProcessing.cpp"],
      "libraries": ["-lgdiplus"],
    }
  ]
}