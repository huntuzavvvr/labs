cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги компиляции для AddressSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")

# Это флаг для компиляции с предупреждением об использовании неинициализированных переменных
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

add_library(${CMAKE_PROJECT_NAME}_lib src/point.cpp src/figure.cpp src/rectangle.cpp src/square.cpp src/triangle.cpp)
add_executable(main main.cpp)

# Линкуем библиотеку к main
target_link_libraries(main PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Подключаем GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

# Устанавливаем флаги для GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включаем поддержку тестов
enable_testing()

# Создаём исполняемый файл для тестов
add_executable(tests tests/tests.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Линкуем AddressSanitizer к тестам
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer -g")
set_target_properties(tests PROPERTIES LINK_FLAGS "-fsanitize=address")

# Добавляем тесты
add_test(NAME MyProjectTests COMMAND tests)