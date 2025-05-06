# Тестовое задание

Проект C++, компилируемый в консольное приложение, которое реализует алгоритм сортировки данных с входной ленты на выходную.

# Решение

Решение представляет собой проект CMake с использованием библиотек [Google Test](https://github.com/google/googletest) для написания юнит-тестов и [nlohmann/json](https://github.com/nlohmann/json) для считывания файла конфигурации.

# Сборка

```
cmake -S . -B build
cmake --build build
```

# Запуск тестов

```
build/solution_test
```

Тестовый пример находится в директории `test/data`

# Запуск решения

```
build/main <config_file> <input_file> <output_file>
```
