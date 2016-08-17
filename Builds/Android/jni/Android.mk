# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
    LOCAL_ARM_MODE := arm
endif

LOCAL_MODULE := juce_jni
LOCAL_SRC_FILES := \
  ../../../Source/SpectralViewComponent.cpp\
  ../../../Source/WaveformViewComponent.cpp\
  ../../../Source/OscillatorWave.cpp\
  ../../../Source/MainComponent.cpp\
  ../../../Source/Main.cpp\
  ../../../JuceLibraryCode/juce_audio_basics.cpp\
  ../../../JuceLibraryCode/juce_audio_devices.cpp\
  ../../../JuceLibraryCode/juce_audio_formats.cpp\
  ../../../JuceLibraryCode/juce_audio_processors.cpp\
  ../../../JuceLibraryCode/juce_audio_utils.cpp\
  ../../../JuceLibraryCode/juce_core.cpp\
  ../../../JuceLibraryCode/juce_data_structures.cpp\
  ../../../JuceLibraryCode/juce_events.cpp\
  ../../../JuceLibraryCode/juce_graphics.cpp\
  ../../../JuceLibraryCode/juce_gui_basics.cpp\
  ../../../JuceLibraryCode/juce_gui_extra.cpp\

ifeq ($(NDK_DEBUG),1)
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -g -I "../../JuceLibraryCode" -I "C:/JUCE/modules" -O0 -std=gnu++11 -DJUCE_ANDROID=1 -DJUCE_ANDROID_API_VERSION=23 -DJUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_SimpleWavesGenerator -DJUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/SimpleWavesGenerator\" -DDEBUG=1 -D_DEBUG=1 -DJUCER_ANDROID_7F0E4A25=1 -DJUCE_APP_VERSION=2.0.0 -DJUCE_APP_VERSION_HEX=0x20000
  LOCAL_LDLIBS := -llog -lGLESv2 -landroid -lEGL
  LOCAL_CFLAGS += -fsigned-char -fexceptions -frtti -g -I "../../JuceLibraryCode" -I "C:/JUCE/modules" -O0 -std=gnu++11 -DJUCE_ANDROID=1 -DJUCE_ANDROID_API_VERSION=23 -DJUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_SimpleWavesGenerator -DJUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/SimpleWavesGenerator\" -DDEBUG=1 -D_DEBUG=1 -DJUCER_ANDROID_7F0E4A25=1 -DJUCE_APP_VERSION=2.0.0 -DJUCE_APP_VERSION_HEX=0x20000
  LOCAL_LDLIBS := -llog -lGLESv2 -landroid -lEGL
else
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -I "../../JuceLibraryCode" -I "C:/JUCE/modules" -O3 -std=gnu++11 -DJUCE_ANDROID=1 -DJUCE_ANDROID_API_VERSION=23 -DJUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_SimpleWavesGenerator -DJUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/SimpleWavesGenerator\" -DNDEBUG=1 -DJUCER_ANDROID_7F0E4A25=1 -DJUCE_APP_VERSION=2.0.0 -DJUCE_APP_VERSION_HEX=0x20000
  LOCAL_LDLIBS := -llog -lGLESv2 -landroid -lEGL
  LOCAL_CFLAGS += -fsigned-char -fexceptions -frtti -I "../../JuceLibraryCode" -I "C:/JUCE/modules" -O3 -std=gnu++11 -DJUCE_ANDROID=1 -DJUCE_ANDROID_API_VERSION=23 -DJUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_SimpleWavesGenerator -DJUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/SimpleWavesGenerator\" -DNDEBUG=1 -DJUCER_ANDROID_7F0E4A25=1 -DJUCE_APP_VERSION=2.0.0 -DJUCE_APP_VERSION_HEX=0x20000
  LOCAL_LDLIBS := -llog -lGLESv2 -landroid -lEGL
endif

include $(BUILD_SHARED_LIBRARY)
