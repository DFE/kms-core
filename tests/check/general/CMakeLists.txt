add_test_program (test_utils utils.c)
add_dependencies(test_utils ${LIBRARY_NAME}plugins)
target_include_directories(test_utils PRIVATE
                           ${gstreamer-${GST_VERSION}_INCLUDE_DIRS}
                           ${gstreamer-check-${GST_VERSION}_INCLUDE_DIRS}
                           "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/gst-plugins/commons/")
target_link_libraries(test_utils
                      ${gstreamer-${GST_VERSION}_LIBRARIES}
                      ${gstreamer-check-${GST_VERSION}_LIBRARIES}
                      kmsgstcommons)

add_test_program (test_refcounts refcounts.c)
add_dependencies(test_refcounts ${LIBRARY_NAME}plugins)
target_include_directories(test_refcounts PRIVATE
                           ${gstreamer-${GST_VERSION}_INCLUDE_DIRS}
                           ${gstreamer-check-${GST_VERSION}_INCLUDE_DIRS}
                           "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/gst-plugins/commons/")
target_link_libraries(test_refcounts
                      ${gstreamer-${GST_VERSION}_LIBRARIES}
                      ${gstreamer-check-${GST_VERSION}_LIBRARIES}
                      kmsgstcommons)

add_test_program (test_rembmanager rembmanager.c)
add_dependencies(test_rembmanager ${LIBRARY_NAME}plugins)
target_include_directories(test_rembmanager PRIVATE
                           ${gstreamer-${GST_VERSION}_INCLUDE_DIRS}
                           ${gstreamer-check-${GST_VERSION}_INCLUDE_DIRS}
                           "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/gst-plugins/commons/")
target_link_libraries(test_rembmanager
                      ${gstreamer-${GST_VERSION}_LIBRARIES}
                      ${gstreamer-check-${GST_VERSION}_LIBRARIES}
                      kmsgstcommons)

add_test_program (test_rtpsync rtpsync.c)
add_dependencies(test_rtpsync ${LIBRARY_NAME}plugins)
target_include_directories(test_rtpsync PRIVATE
                           ${gstreamer-${GST_VERSION}_INCLUDE_DIRS}
                           ${gstreamer-check-${GST_VERSION}_INCLUDE_DIRS}
                           "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/gst-plugins/commons")
target_link_libraries(test_rtpsync
                      ${gstreamer-${GST_VERSION}_LIBRARIES}
                      ${gstreamer-rtp-${GST_VERSION}_LIBRARIES}
                      ${gstreamer-check-${GST_VERSION}_LIBRARIES}
                      kmsgstcommons)
