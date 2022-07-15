#ifndef Header_SuperpoweredSimple
#define Header_SuperpoweredSimple

<<<<<<< HEAD
/**
 @file SuperpoweredSimple.h
 @brief Simple fast utility functions for transforming audio.
 */


/**
 @fn SuperpoweredVolume(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfSamples);
 @brief Applies volume on a single stereo interleaved buffer.

 @param input Input buffer.
 @param output Output buffer. Can be equal to input (in-place processing).
 @param volumeStart Volume for the first sample.
 @param volumeEnd Volume for the last sample. Volume will be smoothly calculated between start end end.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredVolume(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfSamples);

/**
 @fn SuperpoweredChangeVolume(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfSamples);
 @brief Applies volume on a single stereo interleaved buffer.

 @param input Input buffer.
 @param output Output buffer. Can be equal to input (in-place processing).
 @param volumeStart Voume for the first sample.
 @param volumeChange Change volume by this amount for every sample.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredChangeVolume(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfSamples);

/**
 @fn SuperpoweredVolumeAdd(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfSamples);
 @brief Applies volume on a single stereo interleaved buffer and adds it to the audio in the output buffer.

 @param input Input buffer.
 @param output Output buffer.
 @param volumeStart Volume for the first sample.
 @param volumeEnd Volume for the last sample. Volume will be smoothly calculated between start end end.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredVolumeAdd(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfSamples);

/**
 @fn SuperpoweredChangeVolumeAdd(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfSamples);
 @brief Applies volume on a single stereo interleaved buffer and adds it to the audio in the output buffer.

 @param input Input buffer.
 @param output Output buffer.
 @param volumeStart Volume for the first sample.
 @param volumeChange Change volume by this amount for every sample.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredChangeVolumeAdd(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfSamples);

/**
 @fn SuperpoweredPeak(float *input, unsigned int numberOfValues);
 @return Returns the peak value.

 @param input An array of floating point values.
 @param numberOfValues The number of values to process. (2 * numberOfSamples for stereo input) Must be a multiply of 8.
 */
float SuperpoweredPeak(float *input, unsigned int numberOfValues);

/**
 @fn SuperpoweredCharToFloat(signed char *input, float *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 8-bit audio to 32-bit floating point.
 
 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void SuperpoweredCharToFloat(signed char *input, float *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn SuperpoweredFloatToChar(float *input, signed char *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 32-bit floating point audio 8-bit audio.

 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void SuperpoweredFloatToChar(float *input, signed char *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn Superpowered24bitToFloat(void *input, float *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 24-bit audio to 32-bit floating point.

 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void Superpowered24bitToFloat(void *input, float *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn SuperpoweredFloatTo24bit(float *input, void *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 32-bit floating point audio to 24-bit.

 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void SuperpoweredFloatTo24bit(float *input, void *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn SuperpoweredIntToFloat(int *input, float *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 32-bit integer audio to 32-bit floating point.

 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void SuperpoweredIntToFloat(int *input, float *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn SuperpoweredFloatToInt(float *input, int *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 32-bit floating point audio to 32-bit integer.

 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void SuperpoweredFloatToInt(float *input, int *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn SuperpoweredFloatToShortInt(float *input, short int *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 32-bit float input to 16-bit signed integer output.

 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void SuperpoweredFloatToShortInt(float *input, short int *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn SuperpoweredFloatToShortIntInterleave(float *inputLeft, float *inputRight, short int *output, unsigned int numberOfSamples);
 @brief Converts two 32-bit float input channels to stereo interleaved 16-bit signed integer output.

 @param inputLeft 32-bit input for the left side. Should be numberOfSamples + 8 big minimum.
 @param inputRight 32-bit input for the right side. Should be numberOfSamples + 8 big minimum.
 @param output Stereo interleaved 16-bit output. Should be numberOfSamples * 2 + 16 big minimum.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredFloatToShortIntInterleave(float *inputLeft, float *inputRight, short int *output, unsigned int numberOfSamples);

/**
 @fn SuperpoweredShortIntToFloat(short int *input, float *output, unsigned int numberOfSamples, float *peaks);
 @brief Converts a stereo interleaved 16-bit signed integer input to stereo interleaved 32-bit float output.

 @param input Stereo interleaved 16-bit input. Should be numberOfSamples + 8 big minimum.
 @param output Stereo interleaved 32-bit output. Should be numberOfSamples + 8 big minimum.
 @param numberOfSamples The number of samples to process.
 @param peaks Peak value result (2 floats: left peak, right peak).
 */
void SuperpoweredShortIntToFloat(short int *input, float *output, unsigned int numberOfSamples, float *peaks);

