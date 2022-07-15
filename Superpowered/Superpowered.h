#ifndef Header_Superpowered
#define Header_Superpowered

<<<<<<< HEAD
=======
#ifndef JSWASM
#define JSWASM
#endif

/// @file Superpowered.h
/// @brief Initializes the Superpowered SDKs.

namespace Superpowered {

/// @fn Initialize(const char *licenseKey);
/// @brief Initializes the Superpowered SDKs. Use this only once, when your app or library initializes.
/// Do not use this if Superpowered is loaded dynamically and might be loaded multiple times (a DLL in a VST host for example). @see DynamicInitialize
/// @param licenseKey Visit https://superpowered.com/dev to register license keys.
JSWASM void Initialize(const char *licenseKey);

/// @fn DynamicInitialize(const char *licenseKey);
/// @brief Use this if Superpowered is loaded in a dynamically loaded library (such as a DLL on Windows). It allows for multiple loads (DLL in a VST host example). Enables all features.
/// @param licenseKey Visit https://superpowered.com/dev to register license keys.
void DynamicInitialize(const char *licenseKey);

/// @fn DynamicDestroy();
/// @brief Use this if Superpowered is used in a dynamically loaded library (such as a DLL on Windows), when the dynamically loaded library instance unloads (even if multiple loads may happen).
/// This function will block waiting for all Superpowered background threads to exit when the last instance of the library is unloaded.
/// Please note that you still need to "properly" release all Superpowered objects _before_ this call, such as delete all players, effects, etc.
void DynamicDestroy();

}

>>>>>>> master
/**
 @file Superpowered.h
 @brief Initializes the Superpowered SDKs.
 */

/**
 @fn SuperpoweredInitialize(
        const char *licenseKey,
        bool enableAudioAnalysis,
        bool enableFFTAndFrequencyDomain,
        bool enableAudioTimeStretching,
        bool enableAudioEffects,
        bool enableAudioPlayerAndDecoder,
        bool enableCryptographics,
        bool enableNetworking
    );
 
 @brief Initializes the Superpowered SDKs.
 
 @param licenseKey Visit https://superpowered.com/dev to register license keys.
 @param enableAudioAnalysis Enables SuperpoweredAnalyzer, SuperpoweredLiveAnalyzer, SuperpoweredWaveform and SuperpoweredBandpassFilterbank.
 @param enableFFTAndFrequencyDomain Enables SuperpoweredFrequencyDomain, SuperpoweredFFTComplex, SuperpoweredFFTReal and SuperpoweredPolarFFT.
 @param enableAudioTimeStretching Enables SuperpoweredTimeStretching.
 @param enableAudioEffects Enables all effects and every class based on the SuperpoweredFX class.
 @param enableAudioPlayerAndDecoder Enables SuperpoweredAdvancedAudioPlayer and SuperpoweredDecoder.
 @param enableCryptographics Enables Superpowered::RSAPublicKey, Superpowered::RSAPrivateKey, Superpowered::hasher and Superpowered::AES.
 @param enableNetworking Enables Superpowered::httpRequest.
 */

void SuperpoweredInitialize(const char *licenseKey,
                            bool enableAudioAnalysis,
                            bool enableFFTAndFrequencyDomain,
                            bool enableAudioTimeStretching,
                            bool enableAudioEffects,
                            bool enableAudioPlayerAndDecoder,
                            bool enableCryptographics,
                            bool enableNetworking);

#endif
