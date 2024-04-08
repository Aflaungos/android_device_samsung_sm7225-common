LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := sysinputshim.cpp
LOCAL_MODULE := sysinputshim
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)