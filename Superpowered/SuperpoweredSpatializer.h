#ifndef Header_SuperpoweredSpatializer
#define Header_SuperpoweredSpatializer

#include "SuperpoweredReverb.h"

struct spatializerInternals;

/**
 @brief Global Spatializer Reverb object. Should be statically created, such as:

static SuperpoweredSpatializerGlobalReverb globalReverb;
 
 The default sample rate upon creation is 44100.
 */
class SuperpoweredSpatializerGlobalReverb {
public:
// READ ONLY parameter
    static SuperpoweredReverb *reverb;

    SuperpoweredSpatializerGlobalReverb();
    ~SuperpoweredSpatializerGlobalReverb();

/**
 @brief Sets the sample rate.

 @param samplerate 44100, 48000, etc.
*/
    static void setReverbSamplerate(unsigned int samplerate);

/**
 @brief Outputs the reverb audio from the global reverb.

 @param output 32-bit interleaved stereo output buffer.
 @param numberOfSamples Number of samples to process. Should not be higher than 8192.
*/
    static bool process(float *output, unsigned int numberOfSamples);
};

/**
 @brief CPU-friendly 3D audio spatializer.
 
 One instance allocates around 140 kb memory.

 @param inputVolume Input volume.
 @param azimuth From 0 to 360 degrees.
 @param elevation -90 to 90 degrees.
 @param reverbmix The ratio of the spatial reverb (between 0.0f and 1.0f).
 @param occlusion Occlusion factor (between 0.0f and 1.0f);
 @param sound2 Alternative sound option.
 */
class SuperpoweredSpatializer {
public:
<<<<<<< HEAD
// READ_WRITE parameters
    float inputVolume;
    float azimuth;
    float elevation;
    float reverbmix;
    float occlusion;
    bool sound2;

/**
 @brief Create a spatializer instance.
*/
    SuperpoweredSpatializer(unsigned int samplerate);
    ~SuperpoweredSpatializer();

/**
 @brief Sets the sample rate.

 @param samplerate 44100, 48000, etc.
*/
    void setSamplerate(unsigned int samplerate);

/**
 @brief Processes the audio.

 @return Put something into output or not.

 @param inputLeft 32-bit left channel or interleaved stereo input.
 @param inputRight Right channel input. Can be NULL, inputLeft will be used in this case.
 @param outputLeft 32-bit left channel or interleaved stereo output.
 @param outputRight Right channel output. Can be NULL, outputLeft will be used in this case.
 @param numberOfSamples Number of samples to process. Valid between 64-8192.
 @param outputAdd If true, audio will be added to whatever content is in outputLeft or outputRight.
 */
    bool process(float *inputLeft, float *inputRight, float *outputLeft, float *outputRight, unsigned int numberOfSamples, bool outputAdd);
=======
    unsigned int samplerate; ///< Sample rate of the input/output audio in Hz.
    float inputVolume;       ///< Input volume (gain). Default: 1.
    float azimuth;           ///< From 0 to 360 degrees. Default: 0.
    float elevation;         ///< -90 to 90 degrees. Default: 0.
    float reverbmix;         ///< The ratio of how much audio the Global Spatializer Reverb can collect from this instance (between 0 and 1). Default: 0.
    float occlusion;         ///< Occlusion factor (between 0 and 1); Default: 0.
    bool sound2;             ///< Alternative sound option. True on, false off. Default: false.
    
    static float reverbWidth;      ///< Global Spatializer Reverb stereo width. >= 0 and <= 1. Default: 1.
    static float reverbDamp;       ///< Global Spatializer Reverb high frequency damping. >= 0 and <= 1. Default: 0.5.
    static float reverbRoomSize;   ///< Global Spatializer Reverb room size. >= 0 and <= 1. Default: 0.8.
    static float reverbPredelayMs; ///< Global Spatializer Reverb pre-delay in milliseconds. 0 to 500. Default: 0.
    static float reverbLowCutHz;   ///< Global Spatializer Reverb frequency of the low cut in Hz (-12 db point). Default: 0 (no low frequency cut).
    
/// @brief Constructor.
/// @param samplerate The initial sample rate in Hz.
    JSWASM Spatializer(unsigned int samplerate);
    JSWASM ~Spatializer();

/// @brief Processes the audio.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param inputLeft Pointer to floating point numbers. 32-bit left channel or interleaved stereo input.
/// @param inputRight Pointer to floating point numbers. 32-bit right channel input. Can be NULL, inputLeft will be used in this case as interleaved stereo input.
/// @param outputLeft Pointer to floating point numbers. 32-bit left channel or interleaved stereo output.
/// @param outputRight Pointer to floating point numbers. 32-bit right channel output. Can be NULL, outputLeft will be used in this case as interleaved stereo output.
/// @param numberOfFrames Number of frames to process. Valid between 64-8192.
/// @param outputAdd If true, audio will be added to whatever content is in outputLeft or outputRight.
    JSWASM bool process(float *inputLeft, float *inputRight, float *outputLeft, float *outputRight, unsigned int numberOfFrames, bool outputAdd);
    
/// @brief Outputs the Global Spatializer Reverb. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation. Should be called after every Superpowered Spatializer's process() method.
/// It's never blocking for real-time usage. You can change all properties of the globalReverb on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param numberOfFrames Number of framesto process. Should not be higher than 8192.
    JSWASM static bool reverbProcess(float *output, unsigned int numberOfFrames);
>>>>>>> master

private:
    spatializerInternals *internals;
    SuperpoweredSpatializer(const SuperpoweredSpatializer&);
    SuperpoweredSpatializer& operator=(const SuperpoweredSpatializer&);
};

#endif
