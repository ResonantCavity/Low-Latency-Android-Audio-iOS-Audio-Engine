#ifndef Header_Superpowered3BandEQ
#define Header_Superpowered3BandEQ

#include "SuperpoweredFX.h"
struct eqInternals;

/**
 @brief Classic three-band equalizer with unique characteristics and total kills.
 
 It doesn't allocate any internal buffers and needs just a few bytes of memory.
 
 @param bands Low/mid/high gain. Read-write. 1.0f is "flat", 2.0f is +6db. Kill is enabled under -40 db (0.01f). Limits: 0.0f and 8.0f.
 @param enabled True if the effect is enabled (processing audio). Read only. Use the enable() method to set.
 */
class Superpowered3BandEQ: public SuperpoweredFX {
public:
<<<<<<< HEAD
    float bands[3]; // READ-WRITE parameter.

/**
 @brief Turns the effect on/off.
 */
    void enable(bool flag);
    
/**
 @brief Create an eq instance with the current sample rate value.
 
 Enabled is false by default, use enable(true) to enable. Example: Superpowered3BandEQ eq = new Superpowered3BandEQ(44100);
*/
    Superpowered3BandEQ(unsigned int samplerate);
    ~Superpowered3BandEQ();
    
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
    float low; ///< Low gain. Read-write. 1.0f is "flat", 2.0f is +6db. Kill is enabled under -40 db (0.01f). Default: 1.0f. Limits: 0.0f and 8.0f.
    float mid; ///< Mid gain. Read-write. 1.0f is "flat", 2.0f is +6db. Kill is enabled under -40 db (0.01f). Default: 1.0f. Limits: 0.0f and 8.0f.
    float high; ///< High gain. Read-write. 1.0f is "flat", 2.0f is +6db. Kill is enabled under -40 db (0.01f). Default: 1.0f. Limits: 0.0f and 8.0f.
    
/// @brief Constructor. Enabled is false by default.
/// @param samplerate The initial sample rate in Hz.
    JSWASM ThreeBandEQ(unsigned int samplerate);
    JSWASM ~ThreeBandEQ();
    
/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendation for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);
>>>>>>> master
    
private:
    eqInternals *internals;
    Superpowered3BandEQ(const Superpowered3BandEQ&);
    Superpowered3BandEQ& operator=(const Superpowered3BandEQ&);
};

#endif
