#ifndef Header_SuperpoweredCompressor
#define Header_SuperpoweredCompressor

#include "SuperpoweredFX.h"
struct compressorInternals;

/**
 @brief Compressor with 0 latency.
 
 It doesn't allocate any internal buffers and needs less than 1 kb of memory. One compressor instance needs just 5x CPU compared to a SuperpoweredFilter.
 
 @param inputGainDb Input gain in decibels, limited between -24.0f and 24.0f. Default: 0.
 @param outputGainDb Output gain in decibels, limited between -24.0f and 24.0f. Default: 0.
 @param wet Dry/wet ratio, limited between 0.0f (completely dry) and 1.0f (completely wet). Default: 1.0f.
 @param attackSec Attack in seconds (not milliseconds!). Limited between 0.0001f and 1.0f. Default: 0.003f (3 ms).
 @param releaseSec Release in seconds (not milliseconds!). Limited between 0.1f and 4.0f. Default: 0.3f (300 ms).
 @param ratio Ratio, rounded to 1.5f, 2.0f, 3.0f, 4.0f, 5.0f or 10.0f. Default: 3.0f.
 @param thresholdDb Threshold in decibels, limited between 0.0f and -40.0f. Default: 0.
 @param hpCutOffHz Key highpass filter frequency, limited between 1.0f and 10000.0f. Default: 1.0f.
 */
class SuperpoweredCompressor: public SuperpoweredFX {
public:
<<<<<<< HEAD
// READ-WRITE parameters
    float inputGainDb;
    float outputGainDb;
    float wet;
    float attackSec;
    float releaseSec;
    float ratio;
    float thresholdDb;
    float hpCutOffHz;

/**
 @brief Turns the effect on/off.
*/
    void enable(bool flag); // Use this to turn it on/off.

/**
 @brief Create a compressor instance with the current sample rate value.

 Enabled is false by default, use enable(true) to enable.
*/
    SuperpoweredCompressor(unsigned int samplerate);
    ~SuperpoweredCompressor();

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
 @return Returns the maximum gain reduction in decibels since the last getGainReductionDb() call.
 
 This method uses the log10f function, which is CPU intensive. Call it when you must update your user interface.
 */
    float getGainReductionDb();

/**
 @brief Processes interleaved audio.

 @return Put something into output or not.

 @param input 32-bit interleaved stereo input buffer. Can point to the same location with output (in-place processing).
 @param output 32-bit interleaved stereo output buffer. Can point to the same location with input (in-place processing).
 @param numberOfSamples Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
*/
    bool process(float *input, float *output, unsigned int numberOfSamples);
=======
    float inputGainDb;  ///< Input gain in decibels, limited between -24 and 24. Default: 0.
    float outputGainDb; ///< Output gain in decibels, limited between -24 and 24. Default: 0.
    float wet;          ///< Dry/wet ratio, limited between 0 (completely dry) and 1 (completely wet). Default: 1.
    float attackSec;    ///< Attack in seconds (not milliseconds!). Limited between 0.0001 and 1. Default: 0.003 (3 ms).
    float releaseSec;   ///< Release in seconds (not milliseconds!). Limited between 0.1 and 4. Default: 0.3 (300 ms).
    float ratio;        ///< Ratio, rounded to 1.5, 2.0, 3.0, 4.0, 5.0 or 10. Default: 3.
    float thresholdDb;  ///< Threshold in decibels, limited between 0 and -40. Default: 0.
    float hpCutOffHz;   ///< Key highpass filter frequency, limited between 1 and 10000. Default: 1.
    
/// @return Returns the maximum gain reduction in decibels since the last getGainReductionDb() call.
    JSWASM float getGainReductionDb();

/// @brief Constructor. Enabled is false by default.
/// @param samplerate The initial sample rate in Hz.
    JSWASM Compressor(unsigned int samplerate);
    JSWASM ~Compressor();
    
/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties and call getGainReductionDb() on any thread, concurrently with process().
/// If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);
>>>>>>> master

private:
    compressorInternals *internals;
    SuperpoweredCompressor(const SuperpoweredCompressor&);
    SuperpoweredCompressor& operator=(const SuperpoweredCompressor&);
};


struct compressor2Internals;

<<<<<<< HEAD
/**
 @brief The new Superpowered Compressor prototype. It can be used in production, but we're still collecting feedback on its feature set, therefore the documentation is not complete on this one.
 */

class SuperpoweredCompressorProto: public SuperpoweredFX {
public:
// READ-WRITE parameters
    float outputGainDb; // decibels
    float wet;          // 0.0f to 1.0f
    float attackSec;    // 0.0f to 1.0f
    float releaseSec;   // 0.001f to 4.0f
    float ratio;        // 1.0f to 1000.0f
    float thresholdDb;  // 0.0f to -100.0f
    float kneeDb;       // 0.0f to 100.0f
    unsigned char lookaheadMs; // doesn't work yet
    bool rms;           // false: follow peaks, true: follow RMS
    
    SuperpoweredCompressorProto(unsigned int samplerate);
    ~SuperpoweredCompressorProto();
    
    void enable(bool flag);
    void setSamplerate(unsigned int samplerate);
    void reset();
    float getGainReductionDb();
    bool process(float *input, float *output, unsigned int numberOfSamples); // input is the sidechain
    bool process(float *input, float *sidechain, float *output, unsigned int numberOfSamples); // separate sidechain
    
private:
    compressorProtoInternals *internals;
    SuperpoweredCompressorProto(const SuperpoweredCompressorProto&);
    SuperpoweredCompressorProto& operator=(const SuperpoweredCompressorProto&);
=======
/// @brief Compressor with 0 latency, adjustable knee and optional sidechain input.
/// It doesn't allocate any internal buffers and needs less than 1 kb of memory.
class Compressor2: public FX {
public:
    float attackSec;    ///< Attack in seconds (not milliseconds!). Limited between 0.00001 and 10. Default: 0.05 (50 ms).
    float holdSec;      ///< Hold segment before release starts, useful to limit unwanted noise with fast rates. 0 to 1 second (not millisecond). Default: 0.005 (5 ms).
    float releaseSec;   ///< Release in seconds (not milliseconds!). Limited between 0.00001 and 10. Default: 0.05 (50 ms).
    float ratio;        ///< Ratio, 1 to 1000. Default: 4.
    float thresholdDb;  ///< Threshold in decibels, limited between 0 and -60. Default: -6.
    float softKneeDb;   ///< Width of soft knee in decibels, 0 to 12. Default: 6.
    float outputGainDb; ///< Output gain in decibels, limited between -24 and 24. Default: 0.
    bool automaticGain; ///< If true, gain is set relative to compressor output at 0dB. Useful in digital environments. Default: true.
    
/// @brief Constructor. Enabled is false by default.
/// @param samplerate The initial sample rate in Hz.
    JSWASM Compressor2(unsigned int samplerate);
    JSWASM ~Compressor2();
    
/// @return Returns the maximum gain reduction in decibels since the last getGainReductionDb() call.
    JSWASM float getGainReductionDb();
    
/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process().
/// If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);
    
/// @brief Processes the audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process().
/// If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param sidechain Pointer to floating point numbers. 32-bit interleaved stereo sidechain input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
    JSWASM bool processWithSidechain(float *input, float *sidechain, float *output, unsigned int numberOfFrames);
    
private:
    compressor2Internals *internals;
    Compressor2(const Compressor2&);
    Compressor2& operator=(const Compressor2&);
>>>>>>> master
};

#endif
