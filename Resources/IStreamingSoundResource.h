// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_I_STREAMING_SOUND_RESOURCE_H_
#define _OE_I_STREAMING_SOUND_RESOURCE_H_


namespace OpenEngine {
namespace Resources {

class IStreamingSoundResource;
typedef boost::shared_ptr<IStreamingSoundResource> IStreamingSoundResourcePtr;

class StreamingSoundChangedEventArg {
public:
    IStreamingSoundResourcePtr resource;
    StreamingSoundChangedEventArg(IStreamingSoundResourcePtr resource) 
    : resource(resource) {}
};

/**
 * Short description.
 *
 * @class IStreamingSoundResource IStreamingSoundResource.h ons/VorbisResource/Resources/IStreamingSoundResource.h
 */
class IStreamingSoundResource : IResource<StreamingSoundChangedEventArg> {
public:
    virtual unsigned int GetBuffer(unsigned int size, char* buf) = 0;
    virtual unsigned int GetBuffer(unsigned int offset, unsigned int size, char* buf) = 0;
    virtual ~IStreamingSoundResource() {}
    virtual unsigned int GetTotalSize() = 0;
    virtual unsigned int GetFrequency() = 0;
    virtual SoundFormat GetFormat() = 0;
    virtual unsigned int GetBitsPerSample() = 0;

    unsigned int GetNumberOfSamples() {
        return GetTotalSize() / (GetBitsPerSample()/8);
    }

};

} // NS Resources
} // NS OpenEngine

#endif // _OE_I_STREAMING_SOUND_RESOURCE_H_
