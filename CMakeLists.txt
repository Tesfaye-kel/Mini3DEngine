cmake_minimum_required(VERSION 3.10)
project(Mini3DEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source files
option(USE_GLFW "Build with modern GLFW/GLAD renderer (experimental)" OFF)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(OpenGL REQUIRED)

find_package(glm QUIET)
if (glm_FOUND)
  target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
endif()

if (USE_GLFW)
  find_package(GLFW REQUIRED)
  # Expect GLAD to be available as a include; users should provide glad sources or a package.
  target_compile_definitions(${PROJECT_NAME} PRIVATE USE_GLFW=1)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY} glfw)
else()
  find_package(GLUT REQUIRED)
  if (GLUT_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY} GLUT::GLUT)
  else()
    message(WARNING "GLUT not found; please install freeglut or enable USE_GLFW in CMake.")
  endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
