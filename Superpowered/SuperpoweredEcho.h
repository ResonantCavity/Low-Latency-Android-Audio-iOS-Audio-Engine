#ifndef Header_SuperpoweredEcho
#define Header_SuperpoweredEcho

#include "SuperpoweredFX.h"
struct echoInternals;

/**
 @brief Simple echo.
 
 One instance allocates around 770 kb memory.
 
 @param dry >= 0.0f and <= 1.0f. Read only.
 @param wet >= 0.0f and <= 1.0f. Read only.
 @param bpm >= 40.0f and <= 250.0f. Read-write.
 @param beats Delay in beats, >= 0.03125f and <= 2.0f. Read-write.
 @param decay >= 0.0f and <= 0.99f. Read-write.
 */
class SuperpoweredEcho: public SuperpoweredFX {
public:
<<<<<<< HEAD
// READ ONLY parameters, don't set them directly, use the methods below.
    float dry, wet;

// READ-WRITE PARAMETERS:
    float bpm;
    float beats;
    float decay;

/**
 @brief Wet always equals to mix, but dry changes with a nice curve for a good echo/dry balance.
 
 @param mix >= 0.0f and <= 1.0f.
 */
    void setMix(float mix);
/**
 @brief Turns the effect on/off.
 */
    void enable(bool flag);
    
/**
 @brief Create an echo instance with the current sample rate value.
 
 Enabled is false by default, use enable(true) to enable.
 
 @param samplerate The current sample rate.
 @param maximumSamplerate Maximum sample rate to support. Affects memory usage.
 */
    SuperpoweredEcho(unsigned int samplerate, unsigned int maximumSamplerate = 96000);
    ~SuperpoweredEcho();
    
/**
 @brief Sets the sample rate.
 
 @param samplerate 44100, 48000, etc.
 */
    void setSamplerate(unsigned int samplerate); // 44100, 48000, etc.
/**
 @brief Reset all internals, sets the instance as good as new and turns it off.
 */
    void reset();
    
/**
 @brief Processes the audio.
 
 It's not locked when you call other methods from other threads, and they not interfere with process() at all.
 
 @return Put something into output or not.
 
 @param input 32-bit interleaved stereo input buffer. Can point to the same location with output (in-place processing). Special case: input can be NULL, echo will output the tail only this case.
 @param output 32-bit interleaved stereo output buffer. Can point to the same location with input (in-place processing).
 @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
 */
    bool process(float *input, float *output, unsigned int numberOfFrames);

/**
 @brief Processes the audio.
     
 It's not locked when you call other methods from other threads, and they not interfere with process() at all.
 
 @return Put something into output or not.
 
 @param input 32-bit interleaved stereo input buffer. Can point to the same location with output (in-place processing). Special case: input can be NULL, echo will output the tail only this case.
 @param output 32-bit interleaved stereo output buffer. Can point to the same location with input (in-place processing).
 @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
 @param fx Optional. If not NULL, the audio processing of fx (such as a SuperpoweredFilter) will be used to pass audio from input to the internal buffer.
*/
    bool process(float *input, float *output, unsigned int numberOfFrames, SuperpoweredFX *fx);
=======
    float dry;   ///< 0 to 1. Default: 1.
    float wet;   ///< 0 to 1. Default: 0.5.
    float bpm;   ///< Beats per minute, the base tempo of the echo. 40 to 250. Default: 128.
    float beats; ///< Delay between the echo sounds in beats. 0.03125 to 2. Default: 0.5.
    float decay; ///< Decay factor of the echo sounds. 0 to 0.99. Default: 0.5.
    
/// @brief Constructor. Enabled is false by default.
/// @param samplerate The initial sample rate in Hz.
/// @param maximumSamplerate Maximum sample rate (affects memory usage, the lower the smaller).
    JSWASM Echo(unsigned int samplerate, unsigned int maximumSamplerate = 96000);
    JSWASM ~Echo();

/// @brief Sets dry and wet simultaneously with a good balance between them. Wet always equals to mix, but dry changes with a curve.
/// @param mix >= 0 and <= 1.
    JSWASM void setMix(float mix);
    
/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties and call setMix() on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, it indicates silence. The contents of output are not changed in this case (not overwritten with zeros).
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input. Can point to the same location with output (in-place processing). Special case: input can be NULL, the effect will output the tail only in this case.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param numberOfFrames Number of frames to process. Recommendation for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);

/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties and call setMix() on any thread, concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input. Can point to the same location with output (in-place processing). Special case: input can be NULL, the effect will output the tail only in this case.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param numberOfFrames Number of frames to process. Recommendation for best performance: multiply of 4, minimum 64.
/// @param fx A Superpowered FX class instance, such as a Filter. fx->process() will be used to pass audio from input to the internal buffer, "coloring" the echo sounds.
    JSWASM bool processWithFx(float *input, float *output, unsigned int numberOfFrames, FX *fx);
>>>>>>> master
    
private:
    echoInternals *internals;
    SuperpoweredEcho(const SuperpoweredEcho&);
    SuperpoweredEcho& operator=(const SuperpoweredEcho&);
};

#endif
