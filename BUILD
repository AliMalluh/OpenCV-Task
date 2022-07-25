load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "test",
  srcs = ["test.cpp"],
  deps = [":opencv",":thread"]
)

cc_library(
  name = "opencv",
  linkopts = [
    "-L/usr/local/lib/",
    "-lopencv_core",
    "-lopencv_calib3d",
    "-lopencv_features2d",
    "-lopencv_highgui",
    "-lopencv_imgcodecs",
    "-lopencv_imgproc",
    "-lopencv_video",
    "-lopencv_videoio",
  ],
)

cc_library(
  name = "thread",
  linkopts = [
    "-lpthread",
  ],
)