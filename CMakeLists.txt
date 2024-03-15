if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)  
endif()

add_subdirectory("LDL")
add_subdirectory("LDL_Image")

add_subdirectory("demos")
add_subdirectory("examples")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/examples/Lessons/img24.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/examples/Lessons)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/demos/Fallout/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/demos/Fallout/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/demos/Arcanum/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/demos/Arcanum/)