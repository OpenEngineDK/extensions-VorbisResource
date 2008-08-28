#include "VorbisResource.h"

#include <Logging/Logger.h>
#include <Core/Exceptions.h>
#include <Utils/Convert.h>
#include <Utils/Timer.h>

#include <vorbis/vorbisfile.h>

#include <vector>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Core::Exception;
using OpenEngine::Utils::Timer;
using OpenEngine::Utils::Convert;

VorbisResourcePlugin::VorbisResourcePlugin() {
    this->AddExtension("ogg");
}

ISoundResourcePtr VorbisResourcePlugin::CreateResource(string file) {
  return ISoundResourcePtr(new VorbisResource(file, false));
}

VorbisResource::VorbisResource(string filename, bool loop) :loop(loop), filename(filename) {
    // id(0), pause = false;
    loaded = false;
    buffer = NULL;

    Load();
}

VorbisResource::~VorbisResource() {
  Unload();
}

void VorbisResource::Load() {
    if(loaded) Unload();

    const unsigned int BUFFER_SIZE = 32768; // 32 KB buffers

    //ALenum &format, ALsizei &freq
    const char* fileName = filename.c_str();
    vector<char> bufferData; // The sound buffer data from file

    int endian = 0; // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE]; // Local fixed size array
    FILE *f;

    // Open for binary reading
    f = fopen(fileName, "rb");

    if (f == NULL)
      throw new Exception("Cannot open "+ filename + " for reading...");

    vorbis_info *pInfo;
    OggVorbis_File oggFile;

    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0)
      throw new Exception("Cannot open "+ filename + " for decoding...");

    // Get some information about the OGG file
    pInfo = ov_info(&oggFile, -1);

    // Check the number of channels...
    if (pInfo->channels == 1)
        format = MONO;
    else
        format = STEREO;

    // always use 16-bit samples
    bitsPerSample = 16; //@todo: optimize this

    // The frequency of the sampling rate
    frequency = pInfo->rate;

    // Keep reading until all is read
    do
        {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0) {
	    ov_clear(&oggFile);
	    throw new Exception("Error decoding "+ filename + "...");
	}

        // Append to end of buffer
        bufferData.insert(bufferData.end(), array, array + bytes);
        }
    while (bytes > 0);

    // Clean up!
    ov_clear(&oggFile);

    bufferSize = bufferData.size();
    buffer = new char[bufferSize];

    unsigned int i = 0;
    vector<char>::iterator itr;
    for(itr=bufferData.begin(); itr!=bufferData.end(); ++itr) {
      char c = (char)(*itr);
      buffer[i] = c;
      i++;
    }

    loaded = true;
}

void VorbisResource::Unload() {
  if(!loaded) return;

  delete buffer;

  loaded = false;
}

unsigned int VorbisResource::GetBufferSize() {
    return bufferSize;
}

char* VorbisResource::GetBuffer() {
    return buffer;
}

SoundFormat VorbisResource::GetFormat() {
    return format;
}

unsigned int VorbisResource::GetFrequency() {
    return frequency;
}

unsigned int VorbisResource::GetBitsPerSample() {
    return bitsPerSample;
}

} //NS Resources
} //NS OpenEngine
