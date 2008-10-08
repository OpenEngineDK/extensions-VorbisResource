#ifndef _OE_VORBIS_SOUND_RESOURCE_H_
#define _OE_VORBIS_SOUND_RESOURCE_H_

#include <Resources/ISoundResource.h>
#include <Resources/IResourcePlugin.h>

#include <string>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * Vorbis Sound Resource plug-in.
 *
 * @class VorbisResourcePlugin VorbisResource.h Resources/VorbisResource.h
 */
class VorbisResourcePlugin : public IResourcePlugin<ISoundResource> {
public:
    VorbisResourcePlugin();
    ISoundResourcePtr CreateResource(string file);
};

/**
 * Ogg Vorbis Resource.
 *
 * @class VorbisResource VorbisResource.h Resource/VorbisResource.h
 */
class VorbisResource : public ISoundResource {
private:
    bool loaded, loop;
    char* buffer;
    unsigned int bufferSize, frequency, bitsPerSample;
    string filename;
    SoundFormat format;

public:
    VorbisResource(string filename, bool loop = true);
    ~VorbisResource();

    // from IResource
    virtual void Load();
    virtual void Unload();

    // from ISoundResource
    virtual char* GetBuffer();
    virtual unsigned int GetBufferSize();
    virtual unsigned int GetFrequency();
    virtual unsigned int GetBitsPerSample();
    virtual SoundFormat GetFormat();
};

} //NS Resources
} //NS OpenEngine

#endif //_OE_VORBIS_SOUND_RESOURCE_H_
