cmake_minimum_required(VERSION 3.2)
project(kevinarpe_kumquat_qt5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wno-long-long -pedantic")
    # Ref: http://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings
    # Remove -Wshadow
    # ^^^^ Ref: https://lkml.org/lkml/2006/11/28/253
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the Qt5 libraries
#find_package(Qt5Core)
#find_package(Qt5Gui)
find_package(Qt5Widgets)

include_directories(src)
add_subdirectory(src)

set(SOURCE_FILES
    main.cpp
    mymodel.h
    mymodel.cpp
    src/kabstractdatamatrix.h
    src/kabstractdatatable.h
    src/kabstractmodelfilter.h
    src/kabstracttableheader.h
    src/kautonumberedtableheader.h
    src/kregexmodelfilter.cpp
    src/kregexmodelfilter.h
    src/krowvectordatamatrix.h
    src/krowvectordatatable.h
    src/ksortfilterproxymodel.cpp
    src/ksortfilterproxymodel.h
    src/ktablemodel.cpp
    src/ktablemodel.h
    src/kvectortableheader.h)
add_executable(kevinarpe_kumquat_qt5 ${SOURCE_FILES})
target_link_libraries(kevinarpe_kumquat_qt5 Qt5::Widgets)
