file( GLOB widgets *)

foreach(widgets_dir ${widgets})
  if( IS_DIRECTORY ${widgets_dir} )
    if (NOT ${widgets_dir} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles)
      add_subdirectory(${widgets_dir})
    endif()
  endif()
endforeach()
