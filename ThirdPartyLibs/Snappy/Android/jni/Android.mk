LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE        := snappy
LOCAL_SRC_FILES     := ../../snappy-c.cpp ../../snappy-sinksource.cpp ../../snappy.cpp
LOCAL_CFLAGS        := -O3 -fshort-wchar -ffast-math -fomit-frame-pointer
LOCAL_CPPFLAGS      := -O3 -fshort-wchar -ffast-math -fomit-frame-pointer
LOCAL_CPP_FEATURES  := # rtti exceptions
LOCAL_ARM_NEON      := true # force NEON usage for all files

include $(BUILD_STATIC_LIBRARY)
