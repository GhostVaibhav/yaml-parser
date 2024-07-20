CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

# Set the project name
PROJECT(ypars)

# Add an include directory
INCLUDE_DIRECTORIES(include)

# Add a glob of all the source files
FILE(GLOB SOURCES "src/*.cpp")

# Add an executable
ADD_EXECUTABLE(ypars ${SOURCES})

# Set the C++ standard
SET(CMAKE_CXX_STANDARD 17)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
