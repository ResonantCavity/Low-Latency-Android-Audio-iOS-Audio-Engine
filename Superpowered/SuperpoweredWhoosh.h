#ifndef Header_SuperpoweredWhoosh
#define Header_SuperpoweredWhoosh

#include "SuperpoweredFX.h"
struct whooshInternals;

/**
 @brief White noise + filter.
 
 One whoosh instance allocates around 4 kb memory.
 
 @param wet Limited to >= 0.0f and <= 1.0f. Read-write, thread-safe.
 @param frequency Limited to >= 20.0f and <= 20000.0f. Read only.
 */
class SuperpoweredWhoosh: public SuperpoweredFX {
public:
<<<<<<< HEAD
    float wet;
    float frequency;
    
/**
 @brief Sets the low pass filter's frequency.
 */
    void setFrequency(float hz);
/**
 @brief Turns the effect on/off.
 */
    void enable(bool flag); 

/**
 @brief Create a whoosh instance with the current sample rate value.
 Enabled is false by default, use enable(true) to enable.
*/
    SuperpoweredWhoosh(unsigned int samplerate);
    ~SuperpoweredWhoosh();
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
    float wet;       ///< White noise signal volume. Limited to >= 0 and <= 1. Default: 0.4.
    float frequency; ///< Limited to >= 20 and <= 20000. Default: 500.

/// @brief Constructor. Enabled is false by default.
/// @param samplerate The initial sample rate in Hz.
    JSWASM Whoosh(unsigned int samplerate);
    JSWASM ~Whoosh();
    
/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input. The output will be mixed to this. Can be NULL.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo input. Can point to the same location with output (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendation for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);
>>>>>>> master
    
private:
    whooshInternals *internals;
    SuperpoweredWhoosh(const SuperpoweredWhoosh&);
    SuperpoweredWhoosh& operator=(const SuperpoweredWhoosh&);
};

#endif
