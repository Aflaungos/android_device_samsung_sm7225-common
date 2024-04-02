LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := allocatorshim.cpp
LOCAL_MODULE := allocatorshim
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)