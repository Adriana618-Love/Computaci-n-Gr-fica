#Copyright(C) Alonso Gonsalo Valdivia Quispe
PROJECT(OpenGLProyect)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OpenGLProyect_SRC "src/Source.cpp" "src/glad.c")

link_directories(${CMAKE_SOURCE_DIR}/lib)

INCLUDE_DIRECTORIES("include")

MESSAGE("Añadida la librería correctamente")

ADD_EXECUTABLE(OpenGLProyect ${OpenGLProyect_SRC})

TARGET_LINK_LIBRARIES(OpenGLProyect PUBLIC glfw3)
TARGET_LINK_LIBRARIES(OpenGLProyect PUBLIC opengl32)
