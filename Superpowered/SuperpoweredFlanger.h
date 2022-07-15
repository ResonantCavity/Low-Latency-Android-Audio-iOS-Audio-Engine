#ifndef Header_SuperpoweredFlanger
#define Header_SuperpoweredFlanger

#include "SuperpoweredFX.h"
struct flangerInternals;

/**
 @brief Flanger with aggressive sound ("jet").
 
 One instance allocates around 80 kb memory.
 
 @param wet 0.0f to 1.0f. Read only.
 @param depthMs Depth in milliseconds, 0.3f to 8.0f (0.3 ms to 8 ms). Read only.
 @param depth 0.0f to 1.0f (0.0 is 0.3 ms, 1.0 is 8 ms). Read only.
 @param lfoBeats The length in beats between the "lowest" and the "highest" jet sound, >= 0.25f and <= 128.0f. Read only.
 @param bpm Set this right for a nice sounding lfo. Limited to >= 40.0f and <= 250.0f. Read-write.
 @param clipperThresholdDb The flanger has a SuperpoweredClipper inside to prevent overdrive. This is it's thresholdDb parameter.
 @param clipperMaximumDb The flanger has a SuperpoweredClipper inside to prevent overdrive. This is it's maximumDb parameter.
 @param stereo Stereo/mono switch. Read-write.
 */
class SuperpoweredFlanger: public SuperpoweredFX {
public:
<<<<<<< HEAD
// READ ONLY parameters, don't set them directly, use the methods below.
    float wet;
    float depthMs;
    float depth;
    float lfoBeats;
    
// READ-WRITE parameters, thread safe (change from any thread)
    float bpm;
    float clipperThresholdDb;
    float clipperMaximumDb;
    bool stereo;
    
/**
 @brief Set wet.
 
 @param value 0.0f to 1.0f
 */
    void setWet(float value);
/**
 @brief Set depth.
 
 @param value 0.0f to 1.0f
 */
    void setDepth(float value);
/**
 @brief Set LFO, adjustable with beats.
 
 @param beats >= 0.25f and <= 64.0f
 */
    void setLFOBeats(float beats);
/**
 @brief Turns the effect on/off.
 */
    void enable(bool flag);
    
/**
 @brief Create a flanger instance with the current sample rate value.
 
 Enabled is false by default, use enable(true) to enable.
 */
    SuperpoweredFlanger(unsigned int samplerate);
    ~SuperpoweredFlanger();
    
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
 
 @param input 32-bit interleaved stereo input buffer. Can point to the same location with output (in-place processing).
 @param output 32-bit interleaved stereo output buffer. Can point to the same location with input (in-place processing).
 @param numberOfSamples Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
*/
    bool process(float *input, float *output, unsigned int numberOfSamples);
=======
    float wet;                ///< The wet signal mixed into the output. 0 to 1. Default: 0.7.
    float depth;              ///< How far the flanger deviates from the input sound. 0 is 0.3 ms, 1 is 8 ms.'0 to 1 (0 is 0.3 ms, 1 is 8 ms). Default: 0.16.
    float lfoBeats;           ///< The length in beats between the "lowest" and the "highest" jet sound. Depends on bpm property. >= 0.25 and <= 128. Default: 16.
    float bpm;                ///< The bpm of the current audio. Limited to >= 40 and <= 250. Default: 128.
    float clipperThresholdDb; ///< The flanger has a Clipper inside to prevent overdrive. This is the thresholdDb parameter. Default: -3.
    float clipperMaximumDb;   ///< The flanger has a Clipper inside to prevent overdrive. This is the maximumDb parameter. Default: 6.
    bool stereo;              ///< True: stereo, false: mono. It doesn't transform the input or output to mono, this applies for the additional jet effect only. Default: false.
    
/// @brief Constructor. Enabled is false by default.
/// @param samplerate The initial sample rate in Hz.
    JSWASM Flanger(unsigned int samplerate);
    JSWASM ~Flanger();
    
/// @brief Returns with the current depth in milliseconds, 0.3f to 8.0f (0.3 ms to 8 ms).
    JSWASM float getDepthMs();

/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties and call getDepthMs() on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);
>>>>>>> master
    
private:
    flangerInternals *internals;
    SuperpoweredFlanger(const SuperpoweredFlanger&);
    SuperpoweredFlanger& operator=(const SuperpoweredFlanger&);
};

#endif
