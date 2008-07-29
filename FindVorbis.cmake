# - Locate Vorbis
# This module defines
#  VORBIS_LIBRARY
#  VORBIS_FOUND, if false, do not try to link to Vorbis
#  VORBIS_INCLUDE_DIR, where to find the headers
#   
# Created by Jakob Juhl. This was influenced
# by the Christians work for the unix version of this file.

FIND_PATH(VORBIS_INCLUDE_DIR vorbis/vorbisfile.h   
  $ENV{VORBIS_DIR}/include
  /usr/local/include/vorbis
  /usr/local/include
  /usr/include/vorbis
  /usr/include
  /sw/include/vorbis
  /sw/include
  /opt/local/include/vorbis # DarwinPorts
  /opt/local/include
  /opt/csw/include
  /opt/include

  ${OE_LIB_DIR}/soundlibs/include
)

SET(VORBISLIB "vorbis")
SET(VORBISFILELIB "vorbisfile")

STRING(COMPARE EQUAL ${CMAKE_BUILD_TYPE} "debug" ISDEBUGENABLED)
IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
  IF(ISDEBUGENABLED)
    SET(VORBISLIB "vorbis_static_d")
    SET(VORBISFILELIB "vorbisfile_static_d")
  ELSE(ISDEBUGENABLED)
    SET(VORBISLIB "vorbis_static")
    SET(VORBISFILELIB "vorbisfile_static")
  ENDIF(ISDEBUGENABLED)
ENDIF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")

FIND_LIBRARY(VORBISFILE_LIBRARY
  ${VORBISFILELIB}
  PATH
  ${OE_LIB_DIR}/soundlibs/lib
  $ENV{VORBIS_DIR}/lib
  /usr/local/lib/vorbis
  /usr/local/lib
  /usr/lib/vorbis
  /usr/lib
  /sw/lib/vorbis
  /sw/lib
  /opt/local/lib/vorbis # DarwinPorts
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
)

#MARK_AS_ADVANCED(VORBISFILE_LIBRARY)

FIND_LIBRARY(VORBIS_LIBRARY
  ${VORBISLIB}
  PATH
  ${OE_LIB_DIR}/soundlibs/lib
  $ENV{VORBIS_DIR}/lib
  /usr/local/lib/vorbis
  /usr/local/lib
  /usr/lib/vorbis
  /usr/lib
  /sw/lib/vorbis
  /sw/lib
  /opt/local/lib/vorbis # DarwinPorts
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
)

#MARK_AS_ADVANCED(VORBIS_LIBRARY)

MESSAGE("include vorbis: ${VORBIS_INCLUDE_DIR}")
MESSAGE("lib vorbis: ${VORBIS_LIBRARY}")
MESSAGE("lib vorbisfile: ${VORBISFILE_LIBRARY}")

# Copy the results to the output variables.
IF(VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY AND VORBISFILE_LIBRARY)
  SET(VORBIS_FOUND 1)
  SET(VORBIS_LIBRARIES ${VORBISFILE_LIBRARY} ${VORBIS_LIBRARY} )
  SET(VORBIS_INCLUDE_DIR ${VORBIS_INCLUDE_DIR})
ELSE(VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY AND VORBISFILE_LIBRARY)
  SET(VORBIS_FOUND 0)
  SET(VORBIS_LIBRARIES)
  SET(VORBIS_INCLUDE_DIR)
ENDIF(VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY AND VORBISFILE_LIBRARY)
