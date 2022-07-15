#ifndef Header_SuperpoweredClipper
#define Header_SuperpoweredClipper

<<<<<<< HEAD
=======
#ifndef JSWASM
#define JSWASM
#endif

namespace Superpowered {

>>>>>>> master
struct clipperInternals;

/**
 @brief Hard knee clipping with 0 latency.
 
 It doesn't allocate any internal buffers and needs just a few bytes of memory.
 
 @param thresholdDb Audio below this will be unchanged, above this will be attenuated. Limited between -100.0f and 0.0f.
 @param maximumDb Audio will reach 1.0f at this point. Limited between -48.0f and 48.0f.
*/
class SuperpoweredClipper {
public:
<<<<<<< HEAD
    float thresholdDb;
    float maximumDb;

    SuperpoweredClipper();
    ~SuperpoweredClipper();

/**
 @brief Processes the audio.

 @param input 32-bit interleaved stereo input buffer. Can point to the same location with output (in-place processing).
 @param output 32-bit interleaved stereo output buffer. Can point to the same location with input (in-place processing).
 @param numberOfSamples Should be 4 minimum and exactly divisible with 4.
*/
    void process(float *input, float *output, unsigned int numberOfSamples);
=======
    float thresholdDb; ///< Audio below this will be unchanged, above this will be attenuated. Limited between -100 and 0. Default: 0.
    float maximumDb;   ///< Audio will reach 1.0f at this point. Limited between -48 and 48. Default: 6.

/// @brief Constructor;
    JSWASM Clipper();
    JSWASM ~Clipper();

/// @brief Processes the audio.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process().
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Should be 4 minimum and exactly divisible with 4.
    JSWASM void process(float *input, float *output, unsigned int numberOfFrames);
>>>>>>> master

private:
    clipperInternals *internals;
};

#endif
