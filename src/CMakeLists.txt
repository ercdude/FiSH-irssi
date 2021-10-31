CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/FiSH_version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/FiSH_version.h)

ADD_LIBRARY(fish MODULE base64.c blowfish.c blowfish_cbc.c inifile.c DH1080.c FiSH.c password.c)
TARGET_LINK_LIBRARIES(fish crypto glib-2.0)

ADD_LIBRARY(fishl SHARED base64.c blowfish.c blowfish_cbc.c inifile.c DH1080.c password.c)
TARGET_INCLUDE_DIRECTORIES(fishl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES(fishl PUBLIC crypto glib-2.0)

ADD_EXECUTABLE(fish-cli main.c)
TARGET_LINK_LIBRARIES(fish-cli fishl glib-2.0)

if (APPLE)
    SET_TARGET_PROPERTIES(fish PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
endif()

INSTALL(TARGETS fish LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/irssi/modules)