/**
 @fn SuperpoweredShortIntToFloat(short int *input, float *output, unsigned int numberOfSamples, unsigned int numChannels);
 @brief Converts 16-bit signed integer input to 32-bit float output.

 @param input Input buffer.
 @param output Output buffer.
 @param numberOfSamples The number of samples to process.
 @param numChannels The number of channels. One sample may be 1 value (1 channels) or N values (N channels).
 */
void SuperpoweredShortIntToFloat(short int *input, float *output, unsigned int numberOfSamples, unsigned int numChannels = 2);

/**
 @fn SuperpoweredInterleave(float *left, float *right, float *output, unsigned int numberOfSamples);
 @brief Makes an interleaved output from two input channels.
 
 @param left Input for left channel.
 @param right Input for right channel.
 @param output Interleaved output.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredInterleave(float *left, float *right, float *output, unsigned int numberOfSamples);

/**
 @fn SuperpoweredInterleaveAdd(float *left, float *right, float *output, unsigned int numberOfSamples);
 @brief Makes an interleaved audio from two input channels and adds the result to the output.

 @param left Input for left channel.
 @param right Input for right channel.
 @param output Interleaved output.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredInterleaveAdd(float *left, float *right, float *output, unsigned int numberOfSamples);

/**
 @fn SuperpoweredInterleaveAndGetPeaks(float *left, float *right, float *output, unsigned int numberOfSamples, float *peaks);
 @brief Makes an interleaved output from two input channels, and measures the input volume.

 @param left Input for left channel.
 @param right Input for right channel.
 @param output Interleaved output.
 @param numberOfSamples The number of samples to process.
 @param peaks Peak value result (2 floats: left peak, right peak).
 */
void SuperpoweredInterleaveAndGetPeaks(float *left, float *right, float *output, unsigned int numberOfSamples, float *peaks);

/**
 @fn SuperpoweredDeInterleave(float *input, float *left, float *right, unsigned int numberOfSamples);
 @brief Deinterleaves an interleaved input.

 @param input Interleaved input.
 @param left Output for left channel.
 @param right Output for right channel.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredDeInterleave(float *input, float *left, float *right, unsigned int numberOfSamples);

/**
 @fn SuperpoweredDeInterleaveMultiply(float *input, float *left, float *right, unsigned int numberOfSamples, float multiplier);
 @brief Deinterleaves an interleaved input and multiplies the output.
 
 @param input Interleaved input.
 @param left Output for left channel.
 @param right Output for right channel.
 @param numberOfSamples The number of samples to process.
 @param multiplier Multiply each output sample with this value.
 */
void SuperpoweredDeInterleaveMultiply(float *input, float *left, float *right, unsigned int numberOfSamples, float multiplier);

/**
 @fn SuperpoweredDeInterleaveAdd(float *input, float *left, float *right, unsigned int numberOfSamples);
 @brief Deinterleaves an interleaved input and adds the results to the output channels.

 @param input Interleaved input.
 @param left Output for left channel.
 @param right Output for right channel.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredDeInterleaveAdd(float *input, float *left, float *right, unsigned int numberOfSamples);

/**
 @fn SuperpoweredDeInterleaveMultiplyAdd(float *input, float *left, float *right, unsigned int numberOfSamples, float multiplier);
 @brief Deinterleaves an interleaved input, multiplies the results and adds them to the output channels.
 
 @param input Interleaved input.
 @param left Output for left channel.
 @param right Output for right channel.
 @param numberOfSamples The number of samples to process.
 @param multiplier Multiply each output sample with this value.
 */
void SuperpoweredDeInterleaveMultiplyAdd(float *input, float *left, float *right, unsigned int numberOfSamples, float multiplier);

/**
 @fn SuperpoweredHasNonFinite(float *buffer, unsigned int numberOfValues);
 @brief Checks if the samples has non-valid samples, such as infinity or NaN (not a number).
 
 @param buffer The buffer to check.
 @param numberOfValues Number of values in buffer. For stereo buffers, multiply by two!
 */
bool SuperpoweredHasNonFinite(float *buffer, unsigned int numberOfValues);

