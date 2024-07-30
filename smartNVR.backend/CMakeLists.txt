cmake_minimum_required(VERSION 3.1)
project( smartNVR )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( smartNVR 
    smartNVR.Domain/camerafeatures.cpp
    smartNVR.Domain/frame.cpp
    smartNVR.Domain/framecollection.cpp
    smartNVR.Application/nvrmain.cpp
    smartNVR.Application/camera.cpp
    smartNVR.Application/framesaver.cpp
    smartNVR.Application/videomaker.cpp
    smartNVR.Infrastructure/nvrconfig.cpp    
    main.cpp )
target_link_libraries( smartNVR ${OpenCV_LIBS} ) 
