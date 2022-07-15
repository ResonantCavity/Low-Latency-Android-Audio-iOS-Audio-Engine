#ifndef Header_SuperpoweredFilter
#define Header_SuperpoweredFilter

#include "SuperpoweredFX.h"
struct filterInternals;

<<<<<<< HEAD
typedef enum SuperpoweredFilterType {
    SuperpoweredFilter_Resonant_Lowpass = 0,
    SuperpoweredFilter_Resonant_Highpass = 1,
    SuperpoweredFilter_Bandlimited_Bandpass = 2,
    SuperpoweredFilter_Bandlimited_Notch = 3,
    SuperpoweredFilter_LowShelf = 4,
    SuperpoweredFilter_HighShelf = 5,
    SuperpoweredFilter_Parametric = 6,
    SuperpoweredFilter_CustomCoefficients = 7
} SuperpoweredFilterType;

/**
 @brief SuperpoweredFilter is an IIR filter based on the typical direct form 1 formula:
 
 y[n] = (b0/a0)*x[n] + (b1/a0)*x[n-1] + (b2/a0)*x[n-2] - (a1/a0)*y[n-1] - (a2/a0)*y[n-2]
 
 It doesn't allocate any internal buffers and needs just a few bytes of memory.
 
 @param frequency Current frequency value. Read only.
 @param decibel Current decibel value for shelving and parametric filters. Read only.
 @param resonance Current resonance value for resonant filters. Read only.
 @param octave Current octave value for bandlimited and parametric filters. Read only.
 @param slope Current slope value for shelving filters. Read only.
 @param type Filter type. Read only.
 */
class SuperpoweredFilter: public SuperpoweredFX {
public:
// READ ONLY parameters
    float frequency;
    float decibel;
    float resonance;
    float octave;
    float slope;
    SuperpoweredFilterType type;
    
/**
 @brief Change parameters for resonant filters.

 @param frequency The frequency in Hz.
 @param resonance Resonance value. Resonance = Q / 10.
 */
    void setResonantParameters(float frequency, float resonance);
/**
 @brief Change parameters for shelving filters.

 @param frequency The frequency in Hz.
 @param slope Slope.
 @param dbGain Gain in decibel.
 */
    void setShelfParameters(float frequency, float slope, float dbGain);
/**
 @brief Change parameters for bandlimited filters.

 @param frequency The center frequency in Hz.
 @param octaveWidth Width in octave.
 */
    void setBandlimitedParameters(float frequency, float octaveWidth);
/**
 @brief Change parameters for parametric filters.

 @param frequency The center frequency in Hz.
 @param octaveWidth Width in octave.
 @param dbGain Gain in decibel.
 */
    void setParametricParameters(float frequency, float octaveWidth, float dbGain);
    
/**
 @brief Set params and type at once for resonant filters.
 
 @param frequency The frequency in Hz.
 @param resonance Resonance value.
 @param type Must be lowpass or highpass.
 */
    void setResonantParametersAndType(float frequency, float resonance, SuperpoweredFilterType type);
/**
 @brief Set params and type at once for shelving filters.
 
 @param frequency The frequency in Hz.
 @param slope Slope.
 @param dbGain Gain in decibel.
 @param type Must be low shelf or high shelf.
 */
    void setShelfParametersAndType(float frequency, float slope, float dbGain, SuperpoweredFilterType type);
    
/**
 @brief Set params and type at once for bandlimited filters.
 
 @param frequency The center frequency in Hz.
 @param octaveWidth Width in octave. (Min 0.1, max 5.)
 @param type Must be bandpass or notch.
 */
    void setBandlimitedParametersAndType(float frequency, float octaveWidth, SuperpoweredFilterType type);

/**
 @brief Set custom coefficients for the filter.
 
 Coefficient changes will be smoothly handled.
 
 @param coefficients Pointer to the 5 coefficients of the first direct form IIR filter in this order: b0, b1, b2, a0, a1
 */
    void setCustomCoefficients(float *coefficients);
    
/**
 @brief Turns the effect on/off.
 */
    void enable(bool flag); // Use this to turn it on/off.
    
/**
 @brief Create an filter instance with the current sample rate value and filter type.
 
 Enabled is false by default, use enable(true) to enable.
 */
    SuperpoweredFilter(SuperpoweredFilterType filterType, unsigned int samplerate);
    ~SuperpoweredFilter();
    
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
 @brief Processes interleaved audio.
 
