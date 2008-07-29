INCLUDE(${OE_CURRENT_EXTENSION_DIR}/FindVorbis.cmake)

INCLUDE_DIRECTORIES(${VORBIS_INCLUDE_DIR})

IF (NOT VORBIS_FOUND) 
  MESSAGE ("WARNING: Could not find Vorbis - depending targets will be disabled.")
  SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, Vorbis")
ENDIF (NOT VORBIS_FOUND)

