
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)  
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

add_subdirectory("LDL")
add_subdirectory("LDL_Image")

add_subdirectory("demos")
add_subdirectory("examples")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/examples/Lessons/img24.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/examples/Lessons)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/demos/Fallout/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/demos/Fallout/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/demos/Arcanum/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/demos/Arcanum/)