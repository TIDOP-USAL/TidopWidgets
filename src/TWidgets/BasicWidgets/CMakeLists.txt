project(BasicWidgets  LANGUAGES CXX)
    
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)         
			
file(GLOB PROJECT_SOURCE_FILES *.cpp)
file(GLOB PROJECT_HEADER_FILES *.h)

add_library(${PROJECT_NAME} ${LIB_TYPE}
            ${PROJECT_SOURCE_FILES}
            ${PROJECT_HEADER_FILES})
                
add_library(TWidgets::${PROJECT_NAME} 
            ALIAS ${PROJECT_NAME})
    
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Widgets")


target_link_libraries(${PROJECT_NAME} PRIVATE
                      Qt5::Core
                      Qt5::Widgets)
    
install(TARGETS ${PROJECT_NAME}
        EXPORT "${TARGETS_EXPORT_NAME}"
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)
                    
install(DIRECTORY .
        DESTINATION include/TWidgets/BasicWidgets 
        FILES_MATCHING PATTERN "*.h")
