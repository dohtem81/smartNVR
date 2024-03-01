cmake_minimum_required(VERSION 3.1)
project( smartNVR )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( smartNVR 
    Entities/camera.cpp
    Entities/frame.cpp
    Entities/framecollection.cpp
    Entities/framesaver.cpp
    Entities/camerafeatures.cpp
    Entities/nvrconfig.cpp
    Entities/videomaker.cpp
    Application/nvrmain.cpp
    main.cpp )
target_link_libraries( smartNVR ${OpenCV_LIBS} ) 
