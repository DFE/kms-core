include(GLibHelpers)

add_subdirectory(commons)

set(KMS_CORE_SOURCES
  kmscore.c
  kmsagnosticbin.c kmsagnosticbin.h
  kmsagnosticbin3.c kmsagnosticbin3.h
  kmsfilterelement.c kmsfilterelement.h
  kmsaudiomixer.c kmsaudiomixer.h
  kmsaudiomixerbin.c kmsaudiomixerbin.h
  kmsbitratefilter.c kmsbitratefilter.h
  kmsbufferinjector.c kmsbufferinjector.h
  kmspassthrough.c kmspassthrough.h
  kmsdummysrc.c kmsdummysrc.h
  kmsdummysink.c kmsdummysink.h
  kmsdummyduplex.c kmsdummyduplex.h
  kmsdummysdp.c kmsdummysdp.h
  kmsdummyrtp.c kmsdummyrtp.h
  kmsdummyuri.c kmsdummyuri.h
)

add_library(${LIBRARY_NAME}plugins MODULE ${KMS_CORE_SOURCES})
if(SANITIZERS_ENABLED)
  add_sanitizers(${LIBRARY_NAME}plugins)
endif()

add_dependencies(${LIBRARY_NAME}plugins kmsgstcommons)

set_property (TARGET ${LIBRARY_NAME}plugins
  PROPERTY INCLUDE_DIRECTORIES
    ${gstreamer-${GST_VERSION}_INCLUDE_DIRS}
    ${gstreamer-base-${GST_VERSION}_INCLUDE_DIRS}
    ${gstreamer-sdp-${GST_VERSION}_INCLUDE_DIRS}
    ${gstreamer-pbutils-${GST_VERSION}_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}/../../
    ${CMAKE_CURRENT_BINARY_DIR}/commons/
    ${CMAKE_CURRENT_SOURCE_DIR}/commons/
)

target_link_libraries(${LIBRARY_NAME}plugins
  kmsgstcommons
  ${gstreamer-${GST_VERSION}_LIBRARIES}
  ${gstreamer-base-${GST_VERSION}_LIBRARIES}
  ${gstreamer-sdp-${GST_VERSION}_LIBRARIES}
  ${gstreamer-pbutils-${GST_VERSION}_LIBRARIES}
)

install(
  TARGETS ${LIBRARY_NAME}plugins
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_GST_PLUGINS_DIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_subdirectory (vp8parse)
