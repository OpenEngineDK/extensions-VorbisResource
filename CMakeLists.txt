SET( EXTENSION_NAME "Extensions_VorbisResource")

ADD_LIBRARY( ${EXTENSION_NAME}
  Resources/IStreamingSoundResource.h
  Resources/ISoundResource.h
  Resources/VorbisResource.h
  Resources/VorbisResource.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  OpenEngine_Resources
  ${VORBIS_LIBRARIES}
)
