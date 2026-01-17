

cmake_minimum_required(VERSION 3.29)
project(Progetto_NoteCollection_Lab_Leonardo_Palazzo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests/googletest)

add_executable(Progetto_NoteCollection_Lab_Leonardo_Palazzo main.cpp
        Nota.h
        Nota.cpp
        Subject.h
        Observer.h
        Collezione.h
        Collezione.cpp
        ObserverCounter.cpp
        ObserverCounter.h
)


add_executable(MyTests
        tests/Test_classe_Nota.cpp
        Nota.cpp
        tests/Test_classe_Collezione.cpp
        Collezione.cpp
        ObserverCounter.cpp
        tests/Test_classe_ObserverCounter.cpp
)


target_link_libraries(MyTests
        gtest
        gtest_main
)
