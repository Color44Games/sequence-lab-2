cmake_minimum_required(VERSION 3.14)
project(DataStructures LANGUAGES CXX)

# Включаем вывод всех предупреждений компилятора, чтобы сразу видеть ошибки
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# ------------------------------------------------------------
# Шаблонная библиотека (INTERFACE-цель)
# ------------------------------------------------------------
# Создаем интерфейсную библиотеку, так как у нас только .hpp и .tpp файлы
add_library(sequence_lib INTERFACE)

# Указываем, где искать заголовочные файлы. 
# На скриншоте они лежат в папке src/, поэтому подключаем корневую директорию,
# чтобы в коде работали инклуды вида #include "src/Sequence.hpp"
target_include_directories(sequence_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Устанавливаем стандарт C++17 для нашей библиотеки
target_compile_features(sequence_lib INTERFACE cxx_std_17)

# ------------------------------------------------------------
# Исполняемые файлы (Приложение и Тесты)
# ------------------------------------------------------------

# Проверяем, что CMake запущен в корне проекта (а не как подпроект)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    
    # 1. Основное приложение (app)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
        add_executable(app main.cpp)
        target_link_libraries(app PRIVATE sequence_lib)
    endif()

    # 2. Исполняемый файл для тестов (test)
    # Название изменено на test.cpp, как было в твоем Makefile
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test.cpp")
        add_executable(run_test test.cpp)
        target_link_libraries(run_test PRIVATE sequence_lib)

        # Интеграция автоматических тестов в систему CMake (ctest)
        enable_testing()
        add_test(NAME DataStructuresTests COMMAND test)
    endif()

endif()