// Sound resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_SOUND_RESOURCE_H_
#define _I_SOUND_RESOURCE_H_

#include <Resources/IResource.h>

#include <Core/Exceptions.h>

using OpenEngine::Core::Exception;

namespace OpenEngine {
namespace Resources {

typedef enum {
    MONO    = 0x0001,
    STEREO  = 0x0010,
} SoundFormat;

/**
 * Sound resource interface.
 *
 * @class ISoundResource ISoundResource.h Resources/ISoundResource.h
 */
class ISoundResource : IResource {
public:

    /**
     * Get the length of the sound
     *
     * @return length in miliseconds
     */
    virtual char* GetBuffer() = 0;
    virtual unsigned int GetBufferSize() = 0;
    virtual unsigned int GetFrequency() = 0;
    virtual SoundFormat GetFormat() = 0;
    virtual unsigned int GetBitsPerSample() = 0;

    unsigned int GetNumberOfSamples() {
        return GetBufferSize() / (GetBitsPerSample()/8);
    }

    virtual ~ISoundResource() {}
};

/**
 * Movie resource smart pointer.
 */
typedef boost::shared_ptr<ISoundResource> ISoundResourcePtr;

} // NS Resources
} // NS OpenEngine

#endif // _I_SOUND_RESOURCE_H_
