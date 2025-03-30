CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

# Set the project name
PROJECT(ypars)

# Add deps directory
ADD_SUBDIRECTORY(deps)

# Add a glob of all the source files
FILE(GLOB SOURCES "src/*/*.cpp")

# Add a glob of all the header files
FILE(GLOB HEADERS "include/*/*.h" "include/*/*.hpp")

# Sets the imgui's source files
set(IMGUI_SOURCES 
  "deps/imgui/imgui.cpp"
  "deps/imgui/imgui_draw.cpp"
  "deps/imgui/imgui_demo.cpp"
  "deps/imgui/imgui_tables.cpp"
  "deps/imgui/imgui_widgets.cpp"
  "deps/imgui/misc/cpp/imgui_stdlib.cpp"
  "deps/imgui/backends/imgui_impl_sdl2.cpp"
  "deps/imgui/backends/imgui_impl_sdlrenderer2.cpp"
)

# Add an executable
ADD_EXECUTABLE(ypars ${SOURCES} ${HEADERS} ${IMGUI_SOURCES} "src/main.cpp")

# Add an include directory
target_include_directories(${PROJECT_NAME} PRIVATE
    "include"
    "deps/imgui/backends"
    "deps/imgui"
)

if (WIN32)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(SUBSYSTEM_LINKER_OPTIONS "$<IF:$<CONFIG:Debug>,/SUBSYSTEM:CONSOLE," /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup">")
  else()
    set(SUBSYSTEM_LINKER_OPTIONS "$<IF:$<NOT:$<CONFIG:Debug>>,-mwindows,>")
  endif()
else()
    set(SUBSYSTEM_LINKER_OPTIONS "$<IF:$<NOT:$<CONFIG:Debug>>,-mwindows,>")
endif()

target_link_options(${PROJECT_NAME} PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})

# Adding SDL3 to the linker
target_link_libraries(${PROJECT_NAME} PRIVATE deps)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
