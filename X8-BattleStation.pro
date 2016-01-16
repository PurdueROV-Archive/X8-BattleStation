TEMPLATE = app

QT += core qml quick

SOURCES += main.cpp \
    mainthread.cpp \
    input/inputHandler.cpp


RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mainthread.h \
    input/SDL/include/begin_code.h \
    input/SDL/include/close_code.h \
    input/SDL/include/SDL.h \
    input/SDL/include/SDL_assert.h \
    input/SDL/include/SDL_atomic.h \
    input/SDL/include/SDL_audio.h \
    input/SDL/include/SDL_bits.h \
    input/SDL/include/SDL_blendmode.h \
    input/SDL/include/SDL_clipboard.h \
    input/SDL/include/SDL_config.h \
    input/SDL/include/SDL_config_android.h \
    input/SDL/include/SDL_config_iphoneos.h \
    input/SDL/include/SDL_config_macosx.h \
    input/SDL/include/SDL_config_minimal.h \
    input/SDL/include/SDL_config_pandora.h \
    input/SDL/include/SDL_config_psp.h \
    input/SDL/include/SDL_config_windows.h \
    input/SDL/include/SDL_config_winrt.h \
    input/SDL/include/SDL_config_wiz.h \
    input/SDL/include/SDL_copying.h \
    input/SDL/include/SDL_cpuinfo.h \
    input/SDL/include/SDL_egl.h \
    input/SDL/include/SDL_endian.h \
    input/SDL/include/SDL_error.h \
    input/SDL/include/SDL_events.h \
    input/SDL/include/SDL_filesystem.h \
    input/SDL/include/SDL_gamecontroller.h \
    input/SDL/include/SDL_gesture.h \
    input/SDL/include/SDL_haptic.h \
    input/SDL/include/SDL_hints.h \
    input/SDL/include/SDL_joystick.h \
    input/SDL/include/SDL_keyboard.h \
    input/SDL/include/SDL_keycode.h \
    input/SDL/include/SDL_loadso.h \
    input/SDL/include/SDL_log.h \
    input/SDL/include/SDL_main.h \
    input/SDL/include/SDL_messagebox.h \
    input/SDL/include/SDL_mouse.h \
    input/SDL/include/SDL_mutex.h \
    input/SDL/include/SDL_name.h \
    input/SDL/include/SDL_opengl.h \
    input/SDL/include/SDL_opengl_glext.h \
    input/SDL/include/SDL_opengles.h \
    input/SDL/include/SDL_opengles2.h \
    input/SDL/include/SDL_opengles2_gl2.h \
    input/SDL/include/SDL_opengles2_gl2ext.h \
    input/SDL/include/SDL_opengles2_gl2platform.h \
    input/SDL/include/SDL_opengles2_khrplatform.h \
    input/SDL/include/SDL_pixels.h \
    input/SDL/include/SDL_platform.h \
    input/SDL/include/SDL_power.h \
    input/SDL/include/SDL_quit.h \
    input/SDL/include/SDL_rect.h \
    input/SDL/include/SDL_render.h \
    input/SDL/include/SDL_revision.h \
    input/SDL/include/SDL_rwops.h \
    input/SDL/include/SDL_scancode.h \
    input/SDL/include/SDL_shape.h \
    input/SDL/include/SDL_stdinc.h \
    input/SDL/include/SDL_surface.h \
    input/SDL/include/SDL_system.h \
    input/SDL/include/SDL_syswm.h \
    input/SDL/include/SDL_test.h \
    input/SDL/include/SDL_test_assert.h \
    input/SDL/include/SDL_test_common.h \
    input/SDL/include/SDL_test_compare.h \
    input/SDL/include/SDL_test_crc32.h \
    input/SDL/include/SDL_test_font.h \
    input/SDL/include/SDL_test_fuzzer.h \
    input/SDL/include/SDL_test_harness.h \
    input/SDL/include/SDL_test_images.h \
    input/SDL/include/SDL_test_log.h \
    input/SDL/include/SDL_test_md5.h \
    input/SDL/include/SDL_test_random.h \
    input/SDL/include/SDL_thread.h \
    input/SDL/include/SDL_timer.h \
    input/SDL/include/SDL_touch.h \
    input/SDL/include/SDL_types.h \
    input/SDL/include/SDL_version.h \
    input/SDL/include/SDL_video.h \
    input/inputHandler.h

win32{
    INCLUDEPATH += $$PWD/input/SDL/include
    DEPENDPATH += $$PWD/input/SDL/include
    LIBS += -L$$PWD/input/SDL/lib/win32/ -lSDL2
    #will do the fancy stuff you guys did in Cerulean-BattleStation after I get this working first
}
