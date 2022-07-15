#ifndef Header_SuperpoweredTimeStretching
#define Header_SuperpoweredTimeStretching

#ifndef JSWASM
#define JSWASM
#endif

#include "SuperpoweredAudioBuffers.h"
struct stretchInternals;

/**
 @brief Time stretching and pitch shifting.
 
 One instance allocates around 220 kb. Check the SuperpoweredOfflineProcessingExample project on how to use.
 
 @param rate 1.0f means no time stretching. Read only.
 @param pitchShift Pitch shift notes, from -12 (one octave down) to 12 (one octave up). 0 means no pitch shift. Read only.
 @param pitchShiftCents Pitch shift cents, from -2400 (two octaves down) to 2400 (two octaves up). 0 means no pitch shift. Read only.
 @param numberOfInputSamplesNeeded How many samples required to some output. Read only.
*/
class SuperpoweredTimeStretching {
public:
<<<<<<< HEAD
    float rate;
    int pitchShift;
    int pitchShiftCents;
    int numberOfInputSamplesNeeded;
    
/**
 @brief Set rate and pitch shift. This method executes very quickly, in a few CPU cycles.
 
 @param newRate Limited to >= 0.01f and <= 4.0f. Values above 2.0f or below 0.5f are not recommended on mobile devices with low latency audio.
 @param newShift Limited to >= -12 and <= 12.
 */
    bool setRateAndPitchShift(float newRate, int newShift);

/**
 @brief Set rate and pitch shift with greater precision. Calling this method requires magnitudes more CPU than setRateAndPitchShift.

 @param newRate Limited to >= 0.01f and <= 4.0f. Values above 2.0f or below 0.5f are not recommended on mobile devices with low latency audio.
 @param newShiftCents Limited to >= -2400 and <= 2400.
*/
    bool setRateAndPitchShiftCents(float newRate, int newShiftCents);
    
/**
 @brief Create a time-stretching with the current sample rate and minimum rate value.
 
 @param samplerate The current sample rate.
 @param minimumRate The minimum tempo. Example: if you know you don't need tempo below 0.5f, setting minimum tempo to 0.5f will save computing power and memory.
 @param sound Experimental feature to be used with drastically low rates. Valid values are: 0 (default), 1, 2.
 */
    SuperpoweredTimeStretching(unsigned int samplerate, float minimumRate = 0.0f, unsigned char sound = 0);
    ~SuperpoweredTimeStretching();

/**
 @brief This class handles one stereo audio channel pair by default. You can extend it to handle more.

 @param numStereoPairs The number of stereo audio channel pairs. Maximum value: 8.
*/
    void setStereoPairs(unsigned int numStereoPairs);
/**
 @brief Sets the input and output sample rate.
 
 @param samplerate 44100, 48000, etc.
 */
    void setSampleRate(unsigned int samplerate);
/**
 @brief Reset all internals, sets the instance as good as new.
 */
    void reset();
/**
 @brief Removes samples from the input buffer (good for looping for example).
 
 @param samples The number of samples to remove.
 */
    void removeSamplesFromInputBuffersEnd(unsigned int samples);

/**
 @brief Processes the audio.
 
 @param input The input buffer.
 @param outputList The output buffer list.
 
 @see @c SuperpoweredAudiopointerList
 */
    void process(SuperpoweredAudiobufferlistElement *input, SuperpoweredAudiopointerList *outputList);
    
=======
    float rate;          ///< Time stretching rate (tempo). 1 means no time stretching. Maximum: 4. Values above 2 or below 0.5 are not recommended on mobile devices with low latency audio due high CPU load and risk of audio dropouts.
    int pitchShiftCents; ///< Pitch shift cents, limited from -2400 (two octaves down) to 2400 (two octaves up). Examples: 0 (no pitch shift), -100 (one note down), 300 (3 notes up).
                         ///< When the value if a multiply of 100 and is >= -1200 and <= 1200, changing the pitch shift needs only a few CPU clock cycles. Any change in pitchShiftCents involves significant momentary CPU load otherwise.
    unsigned int samplerate; ///< Sample rate in Hz. High quality pitch shifting requires 44100 Hz or more, the sound is "echoing" on lower sample rates.
    unsigned char sound; ///< Valid values are: 0 (best to save CPU with slightly lower audio quality), 1 (best for DJ apps, modern and "complete" music), 2 (best for instrumental loops and single instruments). Default: 1.
    float formantCorrection; ///< Amount of formant correction, between 0 (none) and 1 (full). Default: 0.
    bool preciseTurningOn;  ///< Maintain precise timing when the time-stretcher turns on. Useful for all use-cases except when the audio is heavily manipulated with some resampler (scratching). Default: true.
    Superpowered::AudiopointerList *outputList; ///< The AudiopointerList storing the audio output. To be used with the advancedProcess() method. Read only.

/// @brief Constructor.
/// @param samplerate The initial sample rate in Hz.
/// @param minimumRate The minimum value of rate. For example: if the rate will never go below 0.5, minimumRate = 0.5 will save significant computing power and memory. Minimum value of this: 0.01.
    JSWASM TimeStretching(unsigned int samplerate, float minimumRate = 0.01f);
    JSWASM ~TimeStretching();

/// @return Returns with how many frames of input should be provided to the time stretcher to produce some output.
/// It's never blocking for real-time usage. Use it in the same thread with the other real-time methods of this class.
/// The result can be 0 if rate is 1 and pitch shift is 0, because in that case the time stretcher is fully "transparent" and any number of input frames will produce some output.
    JSWASM unsigned int getNumberOfInputFramesNeeded();

/// @return Returns with how many frames of output is available.
/// It's never blocking for real-time usage. Use it in the same thread with the other real-time methods of this class.
    JSWASM unsigned int getOutputLengthFrames();

/// @brief Audio input.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param numberOfFrames Number of frames in input.
    JSWASM void addInput(float *input, int numberOfFrames);

/// @brief Gets the audio output into a buffer.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process(). Use it in the same thread with the other real-time methods of this class.
/// @return True if it has enough output frames stored and output is successfully written, false otherwise.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param numberOfFrames Number of frames to return with.
    JSWASM bool getOutput(float *output, int numberOfFrames);

/// @brief Reset all internals, sets the instance as good as new.
/// Don't call this concurrently with process() and in a real-time thread.
    JSWASM void reset();

/// @brief This class can handle one stereo audio channel pair by default (left+right). Maybe you need more if you load some music with 4 channels, then less if you load a regular stereo track.
/// Don't call this concurrently with process() and in a real-time thread.
/// @param numStereoPairs The number of stereo audio channel pairs. Valid values: one (stereo) to four (8 channels).
/// @param dontFree If true, this function will not free up any memory if numStereoPairs was bigger before, so no reallocation happens if numStereoPairs needs to be increased later.
    JSWASM void setStereoPairs(unsigned int numStereoPairs, bool dontFree = false);

/// @brief Removes audio from the end of the input buffer. Can be useful for some looping use-cases for example.
/// It's never blocking for real-time usage. Use it in the same thread with the other real-time methods of this class.
/// @param numberOfFrames The number of frames to remove.
    JSWASM void removeFramesFromInputBuffersEnd(unsigned int numberOfFrames);

/// @brief Processes audio. For advanced uses to:
/// 1. Save memory bandwidth (uses no memory copy) for maximum performance.
/// 2. Support up to 8 audio channels.
/// 3. Provide sub-sample precise positioning.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process(). Use it in the same thread with the other real-time methods of this class.
/// Do not use this method with addInput() or getOutput().
/// @param input The input buffer. It will take ownership on the input.
    void advancedProcess(AudiopointerlistElement *input);

>>>>>>> master
private:
    stretchInternals *internals;
    SuperpoweredTimeStretching(const SuperpoweredTimeStretching&);
    SuperpoweredTimeStretching& operator=(const SuperpoweredTimeStretching&);
};

#endif
