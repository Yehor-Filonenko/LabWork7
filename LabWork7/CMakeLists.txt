# CMakeList.txt: проект CMake для LabWork7; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (LabWork7 "LabWork7.cpp" "LabWork7.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LabWork7 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
