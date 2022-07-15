#ifndef Header_SuperpoweredMixer
#define Header_SuperpoweredMixer

<<<<<<< HEAD
struct stereoMixerInternals;
struct monoMixerInternals;

/**
 @brief Mixer and splitter.
 
 Mixes max. 4 interleaved stereo inputs together. Output can be interleaved or non-interleaved (split). Separate input channel levels (good for gain and pan), separate output channel levels (master gain and pan). Returns maximum values for metering.
 
 One instance allocates just a few bytes of memory.
 */
class SuperpoweredStereoMixer {
public:
/**
 @brief Creates a stereo mixer instance.
 */
    SuperpoweredStereoMixer();
    ~SuperpoweredStereoMixer();
    
/**
 @brief Mixes max. 4 interleaved stereo inputs into a stereo output.
 
 @param inputs Four pointers to stereo interleaved input buffers. Any pointer can be NULL.
 @param outputs If outputs[1] is NULL, output is interleaved stereo in outputs[0]. If outputs[1] is not NULL, output is non-interleaved (left side in outputs[0], right side in outputs[1]).
 @param inputLevels Input volume level for each channel. Value changes between consecutive processes are automatically smoothed.
 @param outputLevels Output levels [left, right]. Value changes between consecutive processes are automatically smoothed.
 @param inputMeters Returns the maximum values for metering. Can be NULL.
 @param outputMeters Returns the maximum values for metering. Can be NULL.
 @param numberOfSamples The number of samples to process. Minimum 2, maximum 2048, must be exactly divisible with 2.
 */
    void process(float *inputs[4], float *outputs[2], float inputLevels[8], float outputLevels[2], float inputMeters[8], float outputMeters[2], unsigned int numberOfSamples);
=======
#ifndef JSWASM
#define JSWASM
#endif

namespace Superpowered {

struct stereoMixerInternals;
struct monoMixerInternals;

/// @brief Mixes up to 4 stereo inputs. From the traditional mixer hardware point of view, every input and the output has dedicated metering, gain and pan controls. One instance allocates just a few bytes of memory. Combining multiple instances of the StereoMixer is the recommended way to support more than 4 channels.
class StereoMixer {
public:
    float inputGain[8];  ///< Gain per input channel. Default value for all: 1. Changes between consecutive process() calls are automatically smoothed. Example: inputGain[0] = input 0 left, inputGain[1] = input 0 right, inputGain[2] = input 1 left, ...
    float inputPeak[8];  ///< The peak absolute audio volume per input channel, updated after every process() call, measured before any gain. Example: inputPeak[0] = input 0 left, inputPeak[1] = input 0 right, inputPeak[2] = input 1 left, ...
    float outputGain[2]; ///< Output gain. [0] is left side, [1] is right side. Default value for all: 1. Changes between consecutive process() calls are automatically smoothed.
    float outputPeak[2]; ///< The peak absolute audio volume for the output, updated after every process() call. [0] is left side, [1] is right side.

    /// @brief Constructor.
    JSWASM StereoMixer();
    JSWASM ~StereoMixer();

    /// @brief Mixes up to 4 interleaved stereo inputs into a stereo output.
    /// @param input0 Pointer to floating point numbers. 32-bit interleaved stereo input buffer for the first input. Can be NULL.
    /// @param input1 Pointer to floating point numbers. 32-bit interleaved stereo input buffer for the second input. Can be NULL.
    /// @param input2 Pointer to floating point numbers. 32-bit interleaved stereo input buffer for the third input. Can be NULL.
    /// @param input3 Pointer to floating point numbers. 32-bit interleaved stereo input buffer for the fourth input. Can be NULL.
    /// @param output Pointer to floating point numbers. 32-bit interleaved stereo output buffer.
    /// @param numberOfFrames Number of frames to process. Must be an even number.
    JSWASM void process(float *input0, float *input1, float *input2, float *input3, float *output, unsigned int numberOfFrames);
>>>>>>> master

private:
    stereoMixerInternals *internals;
    SuperpoweredStereoMixer(const SuperpoweredStereoMixer&);
    SuperpoweredStereoMixer& operator=(const SuperpoweredStereoMixer&);
};

<<<<<<< HEAD
/**
@brief Mixes max. 4 mono inputs into a mono output.
 
 One instance allocates just a few bytes of memory.
 */
class SuperpoweredMonoMixer {
public:
/**
 @brief Creates a mono mixer instance.
*/
    SuperpoweredMonoMixer();
    ~SuperpoweredMonoMixer();
    
/**
 @brief Processes the audio.
 
 @param inputs Four pointers to input buffers. Any pointer can be NULL.
 @param output Output buffer.
 @param inputLevels Four input volume levels. Value changes between consecutive processes are automatically smoothed.
 @param outputGain Output level. Value changes between consecutive processes are automatically smoothed.
 @param numberOfSamples The number of samples to process. Minimum 8, maximum 2048, must be exactly divisible with 4.
 */
    void process(float **inputs, void *output, float *inputLevels, float outputGain, unsigned int numberOfSamples);
    
=======
/// @brief Mixes up to 4 mono inputs. Every input and the output has individual gain control. One instance allocates just a few bytes of memory. Combining multiple instances of the MonoMixer is the recommended way to support more than 4 channels.
class MonoMixer {
public:
    float inputGain[4]; ///< Gain per input channel. Default value for all: 1. Changes between consecutive process() calls are automatically smoothed.
    float outputGain;   ///< Gain for the output. Default value: 1. Changes between consecutive process() calls are automatically smoothed.

    /// @brief Constructor.
    JSWASM MonoMixer();
    JSWASM ~MonoMixer();

    /// @brief Mixes up to 4 mono inputs into a mono output.
    /// @param input0 Pointer to floating point numbers. 32-bit input buffer for the first input. Can be NULL.
    /// @param input1 Pointer to floating point numbers. 32-bit input buffer for the second input. Can be NULL.
    /// @param input2 Pointer to floating point numbers. 32-bit input buffer for the third input. Can be NULL.
    /// @param input3 Pointer to floating point numbers. 32-bit input buffer for the fourth input. Can be NULL.
    /// @param output Pointer to floating point numbers. 32-bit output buffer.
    /// @param numberOfFrames Number of frames to process. Must be a multiple of 4.
    JSWASM void process(float *input0, float *input1, float *input2, float *input3, float *output, unsigned int numberOfFrames);

>>>>>>> master
private:
    monoMixerInternals *internals;
    SuperpoweredMonoMixer(const SuperpoweredMonoMixer&);
    SuperpoweredMonoMixer& operator=(const SuperpoweredMonoMixer&);
};

#endif