 @return Put something into output or not.
 
 @param input 32-bit interleaved stereo input buffer. Can point to the same location with output (in-place processing).
 @param output 32-bit interleaved stereo output buffer. Can point to the same location with input (in-place processing).
 @param numberOfSamples Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
*/
    bool process(float *input, float *output, unsigned int numberOfSamples);

/**
 @brief Processes mono audio.

 @return Put something into output or not.

 @param input 32-bit input buffer. Can point to the same location with output (in-place processing).
 @param output 32-bit output buffer. Can point to the same location with input (in-place processing).
 @param numberOfSamples Number of frames to process. Recommendations for best performance: multiply of 8, minimum 64.
*/
    bool processMono(float *input, float *output, unsigned int numberOfSamples);
=======
/// @brief Filter is an IIR filter based on the typical direct form 1 formula:
/// y[n] = (b0/a0)*x[n] + (b1/a0)*x[n-1] + (b2/a0)*x[n-2] - (a1/a0)*y[n-1] - (a2/a0)*y[n-2]
/// It doesn't allocate any internal buffers and needs just a few bytes of memory.
class Filter: public FX {
public:
    /// @brief Superpowered filter types and their effective parameters:
    typedef enum FilterType {
        Resonant_Lowpass = 0,     ///< frequency, resonance
        Resonant_Highpass = 1,    ///< frequency, resonance
        Bandlimited_Bandpass = 2, ///< frequency, octave
        Bandlimited_Notch = 3,    ///< frequency, octave
        LowShelf = 4,             ///< frequency, slope, decibel
        HighShelf = 5,            ///< frequency, slope, decibel
        Parametric = 6,           ///< frequency, octave, decibel
        CustomCoefficients = 7
    } FilterType;
    
    float frequency; ///< Frequency in Hz. From 1 Hz to the half of the current sample rate.
    float decibel;   ///< Decibel gain value for shelving and parametric filters. Limit: -96 to 24.
    float resonance; ///< Resonance value for resonant filters. Resonance = Q / 10. Limit: 0.01 to 1.
    float octave;    ///< Width in octave for bandlimited and parametric filters. Limit: 0.05 to 5.
    float slope;     ///< Slope value for shelving filters. Limit: 0.001 (most gradual slope) to 1 (steepest slope).
    FilterType type; ///< Filter type. Changing the filter type often involves changing other parameters as well. Therefore in a real-time context change the parameters and the type in the same thread with the process() call.

/// @brief For advanced use. Set custom coefficients for the filter. Changes will be smoothly handled to prevent audio artifacts. Do not call this concurrently with process().
/// @param b0 b0/a0
/// @param b1 b1/a0
/// @param b2 b2/a0
/// @param a1 a1/a0
/// @param a2 a2/a0
    JSWASM void setCustomCoefficients(float b0, float b1, float b2, float a1, float a2);
    
/// @brief Constructor. Enabled is false by default.
/// @param type The initial filter type.
/// @param samplerate The initial sample rate in Hz.
    JSWASM Filter(FilterType type, unsigned int samplerate);
    JSWASM ~Filter();
        
/// @brief Processes interleaved stereo audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process(). Do not call any method concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
    JSWASM bool process(float *input, float *output, unsigned int numberOfFrames);

/// @brief Processes mono audio. Always call it in the audio processing callback, regardless if the effect is enabled or not for smooth, audio-artifact free operation.
/// It's never blocking for real-time usage. You can change all properties on any thread, concurrently with process(). Do not call any method concurrently with process().
/// @return If process() returns with true, the contents of output are replaced with the audio output. If process() returns with false, the contents of output are not changed.
/// @param input Pointer to floating point numbers. 32-bit mono input.
/// @param output Pointer to floating point numbers. 32-bit mono output. Can point to the same location with input (in-place processing).
/// @param numberOfFrames Number of frames to process. Recommendations for best performance: multiply of 4, minimum 64.
    JSWASM bool processMono(float *input, float *output, unsigned int numberOfFrames);
>>>>>>> master

protected:
    filterInternals *internals;
    SuperpoweredFilter(const SuperpoweredFilter&);
    SuperpoweredFilter& operator=(const SuperpoweredFilter&);
};

#endif
