#ifndef Header_SuperpoweredDelay
#define Header_SuperpoweredDelay

#include "SuperpoweredFX.h"
struct delayInternals;

/**
 @brief Simple delay with minimum memory operations.
 
 @param delayMs Delay in milliseconds.
 */
class SuperpoweredDelay {
public:
<<<<<<< HEAD
    float delayMs; // READ-WRITE parameter
    
/**
 @brief Create a delay instance.
 
 @param maximumDelayMs Maximum delay in milliseconds. Affects memory usage.
 @param maximumSamplerate Maximum sample rate to support. Affects memory usage.
 @param maximumNumberOfFramesToProcess Maximum number of frames for the process() call. Has minimum effect on memory usage.
 @param samplerate The current sample rate.
 */
    SuperpoweredDelay(unsigned int maximumDelayMs, unsigned int maximumSamplerate, unsigned int maximumNumberOfFramesToProcess, unsigned int samplerate);
    ~SuperpoweredDelay();
    
/**
 @brief Sets the sample rate.
     
 @param samplerate 44100, 48000, etc.
*/
    void setSamplerate(unsigned int samplerate); // 44100, 48000, etc.
    
/**
     @brief Reset all internals, sets the instance as good as new.
*/
    void reset();
    
/**
 @brief Processes the audio.
 
 @return Pointer to the output having numberOfFrames audio available. It is valid until the next call to process().
 
 @param input 32-bit interleaved stereo input.
 @param numberOfFrames Number of frames to input and output.
 @param fx Optional. If NULL, then simple memory copy will be used to pass audio from input to the internal buffer. If not NULL, the audio processing of fx (such as a SuperpoweredFilter) will be used to pass audio from input to the internal buffer.
 */
    const float * const process(float *input, int numberOfFrames, SuperpoweredFX *fx = 0);
=======
    float delayMs;           ///< Delay in milliseconds. Default: 0.
    unsigned int samplerate; ///< Sample rate in Hz.
    
/// @brief Constructor.
/// @param maximumDelayMs Maximum delay in milliseconds. Higher values increase memory usage.
/// @param maximumSamplerate Maximum sample rate to support. Higher values increase memory usage.
/// @param maximumNumberOfFramesToProcess Maximum number of frames for the process() call. Has minimum effect on memory usage.
/// @param samplerate The initial sample rate in Hz.
    JSWASM Delay(unsigned int maximumDelayMs, unsigned int maximumSamplerate, unsigned int maximumNumberOfFramesToProcess, unsigned int samplerate);
    JSWASM ~Delay();
    
/// @brief Processes the audio.
/// It's never blocking for real-time usage. You can change any properties concurrently with process().
/// @return Returns with a pointer to floating point numbers, which is the output with numberOfFrames audio available in it. It is valid until the next call to process().
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input. Special case: set to NULL to empty all buffered content.
/// @param numberOfFrames Number of frames to input and output.
    JSWASM const float * const process(float *input, int numberOfFrames);
    
/// @brief Processes the audio.
/// It's never blocking for real-time usage. You can change any properties concurrently with process().
/// @return Returns with a pointer to floating point numbers, which is the output with numberOfFrames audio available in it. It is valid until the next call to process().
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input. Special case: set to NULL to empty all buffered content.
/// @param numberOfFrames Number of frames to input and output.
/// @param fx A Superpowered FX class instance, such as a Filter. fx->process() will be used to pass audio from input to the internal buffer.
    JSWASM const float * const processWithFx(float *input, int numberOfFrames, FX *fx);
>>>>>>> master
   
private:
    delayInternals *internals;
    SuperpoweredDelay(const SuperpoweredDelay&);
    SuperpoweredDelay& operator=(const SuperpoweredDelay&);
};

#endif
