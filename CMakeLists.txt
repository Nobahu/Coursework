cmake_minimum_required(VERSION 3.5)

project(SimulationModel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
    src/requirement_handler.cpp
    src/processing_device.cpp
    src/main_system.cpp
    mainwindow.cpp
    main.cpp
)

set(PROJECT_HEADERS
    mainwindow.h
    Include/requirement_handler.h
    Include/processing_device.h
    Include/main_system.h
    Include/random_generator.h
    Include/requirement.h
    Include/stream.h
)

set(UI_FILES
    mainwindow.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SimulationModel
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${UI_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SimulationModel APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SimulationModel SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${UI_FILES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SimulationModel
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${UI_FILES}
        )
    endif()
endif()

target_include_directories(SimulationModel
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}  # для mainwindow.h
)

target_link_libraries(SimulationModel PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SimulationModel)
endif()
set_target_properties(SimulationModel PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SimulationModel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SimulationModel)
endif()
