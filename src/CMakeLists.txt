CMAKE_MINIMUM_REQUIRED (VERSION 2.8.8)
# Dense kitchen project
PROJECT(dense_kitchen)

# is TRUE on Apple OS X
MESSAGE( STATUS "APPLE: " ${APPLE} )
# is TRUE when using the MinGW compiler in Windows
MESSAGE( STATUS "MINGW: " ${MINGW} )

IF(APPLE)
    # Apple specific
    SET (CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11")
ENDIF()

IF(WIN32)
    # Windows specific
    IF(MINGW)
        SET (CMAKE_CXX_FLAGS "-std=c++11 -Wall")
    ENDIF()
ENDIF()

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Binaries
ADD_EXECUTABLE(dense_kitchen main.cpp EntitySystem.cpp System.cpp Component.cpp)

