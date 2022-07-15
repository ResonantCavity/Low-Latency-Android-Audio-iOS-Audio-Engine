#ifndef Header_SuperpoweredFrequencyDomain
#define Header_SuperpoweredFrequencyDomain

#ifndef JSWASM
#define JSWASM
#endif

#include "SuperpoweredAudioBuffers.h"
struct frequencyDomainInternals;

<<<<<<< HEAD
/**
 @brief Transforms between time-domain and frequency-domain audio, including buffering, windowing (HanningZ) and window overlap handling (default: 4:1).

 One instance allocates around 131 kb. How to use:
 
 - feed audio input using addInput()
 - then iterate on timeDomainToFrequencyDomain() until it returns false
 - if timeDomainToFrequencyDomain() returns true, you have frequency domain data you can work with, use advance() in this case
 - frequencyDomainToTimeDomain() creates time domain audio samples from frequency domain data
 
 @param fftSize FFT size.
 @param numberOfInputSamplesNeeded How many samples required to some frequency domain output. Read only.
 @param inputList For advanced uses: access to the internal audio input pointer list.
*/
class SuperpoweredFrequencyDomain {
public:
    int fftSize;
    int numberOfInputSamplesNeeded;
    SuperpoweredAudiopointerList *inputList;

/**
 @brief Creates an instance.
 
 @param fftLogSize FFT log size, between 8 and 13 (FFT 256 - 8192). The default value (11) provides a good compromise in precision (~22 Hz per bin), CPU load and time-domain event sensitivity.
 @param maxOverlap Maximum overlap:1 (default: 4:1).
*/
    SuperpoweredFrequencyDomain(int fftLogSize = 11, int maxOverlap = 4);
    ~SuperpoweredFrequencyDomain();

/**
 @brief This class handles one stereo audio channel pair by default. You can extend it to handle more.

 @param numStereoPairs The number of stereo audio channel pairs.
*/
    void setStereoPairs(unsigned int numStereoPairs);

/**
 @brief Add some audio input. Use it only if you created the instance with pool = 0.
 
 @param input 32-bit floating point stereo input.
 @param numberOfSamples The number of input samples.
 */
    void addInput(float *input, int numberOfSamples);
/**
 @brief Add some audio input (advanced use). Use it only if you created the instance with an existing buffer pool.

 @param input The input buffer.
*/
    void addInput(SuperpoweredAudiobufferlistElement *input);

/**
 @brief Converts the audio inputs to frequency domain.
 
 Each frequency bin is (samplerate / fftSize / 2) wide.
 
 @return True, if a conversion was possible (enough samples were available).

 @param magnitudeL Magnitudes for each frequency bin, left side. Must be at least fftSize big.
 @param magnitudeR Magnitudes for each frequency bin, right side.  Must be at least fftSize big.
 @param phaseL Phases for each frequency bin, left side.  Must be at least fftSize big.
 @param phaseR Phases for each frequency bin, right side.  Must be at least fftSize big.
 @param valueOfPi Pi can be translated to any value (Google: the tau manifesto). Leave it at 0 for M_PI.
 @param complexMode Instead of polar transform, returns complex values (magnitude: real, phase: imag).
 @param stereoPairIndex The index of the stereo pair to process.
*/
    bool timeDomainToFrequencyDomain(float *magnitudeL, float *magnitudeR, float *phaseL, float *phaseR, float valueOfPi = 0, bool complexMode = false, int stereoPairIndex = 0);

/**
 @brief Converts the mono audio input to frequency domain.

 Each frequency bin is (samplerate / fftSize / 2) wide.

 @return True, if a conversion was possible (enough samples were available).

 @param magnitude Magnitudes for each frequency bin. Must be at least fftSize big.
 @param phase Phases for each frequency bin.  Must be at least fftSize big.
 @param valueOfPi Pi can be translated to any value (Google: the tau manifesto). Leave it at 0 for M_PI.
 @param complexMode Instead of polar transform, returns complex values (magnitude: real, phase: imag).
*/
    bool timeDomainToFrequencyDomain(float *magnitude, float *phase, float valueOfPi = 0, bool complexMode = false);

/*
 @brief Advances the input buffer (removes the earliest samples).
 
 @param numberOfSamples For advanced use, if you know how window overlapping works. 0 (the default value) means 4:1 overlap (good compromise in audio quality).
*/
    void advance(int numberOfSamples = 0);

/**
 @brief Converts frequency domain data to audio output.
 
 @param magnitudeL Magnitudes for each frequency bin, left side. Must be at least fftSize big.
 @param magnitudeR Magnitudes for each frequency bin, right side.  Must be at least fftSize big.
 @param phaseL Phases for each frequency bin, left side.  Must be at least fftSize big.
 @param phaseR Phases for each frequency bin, right side.  Must be at least fftSize big.
 @param output Output goes here.
 @param valueOfPi Pi can be translated to any value (Google: the tau manifesto). Leave it at 0 for M_PI.
 @param incrementSamples For advanced use, if you know how window overlapping works. 0 (the default value) means 4:1 overlap (good compromise in audio quality).
 @param complexMode Instead of polar transform, returns complex values (magnitude: real, phase: imag).
 @param stereoPairIndex The index of the stereo pair to process.
*/
    void frequencyDomainToTimeDomain(float *magnitudeL, float *magnitudeR, float *phaseL, float *phaseR, float *output, float valueOfPi = 0, int incrementSamples = 0, bool complexMode = false, int stereoPairIndex = 0);

/**
 @brief Reset all internals, sets the instance as good as new.
*/
    void reset();
=======
/// @brief Transforms between time-domain and frequency-domain audio, including buffering, windowing (HanningZ) and window overlap handling (default: 4:1).
/// One instance allocates around 131 kb memory. How to use:
/// 1. Audio input using addInput().
/// 2. Call timeDomainToFrequencyDomain(), if it returns false go back to 1.
/// 3. The output of timeDomainToFrequencyDomain is frequency domain data you can work with.
/// 4. Call advance() (if required).
/// 5. Call frequencyDomainToTimeDomain() to create time domain audio from frequency domain data.
class FrequencyDomain {
public:
    Superpowered::AudiopointerList *inputList; ///< For advanced uses: access to the internal audio input pointer list.

/// @brief Constructor.
/// @param fftLogSize FFT log size, between 8 and 13 (FFT 256 - 8192). The default value (11) provides a good compromise in precision (~22 Hz per bin), CPU load and time-domain event sensitivity.
/// @param maxOverlap [Maximum overlap]:1 (default: 4:1).
    JSWASM FrequencyDomain(unsigned int fftLogSize = 11, unsigned int maxOverlap = 4);
    JSWASM ~FrequencyDomain();

/// @return Returns with how many frames of input should be provided to produce some output.
    JSWASM unsigned int getNumberOfInputFramesNeeded();

/// @brief This class can handle one stereo audio channel pair by default (left+right). You can extend it to handle more.
/// @param numStereoPairs The number of stereo audio channel pairs. Valid values: one (stereo) to four (8 channels).
/// @param dontFree If true, this function will not free up any memory if numStereoPairs is less than before, so no reallocation happens if numStereoPairs needs to be increased later.
    JSWASM void setStereoPairs(unsigned int numStereoPairs, bool dontFree = false);

/// @brief Add some audio input.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param numberOfFrames The number of input frames.
    JSWASM void addInput(float *input, int numberOfFrames);

/// @brief Converts the audio input (added by addInput()) to the frequency domain.
/// Each frequency bin is (samplerate / [FFT SIZE] / 2) wide.
/// @return True, if a conversion was possible (enough frames were available).
/// @param magnitudeL Pointer to floating point numbers. Magnitudes for each frequency bin, left side. Must be at least [FFT SIZE] big.
/// @param magnitudeR Pointer to floating point numbers. Magnitudes for each frequency bin, right side.  Must be at least [FFT SIZE] big.
/// @param phaseL Pointer to floating point numbers. Phases for each frequency bin, left side.  Must be at least [FFT SIZE] big.
/// @param phaseR Pointer to floating point numbers. Phases for each frequency bin, right side.  Must be at least [FFT SIZE] big.
/// @param valueOfPi Pi can be translated to any value (Google: the tau manifesto). Keep it at 0 for M_PI.
/// @param complexMode If true, then it returns with complex numbers (magnitude: real, phase: imag). Performs polar transform otherwise (the output is magnitudes and phases).
/// @param stereoPairIndex The index of the stereo pair to process.
    JSWASM bool timeDomainToFrequencyDomain(float *magnitudeL, float *magnitudeR, float *phaseL, float *phaseR, float valueOfPi = 0, bool complexMode = false, int stereoPairIndex = 0);

/// @brief Converts mono audio input (added by addInput()) to the frequency domain.
/// Each frequency bin is (samplerate / [FFT SIZE] / 2) wide.
/// @return True, if a conversion was possible (enough frames were available).
/// @param magnitude Pointer to floating point numbers. Magnitudes for each frequency bin. Must be at least [FFT SIZE] big.
/// @param phase Pointer to floating point numbers. Phases for each frequency bin.  Must be at least [FFT SIZE] big.
/// @param valueOfPi Pi can be translated to any value (Google: the tau manifesto). Keep it at 0 for M_PI.
/// @param complexMode If true, then it returns with complex numbers (magnitude: real, phase: imag). Performs polar transform otherwise (the output is magnitudes and phases).
    JSWASM bool timeDomainToFrequencyDomainMono(float *magnitude, float *phase, float valueOfPi = 0, bool complexMode = false);

/// @brief Advances the input buffer (removes the earliest frames).
/// @param numberOfFrames For advanced use, if you know how window overlapping works. Use 0 (the default value) otherwise for a 4:1 overlap (good compromise in audio quality).
    JSWASM void advance(int numberOfFrames = 0);

/// @brief Converts frequency domain data to audio output.
/// @param magnitudeL Pointer to floating point numbers. Magnitudes for each frequency bin, left side. Must be at least [FFT SIZE] big.
/// @param magnitudeR Pointer to floating point numbers. Magnitudes for each frequency bin, right side. Must be at least [FFT SIZE] big.
/// @param phaseL Pointer to floating point numbers. Phases for each frequency bin, left side. Must be at least [FFT SIZE] big.
/// @param phaseR Pointer to floating point numbers. Phases for each frequency bin, right side. Must be at least [FFT SIZE] big.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output.
/// @param valueOfPi Pi can be translated to any value (Google: the tau manifesto). Leave it at 0 for M_PI.
/// @param incrementFrames For advanced use, if you know how window overlapping works. Use 0 (the default value) otherwise for a 4:1 overlap (good compromise in audio quality).
/// @param complexMode If true, then the magnitude and phase inputs represent complex numbers (magnitude: real, phase: imag).
/// @param stereoPairIndex The index of the stereo pair to process.
    JSWASM void frequencyDomainToTimeDomain(float *magnitudeL, float *magnitudeR, float *phaseL, float *phaseR, float *output, float valueOfPi = 0, int incrementFrames = 0, bool complexMode = false, int stereoPairIndex = 0);

/// @brief Reset all internals, sets the instance as good as new.
    JSWASM void reset();

/// @brief Add some audio input (advanced use).
/// @param input The input buffer.
    void addAudiopointerlistElement(AudiopointerlistElement *input);
>>>>>>> master

private:
    frequencyDomainInternals *internals;
    SuperpoweredFrequencyDomain(const SuperpoweredFrequencyDomain&);
    SuperpoweredFrequencyDomain& operator=(const SuperpoweredFrequencyDomain&);
};

#endif
