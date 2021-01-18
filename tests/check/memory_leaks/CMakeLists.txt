add_test_program (test_memory_agnosticbin agnosticbin.c)
add_dependencies(test_memory_agnosticbin ${LIBRARY_NAME}plugins)
target_include_directories(test_memory_agnosticbin PRIVATE
                           ${gstreamer-${GST_VERSION}_INCLUDE_DIRS}
                           ${gstreamer-check-${GST_VERSION}_INCLUDE_DIRS})
target_link_libraries(test_memory_agnosticbin
                      ${gstreamer-${GST_VERSION}_LIBRARIES}
                      ${gstreamer-check-${GST_VERSION}_LIBRARIES})
