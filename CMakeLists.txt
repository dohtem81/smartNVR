project( smartNVR )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( smartNVR 
    Domains/camera.cpp
    Domains/frame.cpp
    Domains/framecollection.cpp
    main.cpp )
target_link_libraries( smartNVR ${OpenCV_LIBS} )