/**
 @fn SuperpoweredStereoToMono(float *input, float *output, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);
 @brief Makes mono output from stereo input.

 @param input Stereo interleaved input.
 @param output Output.
 @param leftGainStart Gain of the first sample on the left channel.
 @param leftGainEnd Gain for the last sample on the left channel. Gain will be smoothly calculated between start end end.
 @param rightGainStart Gain of the first sample on the right channel.
 @param rightGainEnd Gain for the last sample on the right channel. Gain will be smoothly calculated between start end end.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredStereoToMono(float *input, float *output, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);

/**
 @fn SuperpoweredStereoToMono2(float *input, float *output0, float *output1, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);
 @brief Makes two mono outputs from stereo input.

 @param input Stereo interleaved input.
 @param output0 Output.
 @param output1 Output.
 @param leftGainStart Gain of the first sample on the left channel.
 @param leftGainEnd Gain for the last sample on the left channel. Gain will be smoothly calculated between start end end.
 @param rightGainStart Gain of the first sample on the right channel.
 @param rightGainEnd Gain for the last sample on the right channel. Gain will be smoothly calculated between start end end.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredStereoToMono2(float *input, float *output0, float *output1, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);

/**
 @fn SuperpoweredCrossMono(float *left, float *right, float *output, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);
 @brief Makes mono output from two separate input channels.
 
 @param left Input for left channel.
 @param right Input for right channel.
 @param output Output.
 @param leftGainStart Gain of the first sample on the left channel.
 @param leftGainEnd Gain for the last sample on the left channel. Gain will be smoothly calculated between start end end.
 @param rightGainStart Gain of the first sample on the right channel.
 @param rightGainEnd Gain for the last sample on the right channel. Gain will be smoothly calculated between start end end.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredCrossMono(float *left, float *right, float *output, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);

/**
 @fn SuperpoweredCrossMono2(float *left, float *right, float *output0, float *output1, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);
 @brief Makes two mono outputs from two separate input channels.

 @param left Input for left channel.
 @param right Input for right channel.
 @param output0 Output.
 @param output1 Output.
 @param leftGainStart Gain of the first sample on the left channel.
 @param leftGainEnd Gain for the last sample on the left channel. Gain will be smoothly calculated between start end end.
 @param rightGainStart Gain of the first sample on the right channel.
 @param rightGainEnd Gain for the last sample on the right channel. Gain will be smoothly calculated between start end end.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredCrossMono2(float *left, float *right, float *output0, float *output1, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfSamples);

/**
 @fn SuperpoweredCrossStereo(float *inputA, float *inputB, float *output, float gainStart[4], float gainEnd[4], unsigned int numberOfSamples);
 @brief Crossfades two separate input channels.

 @param inputA Interleaved stereo input (first).
 @param inputB Interleaved stereo input (second).
 @param output Interleaved stereo output.
 @param gainStart Gain of the first sample (first left, first right, second left, second right).
 @param gainEnd Gain for the last sample (first left, first right, second left, second right). Gain will be smoothly calculated between start end end.
 @param numberOfSamples The number of samples to process.
 */
void SuperpoweredCrossStereo(float *inputA, float *inputB, float *output, float gainStart[4], float gainEnd[4], unsigned int numberOfSamples);

/**
 @fn SuperpoweredAdd1(float *input, float *output, unsigned int numberOfValues)
 @brief Adds input to output.
 
 @param input Input data.
 @param output Output data.
 @param numberOfValues The length of input.
 */
void SuperpoweredAdd1(float *input, float *output, unsigned int numberOfValues);

/**
 @fn SuperpoweredAdd2(float *inputA, float *inputB, float *output, unsigned int numberOfValues)
 @brief Adds two inputs to an output.

 @param inputA Input data.
 @param inputB Input data.
 @param output Output data.
 @param numberOfValues The length of input.
 */
void SuperpoweredAdd2(float *inputA, float *inputB, float *output, unsigned int numberOfValues);

/**
 @fn SuperpoweredAdd4(float *inputA, float *inputB, float *inputC, float *inputD, float *output, unsigned int numberOfValues)
 @brief Adds 4 inputs to an output.

 @param inputA Input data.
 @param inputB Input data.
 @param inputC Input data.
 @param inputD Input data.
 @param output Output data.
 @param numberOfValues The length of input.
 */
void SuperpoweredAdd4(float *inputA, float *inputB, float *inputC, float *inputD, float *output, unsigned int numberOfValues);

/**
 @fn SuperpoweredStereoToMidSide(float *input, float *output, unsigned int numberOfFrames)
 @brief Converts a stereo signal to mid-side.
 
 @param input Input buffer.
 @param output Output buffer. Can be equal to input (in-place processing).
 @param numberOfFrames The number of frames to process.
 */
void SuperpoweredStereoToMidSide(float *input, float *output, unsigned int numberOfFrames);

/**
 @fn SuperpoweredMidSideToStereo(float *input, float *output, unsigned int numberOfFrames)
 @brief Converts a mid-side signal to stereo.
 
 @param input Input buffer.
 @param output Output buffer. Can be equal to input (in-place processing).
 @param numberOfFrames The number of frames to process.
 */
void SuperpoweredMidSideToStereo(float *input, float *output, unsigned int numberOfFrames);

/**
 @fn SuperpoweredDotProduct(float *input0, float *input1, unsigned int numValues)
 @brief Calculates the dot product of two vectors.
 
 @param input0 First input vector.
 @param input1 Second input vector.
 @param numValues Number of value pairs to process.
 @return The dot product.
 */
float SuperpoweredDotProduct(float *input0, float *input1, unsigned int numValues);

