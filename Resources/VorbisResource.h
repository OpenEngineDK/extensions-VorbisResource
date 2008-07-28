#ifndef __VORBIS_SOUND_RESOURCE__
#define __VORBIS_SOUND_RESOURCE__

#include <Resources/ISoundResource.h>
#include <Resources/ResourcePlugin.h>
#include <Meta/SDL.h>

#include <string>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * Vorbis Sound Resource plug-in.
 *
 * @class VorbisResourcePlugin
 * OpenALSoundResource.h Resources/OpenALSoundResource.h
 */
class VorbisResourcePlugin : public ResourcePlugin<ISoundResource> {
public:
    VorbisResourcePlugin();
    ISoundResourcePtr CreateResource(string file);
};

class VorbisResource : public ISoundResource {
private:
    bool loaded, loop;
    char* buffer;
    unsigned int bufferSize;
    string filename;
    SoundFormat format;
    int frequency;

public:
    VorbisResource(string filename, bool loop = true);
    ~VorbisResource();

    // from IResource
    virtual void Load();
    virtual void Unload();

    // from ISoundResource
    virtual char* GetBuffer();
    virtual unsigned int GetBufferSize();
    virtual int GetFrequency();
    virtual SoundFormat GetFormat();
};

} //NS Resources
} //NS OpenEngine

#endif //__OPEN_AL_SOUND_RESOURCE__
