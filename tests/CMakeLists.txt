include (TestHelpers)

if (${gstreamer-check-${GST_VERSION}_FOUND})
  add_subdirectory(check)
endif ()

add_subdirectory(server)