/**
 @fn SuperpoweredVersion()
 @return Returns the current version of the Superpowered SDK.
 
 The returned value is: major version * 10000 + minor version * 100 + revision
 Example: 10402 means 1.4.2
 */
unsigned int SuperpoweredVersion();
=======
#ifndef JSWASM
#define JSWASM
#endif

#include <stdio.h>

/// @file SuperpoweredSimple.h
/// @brief Fast utility functions for transforming audio.

namespace Superpowered {

/// @fn Volume(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfFrames);
/// @brief Applies volume on a single stereo interleaved buffer: output = input * gain
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can be equal to input (in-place processing).
/// @param volumeStart Volume for the first frame.
/// @param volumeEnd Volume for the last frame. Volume will be smoothly calculated between the first and last frames.
/// @param numberOfFrames The number of frames to process.
JSWASM void Volume(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfFrames);

/// @fn ChangeVolume(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfFrames);
/// @brief Applies volume on a single stereo interleaved buffer: output = input * gain
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can be equal to input (in-place processing).
/// @param volumeStart Volume for the first frame.
/// @param volumeChange Change volume by this amount for every frame.
/// @param numberOfFrames The number of frames to process.
JSWASM void ChangeVolume(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfFrames);

/// @fn VolumeAdd(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfFrames);
/// @brief Applies volume on a single stereo interleaved buffer and adds it to the audio in the output buffer: output = output + input * gain
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param volumeStart Volume for the first frame.
/// @param volumeEnd Volume for the last frame. Volume will be smoothly calculated between the first and last frames.
/// @param numberOfFrames The number of frames to process.
JSWASM void VolumeAdd(float *input, float *output, float volumeStart, float volumeEnd, unsigned int numberOfFrames);

/// @fn ChangeVolumeAdd(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfFrames);
/// @brief Applies volume on a single stereo interleaved buffer and adds it to the audio in the output buffer: output = output + input * gain
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param volumeStart Volume for the first frame.
/// @param volumeChange Change volume by this amount for every frame.
/// @param numberOfFrames The number of frames to process.
JSWASM void ChangeVolumeAdd(float *input, float *output, float volumeStart, float volumeChange, unsigned int numberOfFrames);

/// @fn Peak(float *input, unsigned int numberOfValues);
/// @return Returns the peak absolute value. Useful for metering.
/// @param input Pointer to floating point numbers.
/// @param numberOfValues The number of values to process. For a stereo input this value should be 2 * numberOfFrames. Must be a multiply of 8.
JSWASM float Peak(float *input, unsigned int numberOfValues);

/// @fn CharToFloat(signed char *input, float *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 8-bit audio to 32-bit floating point.
/// @param input Pointer to signed bytes. 8-bit input.
/// @param output Pointer to floating point numbers. 32-bit output.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void CharToFloat(signed char *input, float *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn FloatToChar(float *input, signed char *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 32-bit floating point audio 8-bit audio.
/// @param input Pointer to floating point numbers. 32-bit input.
/// @param output Pointer to signed bytes. 8-bit output.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void FloatToChar(float *input, signed char *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn Bit24ToFloat(void *input, float *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 24-bit audio to 32-bit floating point.
/// @param input Input buffer pointer.
/// @param output Pointer to floating point numbers. 32-bit output.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void Bit24ToFloat(void *input, float *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn FloatTo24bit(float *input, void *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 32-bit floating point audio to 24-bit.
/// @param input Pointer to floating point numbers. 32-bit input.
/// @param output Output buffer pointer.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void FloatTo24bit(float *input, void *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn IntToFloat(int *input, float *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 32-bit integer audio to 32-bit floating point.
/// @param input Pointer to integer numbers. 32-bit input.
/// @param output Pointer to floating point numbers. 32-bit output.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void IntToFloat(int *input, float *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn FloatToInt(float *input, int *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 32-bit floating point audio to 32-bit integer.
/// @param input Pointer to floating point numbers. 32-bit input.
/// @param output Pointer to integer numbers. 32-bit output.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void FloatToInt(float *input, int *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn FloatToShortInt(float *input, short int *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 32-bit float input to 16-bit signed integer output.
/// @param input Pointer to floating point numbers. 32-bit input.
/// @param output Pointer to short integer numbers. 16-bit output.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void FloatToShortInt(float *input, short int *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn FloatToShortIntInterleave(float *inputLeft, float *inputRight, short int *output, unsigned int numberOfFrames);
/// @brief Converts two 32-bit mono float input channels to stereo interleaved 16-bit signed integer output.
/// @param inputLeft Pointer to floating point numbers. 32-bit input for the left side. Should be numberOfFrames + 8 big minimum.
/// @param inputRight Pointer to floating point numbers. 32-bit input for the right side. Should be numberOfFrames + 8 big minimum.
/// @param output Pointer to short integer numbers. Stereo interleaved 16-bit output. Should be numberOfFrames * 2 + 16 big minimum.
/// @param numberOfFrames The number of frames to process.
JSWASM void FloatToShortIntInterleave(float *inputLeft, float *inputRight, short int *output, unsigned int numberOfFrames);

/// @fn ShortIntToFloatGetPeaks(short int *input, float *output, unsigned int numberOfFrames, float *peaks);
/// @brief Converts stereo interleaved 16-bit signed integer input to stereo interleaved 32-bit float output, and provides peak measurement.
/// @param input Pointer to short integer numbers. Stereo interleaved 16-bit input. Should be numberOfFrames + 8 big minimum.
/// @param output Pointer to floating point numbers. Stereo interleaved 32-bit output. Should be numberOfFrames + 8 big minimum.
/// @param numberOfFrames The number of frames to process.
/// @param peaks Pointer to two floating point numbers. Peak value result (left, right).
JSWASM void ShortIntToFloatGetPeaks(short int *input, float *output, unsigned int numberOfFrames, float *peaks);

/// @fn ShortIntToFloat(short int *input, float *output, unsigned int numberOfFrames, unsigned int numChannels);
/// @brief Converts 16-bit signed integer input to 32-bit float output.
/// @param input Pointer to short integer numbers. Stereo interleaved 16-bit input.
/// @param output Pointer to floating point numbers. Stereo interleaved 32-bit output.
/// @param numberOfFrames The number of frames to process.
/// @param numChannels The number of channels.
JSWASM void ShortIntToFloat(short int *input, float *output, unsigned int numberOfFrames, unsigned int numChannels = 2);

/// @fn CopyMonoToInterleaved(float *monoInput, unsigned int channelIndex, float *interleavedOutput, unsigned int numInterleavedChannels, unsigned int numberOfFrames);
/// @brief Copy a mono channel into an interleaved buffer.
/// @param monoInput Pointer to floating point numbers. Mono input.
/// @param channelIndex Copy to this channel.
/// @param interleavedOutput Pointer to floating point numbers. Interleaved output.
/// @param numInterleavedChannels The total number of channels in the interleaved output.
/// @param numberOfFrames The number of frames to process.
JSWASM void CopyMonoToInterleaved(float *monoInput, unsigned int channelIndex, float *interleavedOutput, unsigned int numInterleavedChannels, unsigned int numberOfFrames);

/// @fn CopyStereoToInterleaved(float *stereoInput, unsigned int channelIndex, float *interleavedOutput, unsigned int numInterleavedChannels, unsigned int numberOfFrames, float multiplier);
/// @brief Copy interleaved stereo into an interleaved buffer.
/// @param stereoInput Pointer to floating point numbers. Stereo interleaved input.
/// @param channelIndex Copy to this channel pair. Left channel goes to channelIndex, right channel goes to channelIndex + 1.
/// @param interleavedOutput Pointer to floating point numbers. Interleaved output.
/// @param numInterleavedChannels The total number of channels in the interleaved output.
/// @param numberOfFrames The number of frames to process.
/// @param multiplier Multiply the output with this number (constant volume).
JSWASM void CopyStereoToInterleaved(float *stereoInput, unsigned int channelIndex, float *interleavedOutput, unsigned int numInterleavedChannels, unsigned int numberOfFrames, float multiplier = 1.0f);

/// @fn CopyMonoFromInterleaved(float *interleavedInput, float *monoOutput, unsigned int numberOfFrames, unsigned int channelIndex);
/// @brief Copy mono audio from an interleaved buffer.
/// @param interleavedInput Pointer to floating point numbers. Interleaved input.
/// @param numInterleavedChannels The total number of channels in the interleaved input.
/// @param monoOutput Pointer to floating point numbers. Mono output.
/// @param channelIndex Copy this channel.
/// @param numberOfFrames The number of frames to process.
JSWASM void CopyMonoFromInterleaved(float *interleavedInput, unsigned int numInterleavedChannels, float *monoOutput, unsigned int channelIndex, unsigned int numberOfFrames);

/// @fn CopyStereoFromInterleaved(float *interleavedInput, float *monoOutput, unsigned int numberOfFrames, unsigned int channelIndex);
/// @brief Copy stereo audio from an interleaved buffer.
/// @param interleavedInput Pointer to floating point numbers. Interleaved input.
/// @param numInterleavedChannels The total number of channels in the interleaved input.
/// @param stereoOutput Pointer to floating point numbers. Stereo interleaved output.
/// @param channelIndex Copy this channel. channelIndex is the left side, channelIndex + 1 is the right side.
/// @param numberOfFrames The number of frames to process.
JSWASM void CopyStereoFromInterleaved(float *interleavedInput, unsigned int numInterleavedChannels, float *stereoOutput, unsigned int channelIndex, unsigned int numberOfFrames);

/// @fn GetPeaks(float *interleavedInput, unsigned int numInterleavedChannels, float *peaks);
/// @brief Get the peak values of each channel in an interleaved buffer.
/// @param interleavedInput Pointer to floating point numbers. Interleaved input.
/// @param numInterleavedChannels The total number of channels in the interleaved input.
/// @param numberOfFrames The number of frames to process.
/// @param peaks Pointer to floating point numbers. Peak value result, should be numInterleavedChannels big minimum.
JSWASM void GetPeaks(float *interleavedInput, unsigned int numInterleavedChannels, unsigned int numberOfFrames, float *peaks);

/// @fn Interleave(float *left, float *right, float *output, unsigned int numberOfFrames);
/// @brief Makes an interleaved stereo output from two mono input channels: output = [L, R, L, R, ...]
/// @param left Pointer to floating point numbers. Mono input for left channel.
/// @param right Pointer to floating point numbers. Mono input for right channel.
/// @param output Pointer to floating point numbers. Stereo interleaved output.
/// @param numberOfFrames The number of frames to process.
JSWASM void Interleave(float *left, float *right, float *output, unsigned int numberOfFrames);

/// @fn Interleave(float *left, float *right, float *output, unsigned int numberOfFrames);
/// @brief Makes an interleaved stereo output from two mono input channels and adds the result to the audio in the output buffer: output = output + [L, R, L, R, ...]
/// @param left Pointer to floating point numbers. Mono input for left channel.
/// @param right Pointer to floating point numbers. Mono input for right channel.
/// @param output Pointer to floating point numbers. Stereo interleaved output.
/// @param numberOfFrames The number of frames to process.
JSWASM void InterleaveAdd(float *left, float *right, float *output, unsigned int numberOfFrames);

/// @fn InterleaveAndGetPeaks(float *left, float *right, float *output, unsigned int numberOfFrames, float *peaks);
/// @brief Makes an interleaved output from two input channels and measures the volume: output = [L, R, L, R, ...]
/// @param left Pointer to floating point numbers. Mono input for left channel.
/// @param right Pointer to floating point numbers. Mono input for right channel.
/// @param output Pointer to floating point numbers. Stereo interleaved output.
/// @param numberOfFrames The number of frames to process.
/// @param peaks Pointer to two floating point numbers. Peak value result (left, right).
JSWASM void InterleaveAndGetPeaks(float *left, float *right, float *output, unsigned int numberOfFrames, float *peaks);

/// @fn DeInterleave(float *input, float *left, float *right, unsigned int numberOfFrames);
/// @brief Deinterleaves an interleaved stereo input to two mono output channels: left = [L, L, L, L, ...], right = [R, R, R, R, ...]
/// @param input Pointer to floating point numbers. Stereo interleaved input.
/// @param left Pointer to floating point numbers. Mono output for left channel.
/// @param right Pointer to floating point numbers. Mono output for right channel.
/// @param numberOfFrames The number of frames to process.
JSWASM void DeInterleave(float *input, float *left, float *right, unsigned int numberOfFrames);

/// @fn DeInterleaveMultiply(float *input, float *left, float *right, unsigned int numberOfFrames, float multiplier);
/// @brief Deinterleaves an interleaved stereo input to two mono output channels and multiplies the output (gain): left = [L, L, L, L, ...] * gain, right = [R, R, R, R, ...] * gain
 /// @param input Pointer to floating point numbers. Stereo interleaved input.
 /// @param left Pointer to floating point numbers. Mono output for left channel.
 /// @param right Pointer to floating point numbers. Mono output for right channel.
 /// @param numberOfFrames The number of frames to process.
 /// @param multiplier Multiply each output sample with this value.
JSWASM void DeInterleaveMultiply(float *input, float *left, float *right, unsigned int numberOfFrames, float multiplier);

/// @fn DeInterleaveAdd(float *input, float *left, float *right, unsigned int numberOfFrames);
/// @brief Deinterleaves an interleaved stereo input and adds the results to the two mono output channels: left = left + [L, L, L, L, ...], right = right + [R, R, R, R, ...]
/// @param input Pointer to floating point numbers. Stereo interleaved input.
/// @param left Pointer to floating point numbers. Mono output for left channel.
/// @param right Pointer to floating point numbers. Mono output for right channel.
/// @param numberOfFrames The number of frames to process.
JSWASM void DeInterleaveAdd(float *input, float *left, float *right, unsigned int numberOfFrames);

/// @fn DeInterleaveMultiplyAdd(float *input, float *left, float *right, unsigned int numberOfFrames, float multiplier);
/// @brief Deinterleaves an interleaved stereo input to two mono output channels, multiplies the result (gain) and and adds the results to the two mono output channels: left = left + [L, L, L, L, ...] * gain, right = right + [R, R, R, R, ...] * gain
 /// @param input Pointer to floating point numbers. Stereo interleaved input.
 /// @param left Pointer to floating point numbers. Mono output for left channel.
 /// @param right Pointer to floating point numbers. Mono output for right channel.
 /// @param numberOfFrames The number of frames to process.
 /// @param multiplier Multiply each output sample with this value.
JSWASM void DeInterleaveMultiplyAdd(float *input, float *left, float *right, unsigned int numberOfFrames, float multiplier);

/// @fn HasNonFinite(float *input, unsigned int numberOfValues);
/// @brief Checks if the audio samples have non-valid values, such as infinity or NaN (not a number).
/// @param input Pointer to floating point numbers to check.
/// @param numberOfValues Number of values in the buffer. Please note, this is NOT numberOfFrames. You need to provide the number of floating point numbers in the buffer.
JSWASM bool HasNonFinite(float *input, unsigned int numberOfValues);

/// @fn StereoToMono(float *input, float *output, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfFrames);
/// @brief Makes mono output from stereo interleaved input: output = [L + R], [L + R], [L + R], ...
/// @param input Pointer to floating point numbers. Stereo interleaved input.
/// @param output Pointer to floating point numbers. Mono output.
/// @param leftGainStart Gain of the first sample on the left channel.
/// @param leftGainEnd Gain for the last sample on the left channel. Gain will be smoothly calculated between start end end.
/// @param rightGainStart Gain of the first sample on the right channel.
/// @param rightGainEnd Gain for the last sample on the right channel. Gain will be smoothly calculated between start end end.
/// @param numberOfFrames The number of frames to process.
JSWASM void StereoToMono(float *input, float *output, float leftGainStart, float leftGainEnd, float rightGainStart, float rightGainEnd, unsigned int numberOfFrames);

/// @fn CrossMono(float *inputA, float *inputB, float *output, float inputAGainStart, float inputAGainEnd, float inputBGainStart, float inputBGainEnd, unsigned int numberOfFrames);
/// @brief Crossfades two mono input channels into a mono output: output = inputA * gain + inputB + gain
/// @param inputA Pointer to floating point numbers. First mono input.
/// @param inputB Pointer to floating point numbers. Second mono input.
/// @param output Pointer to floating point numbers. Mono output. Can be equal with one of the inputs (in-place processing).
/// @param inputAGainStart Gain of the first sample on the first input.
/// @param inputAGainEnd Gain for the last sample on the first input. Gain will be smoothly calculated between start end end.
/// @param inputBGainStart Gain of the first sample on the second input.
/// @param inputBGainEnd Gain for the last sample on the second input. Gain will be smoothly calculated between start end end.
/// @param numberOfFrames The number of frames to process.
JSWASM void CrossMono(float *inputA, float *inputB, float *output, float inputAGainStart, float inputAGainEnd, float inputBGainStart, float inputBGainEnd, unsigned int numberOfFrames);

/// @fn CrossStereo(float *inputA, float *inputB, float *output, float inputAGainStart, float inputAGainEnd, float inputBGainStart, float inputBGainEnd, unsigned int numberOfFrames);
/// @brief Crossfades two stereo inputs into a stereo output: output = inputA * gain + inputB + gain
/// @param inputA Pointer to floating point numbers. Interleaved stereo input (first).
/// @param inputB Pointer to floating point numbers. Interleaved stereo input (second).
/// @param output Pointer to floating point numbers. Interleaved stereo output. Can be equal with one of the inputs (in-place processing).
/// @param inputAGainStart Gain of the first sample on the first input.
/// @param inputAGainEnd Gain for the last sample on the first input. Gain will be smoothly calculated between start end end.
/// @param inputBGainStart Gain of the first sample on the second input.
/// @param inputBGainEnd Gain for the last sample on the second input. Gain will be smoothly calculated between start end end.
/// @param numberOfFrames The number of frames to process.
JSWASM void CrossStereo(float *inputA, float *inputB, float *output, float inputAGainStart, float inputAGainEnd, float inputBGainStart, float inputBGainEnd, unsigned int numberOfFrames);

/// @fn Add1(float *input, float *output, unsigned int numberOfItems)
/// @brief Adds the values in input to the values in output: output[n] += input[n]
/// @param input Pointer to floating point numbers. Input data.
/// @param output Pointer to floating point numbers. Output data.
/// @param numberOfItems The length of input.
JSWASM void Add1(float *input, float *output, unsigned int numberOfItems);

/// @fn Add2(float *inputA, float *inputB, float *output, unsigned int numberOfItems)
/// @brief Adds the values in two inputs to the values in output: output[n] += inputA[n] + inputB[n]
/// @param inputA Pointer to floating point numbers. Input data.
/// @param inputB Pointer to floating point numbers. Input data.
/// @param output Pointer to floating point numbers. Output data.
/// @param numberOfItems The length of input.
JSWASM void Add2(float *inputA, float *inputB, float *output, unsigned int numberOfItems);

/// @fn Add4(float *inputA, float *inputB, float *inputC, float *inputD, float *output, unsigned int numberOfItems)
/// @brief Adds the values in four inputs to the values in output: output[n] += inputA[n] + inputB[n] + inputC[n] + inputD[n]
/// @param inputA Pointer to floating point numbers. Input data.
/// @param inputB Pointer to floating point numbers. Input data.
/// @param inputC Pointer to floating point numbers. Input data.
/// @param inputD Pointer to floating point numbers. Input data.
/// @param output Pointer to floating point numbers. Output data.
/// @param numberOfItems The length of input.
JSWASM void Add4(float *inputA, float *inputB, float *inputC, float *inputD, float *output, unsigned int numberOfItems);

/// @fn StereoToMidSide(float *input, float *output, unsigned int numberOfFrames)
/// @brief Converts a stereo signal to mid-side.
/// @param input Pointer to floating point numbers. Interleaved stereo input.
/// @param output Pointer to floating point numbers. Mid-side interleaved output. Can be equal to input (in-place processing).
/// @param numberOfFrames The number of frames to process.
JSWASM void StereoToMidSide(float *input, float *output, unsigned int numberOfFrames);

/// @fn MidSideToStereo(float *input, float *output, unsigned int numberOfFrames)
/// @brief Converts a mid-side signal to stereo.
/// @param input Pointer to floating point numbers. Mid-side interleaved input.
/// @param output Pointer to floating point numbers. Interleaved stereo output. Can be equal to input (in-place processing).
/// @param numberOfFrames The number of frames to process.
JSWASM void MidSideToStereo(float *input, float *output, unsigned int numberOfFrames);

/// @fn DotProduct(float *inputA, float *inputB, unsigned int numValues)
/// @brief Calculates the dot product of two vectors.
/// @param inputA Pointer to floating point numbers. First input vector.
/// @param inputB Pointer to floating point numbers. Second input vector.
/// @param numValues Number of value pairs to process.
/// @return The dot product.
JSWASM float DotProduct(float *inputA, float *inputB, unsigned int numValues);

/// @fn float frequencyOfNote(int note);
/// @return Returns the frequency of a specific note.
/// @param note The index of the note. Note 0 is the standard A note at 440 Hz.
JSWASM float frequencyOfNote(int note);

/// @fn FILE *createWAV(const char *path, unsigned int samplerate, unsigned char numChannels);
/// @brief Creates a 16-bit WAV file.
/// After createWAV, write audio data using the writeWAV() function or fwrite(). Close the file with the closeWAV() function.
/// Never use direct disk writing in a real-time audio processing thread, use the Superpowered Recorder class in that case.
/// @return A file handle (success) or NULL (error).
/// @param path The full filesystem path of the file.
/// @param samplerate Sample rate of the file in Hz.
/// @param numChannels The number of channels.
FILE *createWAV(const char *path, unsigned int samplerate, unsigned char numChannels);

/// @fn FILE *createWAVfd(int fd, unsigned int samplerate, unsigned char numChannels);
/// @brief Creates a 16-bit WAV file.
/// After createWAVfd, write audio data using the writeWAV() function or fwrite(). Close the file with the closeWAV() function.
/// Never use direct disk writing in a real-time audio processing thread, use the Superpowered Recorder class in that case.
/// @return A file handle (success) or NULL (error).
/// @param fd Existing file descriptor. Superpowered will fdopen on this using "w" mode.
/// @param samplerate Sample rate of the file in Hz.
/// @param numChannels The number of channels.
FILE *createWAVfd(int fd, unsigned int samplerate, unsigned char numChannels);

/// @fn bool writeWAV(FILE *fd, short int *audio, unsigned int numberOfBytes);
/// @brief Writes audio into a WAV file.
/// @return Returns true for success and false for error.
/// @param fd The file handle to write into.
/// @param audio Pointer to signed short integer numbers. Audio to write.
/// @param numberOfBytes The number of bytes to write.
bool writeWAV(FILE *fd, short int *audio, unsigned int numberOfBytes);

/// @fn void closeWAV(FILE *fd);
/// @brief Closes a 16-bit stereo WAV file.
/// fclose() is not enough to create a valid a WAV file, use this function to close it.
/// @param fd The file handle to close.
void closeWAV(FILE *fd);

/// @fn Version()
/// @return Returns the current version of the Superpowered SDK.
/// The returned value is: major version * 10000 + minor version * 100 + revision
/// Example: 10402 means 1.4.2
JSWASM unsigned int Version();

}
>>>>>>> master

#endif
