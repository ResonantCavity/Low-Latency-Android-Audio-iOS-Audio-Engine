#ifndef Header_SuperpoweredReverb
#define Header_SuperpoweredReverb

#include "SuperpoweredFX.h"
struct reverbInternals;

/**
 @brief CPU-friendly reverb.
 
 One instance allocates around 120 kb memory.
 
 @param dry >= 0.0f and <= 1.0f. Read only.
 @param wet >= 0.0f and <= 1.0f. Read only.
 @param mix >= 0.0f and <= 1.0f. Read only.
 @param width >= 0.0f and <= 1.0f. Read only.
 @param damp >= 0.0f and <= 1.0f. Read only.
 @param roomSize >= 0.0f and <= 1.0f. Read only.
 @param predelayMs Pre-delay in milliseconds. 0.0f to 500.0f. Read only.
 @param lowCutHz Frequency of a low cut (-12 db). Default: 0 (no low frequency cut). Read only.
 */
class SuperpoweredReverb: public SuperpoweredFX {
public:
<<<<<<< HEAD
// READ ONLY parameters, don't set them directly, use the methods below.
    float dry;
    float wet;
    float mix;
    float width;
    float damp;
    float roomSize;
    float predelayMs;
    float lowCutHz;
    
/**
 @brief You can set dry and wet independently, but don't use setMix in this case.
 
 @param value Limited to >= 0.0f and <= 1.0f.
 */
    void setDry(float value);
/**
 @brief You can set dry and wet independently, but don't use setMix in this case.
 
 @param value Limited to >= 0.0f and <= 1.0f.
 */
    void setWet(float value);
/**
 @brief Mix has a nice dry/wet constant power curve. Don't use setDry() and setWet() with this.
 
 @param value Limited to >= 0.0f and <= 1.0f.
 */
    void setMix(float value);
/**
 @brief Sets stereo width.
 
 @param value Limited to >= 0.0f and <= 1.0f.
 */
    void setWidth(float value);
/**
 @brief Sets high frequency damping.
 
 @param value Limited to >= 0.0f and <= 1.0f.
 */
    void setDamp(float value);
/**
 @brief Adjust room size.
 
 @param value Limited to >= 0.0f and <= 1.0f.
 */
    void setRoomSize(float value);
/**
 @brief Set pre-delay.
 
 @param ms Milliseconds.
 */
    void setPredelay(float ms);
/**
 @brief Set low-cut frequency.
 
 @param hz Frequency hz.
 */
    void setLowCut(float hz);
/**
 @brief Turns the effect on/off.
 */
    void enable(bool flag);

/**
 @brief Create a reverb instance with the current sample rate value.
 
 Enabled is false by default, use enable(true) to enable.
 
 @param samplerate The current sample rate.
 @param maximumSamplerate The maximum sample rate this effect will be operated. Affects memory usage.
 */
    SuperpoweredReverb(unsigned int samplerate, unsigned int maximumSamplerate = 96000);
    ~SuperpoweredReverb();
    
/**
 @brief Sets the sample rate.
 
 @param samplerate 44100, 48000, etc.
*/
    void setSamplerate(unsigned int samplerate);
/**
 @brief Reset all internals, sets the instance as good as new and turns it off.
 */
    void reset();

/**
 @brief Processes the audio.
 
 It's not locked when you call other methods from other threads, and they not interfere with process() at all.
 
 @return Put something into output or not.
 
 @param input 32-bit interleaved stereo input buffer. Can point to the same location with output (in-place processing). Special case: input can be NULL, reverb will output the tail only this case.
 @param output 32-bit interleaved stereo output buffer. Can point to the same location with input (in-place processing).
 @param numberOfSamples Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
 */
    bool process(float *input, float *output, unsigned int numberOfSamples);
=======
    float dry;        ///< Loudness of the dry signal. Don't use the mix property when using the dry and wet properties. >= 0 and <= 1. Default: 0.987...
    float wet;        ///< Loudness of the wet signal. Don't use the mix property when using the dry and wet properties. >= 0 and <= 1. Default: 0.587...
    float mix;        ///< Sets dry and wet simultaneously with a nice balanced power curve. Don't use the dry and wet properties while using mix. >= 0 and <= 1. Default: 0.4.
    float width;      ///< Stereo width of the reverberation. >= 0 and <= 1. Default: 1.
    float damp;       ///< Used to control the absorption of high frequencies in the reverb. More absorption of high frequencies means higher damping values. The tail of the reverb will lose high frequencies as they bounce around softer surfaces like halls and result in warmer sounds. >= 0 and <= 1. Default: 0.5.
    float roomSize;   ///< Room size controls the scale of the decay time and reflections found in the physical characteristics of living spaces, and studios. These unique attributes will simulate the expected behavior of acoustic environments. A larger room size typically results in longer reverb time. >= 0 and <= 1. Default: 0.8.
    float predelayMs; ///< Pre-delay in milliseconds. The length of time it takes for a sound wave to leave its source and create its first reflection is determined by the pre-delay. This property controls the offset of reverb from the dry signal. An increase in pre-delay can result in a feeling of a bigger space. 0 to 500. Default: 0.
    float lowCutHz;   ///< Frequency of the low cut in Hz (-12 db point). Controls the low frequency build up generated from the reverb. Default: 0 (no low frequency cut).

/// @brief Constructor. Enabled is false by default.
/// @param samplerate The initial sample rate in Hz.
/// @param maximumSamplerate Maximum sample rate (affects memory usage, the lower the smaller).
    JSWASM Reverb(unsigned int samplerate, unsigned int maximumSamplerate = 96000);
    JSWASM ~Reverb();

/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input. Can point to the same location with output (in-place processing). Special case: input can be NULL, the effect will output the tail only in this case.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param numberOfFrames Number of frames to process. Recommendation for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);
>>>>>>> master

private:
    reverbInternals *internals;    
    SuperpoweredReverb(const SuperpoweredReverb&);
    SuperpoweredReverb& operator=(const SuperpoweredReverb&);
};

#endif
