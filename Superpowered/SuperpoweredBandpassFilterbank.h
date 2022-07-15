#ifndef Header_SuperpoweredBandpassFilterBank
#define Header_SuperpoweredBandpassFilterBank

<<<<<<< HEAD
=======
#ifndef JSWASM
#define JSWASM
#endif

namespace Superpowered {

>>>>>>> master
struct bandpassFilterbankInternals;

/**
 @brief Efficient bandpass filter bank for real-time, zero latency frequency analysation.
*/
class SuperpoweredBandpassFilterbank {
public:
<<<<<<< HEAD

/**
 Create a filterbank instance.
 
 @param numBands The number of bands. Must be a multiply of 8.
 @param frequencies The center frequencies of the bands.
 @param widths The width of the bands. 1.0f is one octave, 1.0f / 12.0f is one halfnote.
 @param samplerate The initial sample rate.
 */
    SuperpoweredBandpassFilterbank(int numBands, float *frequencies, float *widths, unsigned int samplerate);
/**
 Create a filterbank instance for advanced "grouped" usage. 
 The filterbank can be set up with multiple settings (frequency/width groups), then process can be performed with the selected setting (group).

 @param numGroups the number of groups.
 @param numBandsInGroup The number of bands. Must be a multiply of 8.
 @param frequencies The center frequencies of the bands. Example: if you have numGroups = 2 and numBandsInGroup = 8, then you should provide 2 * 8 = 16 frequencies.
 @param widths The width of the bands. 1.0f is one octave, 1.0f / 12.0f is one halfnote. Example: if you have numGroups = 2 and numBandsInGroup = 8, then you should provide 2 * 8 = 16 widths.
 @param samplerate The initial sample rate.
*/
    SuperpoweredBandpassFilterbank(int numGroups, int numBandsInGroup, float *frequencies, float *widths, unsigned int samplerate);
    ~SuperpoweredBandpassFilterbank();

/**
 @brief Sets the sample rate.

 @param samplerate 44100, 48000, etc.
*/
    void setSamplerate(unsigned int samplerate);

/**
 @brief Processes the audio.

 @param input 32-bit interleaved stereo input buffer.
 @param bands Frequency band results (magnitudes) will be ADDED to these. For example: bands[0] += result[0] If you divide each with the number of samples, the result will be between 0.0f and 1.0f.
 @param peak Maximum absolute peak value. Will compare against the input value of peak too. For example: peak = max(peak, fabsf(all samples))
 @param sum The cumulated absolute value will be ADDED to this. For example: sum += (sum of all fabsf(samples))
 @param numberOfSamples The number of samples to process.
 @param group The group index for advanced "grouped" usage.
*/
    void process(float *input, float *bands, float *peak, float *sum, unsigned int numberOfSamples, int group = 0);
/**
 @brief Processes the audio.

 @param input 32-bit interleaved stereo input buffer.
 @param bands Frequency band results. If you divide each with the number of samples, the result will be between 0.0f and 1.0f.
 @param peak Maximum absolute peak value. Will compare against the input value of peak too. For example: peak = max(peak, fabsf(all samples))
 @param sum The cumulated absolute value will be ADDED to this. For example: sum += (sum of all fabsf(samples))
 @param numberOfSamples The number of samples to process.
 @param group The group index for advanced "grouped" usage.
 */
    void processNoAdd(float *input, float *bands, float *peak, float *sum, unsigned int numberOfSamples, int group = 0);

=======
    unsigned int samplerate; ///< Sample rate in Hz.

    /// @brief Constructor.
    /// @param numBands The number of bands. Must be a multiply of 8.
    /// @param frequencies Center frequencies of each band in Hz.
    /// @param widths Widths of each band in octave (1.0f is one octave, 1.0f / 12.0f is one halfnote).
    /// @param samplerate The initial sample rate in Hz.
    /// @param numGroups For advanced use.
    /// The filter bank can be set up with multiple frequency + width groups, then process() or processNoAdd() can be performed with one specific frequency + width group. For example, set up one group with wide frequency coverage for the 20-20000 Hz range and three additional groups for 20-200 Hz, 200-2000 Hz and 2000-20000 Hz. When processing with the wide group of 20-20000 Hz and the highest magnitude can be found at 1000 Hz, use the 200-2000 Hz group for the next process() or processNoAdd() call, so the filter bank will have a "focus" on a narrower range.
    /// If numGroups > 0, then the number of frequencies and widths should be numGroups * numBands. Example: for numBands = 8 and numGroups = 2, provide 8 + 8 frequencies and 8 + 8 widths.
    JSWASM BandpassFilterbank(unsigned int numBands, float *frequencies, float *widths, unsigned int samplerate, unsigned int numGroups = 0);

    JSWASM ~BandpassFilterbank();

    /// @brief Processes the audio.
    /// It will ADD to the current magnitude in bands (like bands[0] += 0.123), so you can "measure" the magnitude of each frequency for a longer period of time.
    /// To calculate a result between 0 and 1 for multiple consecutive process() calls, divide each value in bands with the total number of frames passed to the consecutive process() calls.
    /// @param input 32-bit interleaved stereo input buffer.
    /// @param numberOfFrames Number of frames to process.
    /// @param group The group index for advanced "grouped" usage.
    JSWASM void process(float *input, unsigned int numberOfFrames, int group = 0);

    /// @brief Processes the audio. It will replace the contents of bands.
    /// @param input 32-bit interleaved stereo input buffer.
    /// @param numberOfFrames Number of frames to process.
    /// @param group The group index for advanced "grouped" usage.
    JSWASM void processNoAdd(float *input, unsigned int numberOfFrames, int group = 0);

    /// @return Pointer to floating point numbers representing the magnitude of each frequency band. Updated after each process() or processNoAdd() call.
    JSWASM float *getBands();

    /// @brief Sets all values of bands to 0.
    JSWASM void resetBands();

    /// @brief Returns with the average volume of all audio passed to all previous process() or processNoAdd() calls.
    JSWASM float getAverageVolume();

    /// @brief Returns with the cumulated absolute value of all audio passed to all previous process() or processNoAdd() calls. Like you would add the absolute value of all audio samples together.
    JSWASM float getSumVolume();

    /// @brief Resets the sum and average volume value to start measurement anew.
    JSWASM void resetSumAndAverageVolume();

    /// @brief Returns with the peak volume of all audio passed to all previous process() or processNoAdd() calls.
    JSWASM float getPeakVolume();

    /// @brief Resets the peak volume value to start measurement anew.
    JSWASM void resetPeakVolume();

>>>>>>> master
private:
    bandpassFilterbankInternals *internals;
    SuperpoweredBandpassFilterbank(const SuperpoweredBandpassFilterbank&);
    SuperpoweredBandpassFilterbank& operator=(const SuperpoweredBandpassFilterbank&);
};

#endif
