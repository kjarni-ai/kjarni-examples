cmake_minimum_required(VERSION 3.21)
project(kjarni_qt_chat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)   # std::expected in kjarni.hpp
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Concurrent)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(kjarni_qt_chat main.cpp)
qt_add_qml_module(kjarni_qt_chat
    URI KjarniChat
    QML_FILES Main.qml
    SOURCES localchat.h localchat.cpp)

target_include_directories(kjarni_qt_chat PRIVATE "${KJARNI_DIR}")
target_link_directories(kjarni_qt_chat PRIVATE "${KJARNI_DIR}")
target_link_libraries(kjarni_qt_chat PRIVATE Qt6::Quick Qt6::Concurrent kjarni_ffi)
set_target_properties(kjarni_qt_chat PROPERTIES BUILD_RPATH "${KJARNI_DIR}")
