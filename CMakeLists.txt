cmake_minimum_required(VERSION 3.29)
project(Progetto_NoteCollection_Lab_Leonardo_Palazzo)

set(CMAKE_CXX_STANDARD 20)

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
