#ifndef Header_SuperpoweredAdvancedAudioPlayer
#define Header_SuperpoweredAdvancedAudioPlayer

#include "SuperpoweredHTTP.h"

struct SuperpoweredAdvancedAudioPlayerInternals;
struct SuperpoweredAdvancedAudioPlayerBase;

<<<<<<< HEAD
/**
 @brief The compressor settings of the STEMS format.
 */
typedef struct stemsCompressor {
    bool enabled;
    float inputGainDb;
    float outputGainDb;
    float dryWetPercent;
    float ratio;
    float attackSec;
    float releaseSec;
    float thresholdDb;
    float hpCutoffHz;
} stemsCompressor;
=======
class AdvancedAudioPlayer;
struct PlayerInternals;
>>>>>>> master

/**
 @brief The limiter settings of the STEMS format.
 */
typedef struct stemsLimiter {
    bool enabled;
    float releaseSec;
    float thresholdDb;
    float ceilingDb;
} stemsLimiter;

<<<<<<< HEAD
/**
 @brief Complete information about a STEMS file.
 */
typedef struct stemsInfo {
    char *names[4];
    char *colors[4];
    stemsCompressor compressor;
    stemsLimiter limiter;
} stemsInfo;

typedef enum SuperpoweredAdvancedAudioPlayerSyncMode {
    SuperpoweredAdvancedAudioPlayerSyncMode_None,
    SuperpoweredAdvancedAudioPlayerSyncMode_Tempo,
    SuperpoweredAdvancedAudioPlayerSyncMode_TempoAndBeat
} SuperpoweredAdvancedAudioPlayerSyncMode;

typedef enum SuperpoweredAdvancedAudioPlayerJogMode {
    SuperpoweredAdvancedAudioPlayerJogMode_Scratch,
    SuperpoweredAdvancedAudioPlayerJogMode_PitchBend,
    SuperpoweredAdvancedAudioPlayerJogMode_Parameter
} SuperpoweredAdvancedAudioPlayerJogMode;

typedef enum SuperpoweredAdvancedAudioPlayerEvent {
    SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess,
    SuperpoweredAdvancedAudioPlayerEvent_LoadError,
    SuperpoweredAdvancedAudioPlayerEvent_HLSNetworkError,
    SuperpoweredAdvancedAudioPlayerEvent_ProgressiveDownloadError,
    SuperpoweredAdvancedAudioPlayerEvent_EOF,
    SuperpoweredAdvancedAudioPlayerEvent_JogParameter,
    SuperpoweredAdvancedAudioPlayerEvent_DurationChanged,
    SuperpoweredAdvancedAudioPlayerEvent_LoopEnd,
    SuperpoweredAdvancedAudioPlayerEvent_LoopStartReverse
} SuperpoweredAdvancedAudioPlayerEvent;

/**
 @brief Represents the properties of a HLS stream alternative.
 */
typedef struct hlsStreamAlternative {
    char *uri, *name, *language, *groupid;
    int bps;
    bool isDefault, isMp4a;
} hlsStreamAlternative;

#define HLS_DOWNLOAD_EVERYTHING 86401
#define HLS_DOWNLOAD_REMAINING 86400

/**
 @brief Events happen asynchronously, implement this callback to get notified.
 
 LoadSuccess, LoadError, HLSNetworkError and ProgressiveDownloadError are called from an internal thread of this object.
 
 EOF (end of file), LoopEnd, LoopStartReverse and ScratchControl are called from the (probably real-time) audio processing thread while actually producing/processing samples, therefore: don't do any expensive or blocking, and don't expect the player's properties updated yet (such as position).
 
 @param clientData Some custom pointer you set when you created the SuperpoweredAdvancedAudioPlayer instance.
 @param event What happened (load success, load error, end of file, jog parameter).
 @param value A pointer to a stemsInfo structure or NULL for LoadSuccess (you take ownership over the strings). (const char *) for LoadError, pointing to the error message. (double *) for JogParameter in the range of 0.0 to 1.0. (bool *) for EOF, set it to true to pause playback. (bool *) for LoopEnd and LoopStartReverse, set it to false to exit the loop. Don't call this instance's methods from an EOF event callback!
 */
typedef void (* SuperpoweredAdvancedAudioPlayerCallback) (void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void *value);

/**
 The maximum playback or scratch speed.
 */
#define SUPERPOWEREDADVANCEDAUDIOPLAYER_MAXSPEED 20.0f


/**
 @brief High performance advanced audio player with:
 
 - time-stretching and pitch shifting,
 
 - beat and tempo sync,
 
 - scratching,
 
 - tempo bend,
 
 - looping,
 
 - slip mode,
 
 - fast seeking (cached points),
 
 - momentum and jog wheel handling,
 
 - 0 latency, real-time operation,
 
 - low memory usage,
 
 - thread safety (all methods are thread-safe),
 
 - direct iPod music library access.
 
 Can not be used for offline processing. Supported file types:
 - Stereo or mono pcm WAV and AIFF (16-bit int, 24-bit int, 32-bit int or 32-bit IEEE float).
 - MP3: MPEG-1 Layer III (sample rates: 32000 Hz, 44100 Hz, 48000 Hz). MPEG-2 is not supported.
 - AAC-LC in M4A container (iTunes).
 - AAC-LC in ADTS container (.aac).
 - Apple Lossless (on iOS only).
 - Http Live Streaming (HLS): vod/live/event streams, AAC-LC/MP3 in audio files or MPEG-TS files. Support for byte ranges and AES-128 encryption.

 @param positionMs The current position. Always accurate, no matter of time-stretching and other transformations. Read only.
 @param positionPercent The current position as a percentage (0.0f to 1.0f). Read only.
 @param positionSeconds The current position as seconds elapsed. Read only.
 @param displayPositionMs Same as positionMs, but positionMs is not updated until seeking to a different position is finished. This is updated immediately after setPosition() or seek() is called.  Read only.
 @param durationMs The duration of the current track in milliseconds. Equals to UINT_MAX for live streams. Read only.
 @param durationSeconds The duration of the current track in seconds. Equals to UINT_MAX for live streams. Read only.
 @param waitingForBuffering Indicates if the player waits for audio data to be bufferred. Read only.
 @param playing Indicates if the player is playing or paused. Read only.
 @param waitingForSyncMs The player is waiting silently for this amount of time from now. Default: 0 (not waiting).
 @param willSyncMs The player is playing and waiting for this amount of time from now to sync. Default: 0 (not waiting).
 @param audioStartMs The length of the silence at the beginning of the file.
 @param tempo The current tempo. Read only.
 @param masterTempo Time-stretching is enabled or not. Read only.
 @param pitchShift Note offset from -12 to 12. 0 means no pitch shift. Read only.
 @param pitchShiftCents Pitch shift cents, from -1200 (one octave down) to 1200 (one octave up). 0 means no pitch shift. Read only.
 @param bpm Must be correct for syncing. There is no auto-bpm detection inside. Read only.
 @param currentBpm The actual bpm of the track (as bpm changes with the current tempo). Read only.
 @param slip If enabled, scratching or reverse will maintain the playback position as if you had never entered those modes. Read only.
 @param scratching The player is in scratching mode or not. Read only.
 @param reverse Indicates if the playback goes backwards. Read only.
 @param looping Indicates if looping is enabled. Read only.
 @param firstBeatMs Tells where the first beat (the beatgrid) begins. Must be correct for syncing. Read only.
 @param msElapsedSinceLastBeat How many milliseconds elapsed since the last beat. Read only.
 @param phase Reserved for future use.
 @param quantum Reserved for future use.
 @param bendMsOffset Reserved for future use.
 @param beatIndex Which beat has just happened (1 [1.0f-1.999f], 2 [2.0f-2.999f], 3 [3.0f-3.99f], 4 [4.0f-4.99f]). A value of 0 means "don't know". Read only.
 @param bufferStartPercent What is buffered from the original source, start point. Will always be 0 for non-network sources (files). Read only.
 @param bufferEndPercent What is buffered from the original source, end point. Will always be 1.0f for non-network sources (files). Read only.
 @param currentBps For HLS only. Updated after each segment download to indicate the actual network throughput (for best stream selection).
 @param loadStatusCode @see @c Superpowered::httpResponse
 @param syncMode The current sync mode (off, tempo, or tempo and beat).
 @param fixDoubleOrHalfBPM If tempo is >1.4f or <0.6f, it will treat the bpm as half or double. Good for certain genres. False by default.
 @param dynamicHLSAlternativeSwitching Dynamicly changing the current HLS alternative to match the available network bandwidth. Default is true.
 @param reverseToForwardAtLoopStart If looping and playback direction is reverse, reaching the beginning of the loop will change direction to forward. False by default.
 @param getAudioStartMs If enabled, the player will try to detect the length of the silence at the beginning of the file during open() (up to 10 seconds), and set the audioStartSampleMs property accordingly.
 @param downloadSecondsAhead The HLS content download strategy: how many seconds ahead of the playback position to download. Default is HLS_DOWNLOAD_REMAINING, meaning it will download everything after the playback position, until the end. HLS_DOWNLOAD_EVERYTHING downloads before the playback position too.
 @param maxDownloadAttempts If HLS download fails, how many times to try until sleep. Default: 100. After sleep, NetworkError is called continously.
 @param minTimeStretchingTempo Will not time-stretch, just resample below this tempo. Default: 0.501f (recommended value for low CPU on older mobile devices, such as the first iPad). Set this before an open() call. 
 @param maxTimeStretchingTempo Will not time-stretch, just resample above this tempo. Default: 2.0f (recommended value for low CPU on older mobile devices, such as the first iPad).
 @param handleStems Output 4 distinct stereo pairs for Native Instruments STEMS format. Default: false (output stem 0 for STEMS).
 @param defaultQuantum Reserved for future use.
 @param hlsLiveLatencySeconds Number of seconds of latency for a HLS live stream. The player will try to stay at this value on every reconnect. Default: -1 (stream starts at the first segment specified by the server)
 @param fullyDownloadedFilePath The file system path of the fully downloaded audio file for progressive downloads. Progressive downloads are automatically removed if no SuperpoweredAdvancedAudioPlayer instance is active for the same url. This parameter provides an alternative to save the file.
 @param tempFolderPath The path for temporary files.
*/
class SuperpoweredAdvancedAudioPlayer {
public:
// READ ONLY parameters, don't set them directly, use the methods below.
    double positionMs;
    float positionPercent;
    int positionSeconds;
    double displayPositionMs;
    unsigned int durationMs;
    unsigned int durationSeconds;
    bool waitingForBuffering;
    bool playing;
    double waitingForSyncMs;
    double willSyncMs;
    double audioStartMs;

    double tempo;
    bool masterTempo;
    int pitchShift;
    int pitchShiftCents;
    double bpm;
    double currentBpm;
    
    bool slip;
    bool scratching;
    bool reverse;
    bool looping;
    
    double firstBeatMs;
    double msElapsedSinceLastBeat;
    double phase;
    double quantum;
    double bendMsOffset;
    float beatIndex;

    float bufferStartPercent;
    float bufferEndPercent;
    int currentBps;
    int loadStatusCode;

    char *fullyDownloadedFilePath;
    static char *tempFolderPath;

// READ-WRITE parameters
    SuperpoweredAdvancedAudioPlayerSyncMode syncMode;
    bool fixDoubleOrHalfBPM;
    bool dynamicHLSAlternativeSwitching;
    bool reverseToForwardAtLoopStart;
    bool getAudioStartMs;
    int downloadSecondsAhead;
    int maxDownloadAttempts;
    float minTimeStretchingTempo;
    float maxTimeStretchingTempo;
    bool handleStems;
    double defaultQuantum;
    char hlsLiveLatencySeconds;

/**
 @brief Set the folder path for temporary files. Used for HLS and progressive download only.
 
 Call this first before any player instance is created. It will create a subfolder with the name "SuperpoweredAAP" in this folder.
 
 @param path File system path of the folder.
 */
    static void setTempFolder(const char *path);

/**
 @brief Remove the temp folder. Use this when your program ends.
 */
    static void clearTempFolder();
    
/**
 @brief Create a player instance with the current sample rate value.
 
 Example: SuperpoweredAdvancedAudioPlayer player = new SuperpoweredAdvancedAudioPlayer(this, playerCallback, 44100, 4);
 
 @param clientData A custom pointer your callback receives.
 @param callback Your callback to receive player events.
 @param sampleRate The current sample rate.
 @param cachedPointCount Sets how many positions can be cached in the memory. Jumping to a cached point happens with 0 latency. Loops are automatically cached.
 @param internalBufferSizeSeconds The number of seconds to buffer internally for playback and cached points. Minimum 2, maximum 60. Default: 2.
 @param negativeSeconds The number of seconds of silence in the negative direction, before the beginning of the track.
*/
    SuperpoweredAdvancedAudioPlayer(void *clientData, SuperpoweredAdvancedAudioPlayerCallback callback, unsigned int sampleRate, unsigned char cachedPointCount, unsigned int internalBufferSizeSeconds = 2, unsigned int negativeSeconds = 0);
    ~SuperpoweredAdvancedAudioPlayer();
/**
 @brief Opens an audio file with playback paused.
 
 Tempo, pitchShift, masterTempo and syncMode are NOT changed if you open a new one. Do not call open() in the audio processing callback.
 
 @param path Full file system path or progressive download path (http or https).
 @param customHTTPRequest If custom HTTP communication is required (such as sending http headers for authorization), pass a fully prepared http request object. The player will copy this.
*/
    void open(const char *path, Superpowered::httpRequest *customHTTPRequest = 0);
=======
/// @brief High performance advanced audio player with:
/// - time-stretching and pitch shifting,
/// - beat and tempo sync,
/// - scratching,
/// - tempo bend,
/// - looping,
/// - slip mode,
/// - fast seeking (cached points),
/// - momentum and jog wheel handling,
/// - 0 latency, real-time operation,
/// - low memory usage,
/// - thread safety (all methods are thread-safe),
/// - direct iPod music library access.
/// Can be used in a real-time audio processing thread. Can not be used for offline processing.
/// Supported file types:
/// - Stereo or mono pcm WAV and AIFF (16-bit int, 24-bit int, 32-bit int or 32-bit IEEE float).
/// - MP3: MPEG-1 Layer III (sample rates: 32000 Hz, 44100 Hz, 48000 Hz). MPEG-2 Layer III is not supported (mp3 with sample rates below 32000 Hz).
/// - AAC or HE-AAC in M4A container (iTunes) or ADTS container (.aac).
/// - ALAC/Apple Lossless (on iOS only).
/// - Http Live Streaming (HLS): vod/live/event streams, AAC-LC/MP3 in audio files or MPEG-TS files. Support for byte ranges and AES-128 encryption.

class AdvancedAudioPlayer {
public:
    static const int HLSDownloadEverything;  ///< Will download everything after the playback position until the end.
    static const int HLSDownloadRemaining;   ///< Downloads everything from the beginning to the end, regardless the playback position.
    static const float MaxPlaybackRate;      ///< The maximum playback rate or scratching speed: 20.
    
    /// @brief Jog Wheel Mode, to be used with the jogT... methods.
    typedef enum JogMode {
        JogMode_Scratch = 0,   ///< Jog wheel controls scratching.
        JogMode_PitchBend = 1, ///< Jog wheel controls pitch bend.
        JogMode_Parameter = 2  ///< Jog wheel changes a parameter.
    } JogMode;
    
    /// @brief Player events.
    typedef enum PlayerEvent {
        PlayerEvent_None = 0,       ///< Open was not called yet.
        PlayerEvent_Opening = 1,    ///< Trying to open the content.
        PlayerEvent_OpenFailed = 2, ///< Failed to open the content.
        PlayerEvent_Opened = 10,    ///< Successfully opened the content, playback can start.
        PlayerEvent_ConnectionLost = 3, ///< Network connection lost to the HLS stream or progressive download. Can only be "recovered" by a new open(). May happen after PlayerEvent_Opened has been delivered.
        PlayerEvent_ProgressiveDownloadFinished = 11 ///< The content has finished downloading and is fully available locally. May happen after PlayerEvent_Opened has been delivered.
    } PlayerEvent;
    
    /// @brief Synchronization modes.
    typedef enum SyncMode {
        SyncMode_None = 0,        ///< No synchronization.
        SyncMode_Tempo = 1,       ///< Sync tempo only.
        SyncMode_TempoAndBeat = 2 ///< Sync tempo and beat.
    } SyncMode;
    
    unsigned int outputSamplerate;           ///< The player output sample rate in Hz.
    double playbackRate;                     ///< The playback rate. Must be positive and above 0.00001. Default: 1.
    bool timeStretching;                     ///< Enable/disable time-stretching. Default: true.
    float formantCorrection;                 ///< Amount of formant correction, between 0 (none) and 1 (full). Default: 0.
    double originalBPM;                      ///< The original bpm of the current music. There is no auto-bpm detection inside, this must be set to a correct value for syncing. Maximum 300. A value below 20 will be automatically set to 0. Default: 0 (no bpm value known).
    bool fixDoubleOrHalfBPM;                 ///< If true and playbackRate is above 1.4f or below 0.6f, it will sync the tempo as half or double. Default: false.
    double firstBeatMs;                      ///< The start position of the beatgrid in milliseconds. Must be set to a correct value for syncing. Default: 0.
    double defaultQuantum;                   ///< Sets the quantum for quantized synchronization. Example: 4 means 4 beats. Default: 1.
    SyncMode syncMode;                       ///< The current sync mode (off, tempo, or tempo+beat). Default: off.
    double syncToBpm;                        ///< A bpm value to sync with. Use 0 for no syncing. Default: 0.
    double syncToMsElapsedSinceLastBeat;     ///< The number of milliseconds elapsed since the last beat on audio the player has to sync with. Use -1.0 to ignore. Default: -1.
    double syncToPhase;                      ///< Used for quantized synchronization. The phase to sync with between 0 and 1. Use -1 to ignore. Default: -1.
    double syncToQuantum;                    ///< Used for quantized synchronization. The quantum to sync with. Use -1 to ignore. Default: -1.
    int pitchShiftCents;                     ///< Pitch shift cents, from -2400 (two octaves down) to 2400 (two octaves up). Low CPU load for multiples of 100 between -1200 and 1200. Default: 0 (no pitch shift).
    bool loopOnEOF;                          ///< If true, jumps back and continues playback. If false, playback stops. Default: false.
    bool reverseToForwardAtLoopStart;        ///< If this is true with playing backwards and looping, then reaching the beginning of the loop will change playback direction to forwards. Default: false.
    bool HLSAutomaticAlternativeSwitching;   ///< If true, then the player will automatically switch between the HLS alternatives according to the available network bandwidth. Default: true.
    char HLSLiveLatencySeconds;              ///< When connecting or reconnecting to a HLS live stream, the player will try to skip audio to maintain this latency. Default: -1 (the player will not skip audio and the live stream starts at the first segment specified by the server).
    int HLSMaximumDownloadAttempts;          ///< How many times to retry if a HLS segment download fails. Default: 100.
    int HLSBufferingSeconds;                 ///< How many seconds ahead of the playback position to download. Default value: HLSDownloadRemaining.
    unsigned char timeStretchingSound;       ///< The sound parameter of the internal TimeStretching instance. @see TimeStretching

/// @brief Set the folder to store for temporary files. Used for HLS and progressive download only.
/// Call this before any player instance is created.
/// It will create a subfolder with the name "SuperpoweredAAP" in the specified folder (and will clear all content inside SuperpoweredAAP if it exists already).
/// If you need to clear the folder before your app quits, use NULL for the path.
/// @param path File system path of the folder.
    static void setTempFolder(const char *path);
    
/// @return Returns with the temporary folder path.
    static const char *getTempFolderPath();
    
/// @return Returns with a human readable error string. If the code is not a decoder status code, then it's a SuperpoweredHTTP status code and returns with that.
/// @param code The return value of the open...() method.
    JSWASM static const char *statusCodeToString(int code);
    
/// @brief Creates a player instance.
/// @param samplerate The initial sample rate of the player output in hz.
/// @param cachedPointCount How many positions can be cached in the memory. Jumping to a cached point happens with zero latency. Loops are automatically cached.
/// @param internalBufferSizeSeconds The number of seconds to buffer internally for playback and cached points. Minimum 2, maximum 60. Default: 2.
/// @param negativeSeconds The number of seconds of silence in the negative direction, before the beginning of the track.
/// @param minimumTimestretchingPlaybackRate Will not time-stretch but resample below this playback rate. Default: 0.501f (the recommended value for low CPU load on older mobile devices, such as the first iPad). Will be applied after changing playbackRate or scratching. Default: 0.501f
/// @param maximumTimestretchingPlaybackRate Will not time-stretch but resample above this playback rate. Default: 2.0f (the recommended value for low CPU load on older mobile devices, such as the first iPad). Will be applied after changing playbackRate or scratching.
/// @param enableStems If true and a Native Instruments STEMS file is loaded, output 4 stereo channels. Default: false (stereo master mix output).
    JSWASM AdvancedAudioPlayer(unsigned int samplerate, unsigned char cachedPointCount, unsigned int internalBufferSizeSeconds = 2, unsigned int negativeSeconds = 0, float minimumTimestretchingPlaybackRate = 0.501f, float maximumTimestretchingPlaybackRate = 2.0f, bool enableStems = false);
    JSWASM ~AdvancedAudioPlayer();
    
/// @brief Opens an audio file with playback paused.
/// Playback rate, pitchShift, timeStretching and syncMode are NOT changed if you open a new file.
/// @warning This method has no effect if the previous open didn't finish or if called in the audio processing thread.
/// @param path Full file system path or progressive download path (http or https).
/// @param customHTTPRequest If custom HTTP communication is required (such as sending http headers for authorization), pass a fully prepared http request object. The player will copy this object.
/// @param skipSilenceAtBeginning If true, the player will set the position to skip the initial digital silence of the audio file (up to 10 seconds).
/// @param measureSilenceAtEnd If true, the player will check the length of the digital silence at the end of the audio file.
    void open(const char *path, Superpowered::httpRequest *customHTTPRequest = 0, bool skipSilenceAtBeginning = false, bool measureSilenceAtEnd = false);
    
/// @brief Opens an audio file with playback paused.
/// Playback rate, pitchShift, timeStretching and syncMode are NOT changed if you open a new file.
/// @warning This method has no effect if the previous open didn't finish or if called in the audio processing thread.
/// @param path Full file system path or progressive download path (http or https).
/// @param offset The byte offset inside the path.
/// @param length The byte length from the offset.
/// @param customHTTPRequest If custom HTTP communication is required (such as sending http headers for authorization), pass a fully prepared http request object. The player will copy this object.
/// @param skipSilenceAtBeginning If true, the player will set the position to skip the initial digital silence of the audio file (up to 10 seconds).
/// @param measureSilenceAtEnd If true, the player will check the length of the digital silence at the end of the audio file.
    void open(const char *path, int offset, int length, Superpowered::httpRequest *customHTTPRequest = 0, bool skipSilenceAtBeginning = false, bool measureSilenceAtEnd = false);
    
/// @brief Opens raw 16-bit sterteo PCM audio in memory, with playback paused.
/// Playback rate, pitchShift, timeStretching and syncMode are NOT changed if you open a new file.
/// @warning This method has no effect if the previous open didn't finish or if called in the audio processing thread.
/// @param pointer Pointer to 16-bit integer numbers, raw stereo interleaved pcm audio.
/// @param samplerate The sample rate in Hz. Valid from 8192 to 384000.
/// @param durationFrames The duration of the audio in frames.
/// @param skipSilenceAtBeginning If true, the player will set the position to skip the initial digital silence of the audio file (up to 10 seconds).
/// @param measureSilenceAtEnd If true, the player will check the length of the digital silence at the end of the audio file.
    JSWASM void openPCM16AudioInMemory(void *pointer, unsigned int samplerate, unsigned int durationFrames, bool skipSilenceAtBeginning = false, bool measureSilenceAtEnd = false);
    
/// @brief Opens a memory location in Superpowered AudioInMemory format, with playback paused. This feature supports progressive loading via AudioInMemory::append (and the AudioInMemory doesn't even need to hold any data when openMemory is called).
/// Playback rate, pitchShift, timeStretching and syncMode are NOT changed if you open a new file.
/// @warning This method has no effect if the previous open didn't finish or if called in the audio processing thread.
/// @param pointer Pointer to data in Superpowered AudioInMemory format, pointing to raw stereo interleaved pcm audio inside.
/// @param skipSilenceAtBeginning If true, the player will set the position to skip the initial digital silence of the audio file (up to 10 seconds).
/// @param measureSilenceAtEnd If true, the player will check the length of the digital silence at the end of the audio file.
    JSWASM void openMemory(void *pointer, bool skipSilenceAtBeginning = false, bool measureSilenceAtEnd = false);
>>>>>>> master
    
/**
 @brief Opens an audio file with playback paused.
 
 Tempo, pitchShift, masterTempo and syncMode are NOT changed if you open a new one. Do not call open() in the audio processing callback.
 
 @param path Full file system path or progressive download path (http or https).
 @param offset The byte offset inside the file.
 @param length The byte length from the offset.
 @param customHTTPRequest If custom HTTP communication is required (such as sending http headers for authorization), pass a fully prepared http request object. The player will copy this.
*/
    void open(const char *path, int offset, int length, Superpowered::httpRequest *customHTTPRequest = 0);
/**
 @brief Opens a HTTP Live Streaming stream with playback paused.
 
 Tempo, pitchShift, masterTempo and syncMode are NOT changed if you open a new one. Do not call openHLS() in the audio processing callback.
 
 @param url URL of the stream.
 @param customHTTPRequest If custom HTTP communication is required (such as sending http headers for authorization), pass a fully prepared http request object. The player will copy this.
 */
    void openHLS(const char *url, Superpowered::httpRequest *customHTTPRequest = 0);
<<<<<<< HEAD

/**
 @brief Starts playback.
 
 @param synchronised Set it to true for a beat-synced or tempo-synced start.
 */
    void play(bool synchronised);
    
/**
 @brief Pause playback. 
 
 There is no need for a "stop" method, this player is very efficient with the battery and has no significant "stand-by" processing.
 
 @param decelerateSeconds Optional momentum. 0 means pause immediately.
 @param slipMs Enable slip mode for a specific amount of time, or 0 to not slip.
 */
    void pause(float decelerateSeconds = 0, unsigned int slipMs = 0);
    
/**
 @brief Toggle play/pause.
 */
    void togglePlayback();
/**
 @brief Simple seeking to a percentage.
 */
    void seek(double percent);
/**
 @brief Precise seeking.
 
 @param ms Position in milliseconds.
 @param andStop If true, stops playback.
 @param synchronisedStart If andStop is false, a beat-synced start is possible.
 @param forceDefaultQuantum Reserved for future use.
 @param preferWaitingforSynchronisedStart Wait or start immediately when synchronized.
 */
    void setPosition(double ms, bool andStop, bool synchronisedStart, bool forceDefaultQuantum = false, bool preferWaitingforSynchronisedStart = false);
/**
 @brief Cache a position for zero latency seeking. It will cache around +/- 1 second around this point.
 
 @param ms Position in milliseconds.
 @param pointID Use this to provide a custom identifier, so you can overwrite the same point later. Use 255 for a point with no identifier.
*/
    void cachePosition(double ms, unsigned char pointID);
/**
 @brief Loop from a start point with some length.
 
 @param startMs Loop from this millisecond.
 @param lengthMs Length in millisecond.
 @param jumpToStartMs If the playhead is within the loop, jump to startMs or not.
 @param pointID Looping caches startMs, so you can specify a pointID too (or set to 255 if you don't care).
 @param synchronisedStart Beat-synced start.
 @param forceDefaultQuantum Reserved for future use.
 @param preferWaitingforSynchronisedStart Wait or start immediately when synchronized.
 */
    bool loop(double startMs, double lengthMs, bool jumpToStartMs, unsigned char pointID, bool synchronisedStart, bool forceDefaultQuantum = false, bool preferWaitingforSynchronisedStart = false);
/**
 @brief Loop from a start to an end point.
     
 @param startMs Loop from this millisecond.
 @param endMs Loop to this millisecond.
 @param jumpToStartMs If the playhead is within the loop, jump to startMs or not.
 @param pointID Looping caches startMs, so you can specify a pointID too (or set to 255 if you don't care).
 @param synchronisedStart Beat-synced start.
 @param forceDefaultQuantum Reserved for future use.
 @param preferWaitingforSynchronisedStart Wait or start immediately when synchronized.
*/
    bool loopBetween(double startMs, double endMs, bool jumpToStartMs, unsigned char pointID, bool synchronisedStart, bool forceDefaultQuantum = false, bool preferWaitingforSynchronisedStart = false);
/**
 @brief Exits from the current loop.
 
 @param synchronisedStart Synchronized start after the loop exit.
 */
    void exitLoop(bool synchronisedStart = false);
/**
 @brief Checks if ms fall into the current loop.
 
 @param ms The position to check in milliseconds.
 */
    bool msInLoop(double ms);
/**
 @brief There is no auto-bpm detection inside, you must set the original bpm of the track with this for syncing.
 
 Should be called after a successful open().
 
 @param newBpm The bpm value. A number below 10.0f means "bpm unknown", and sync will not work.
*/
    void setBpm(double newBpm);
/**
  @brief Beat-sync works only if the first beat's position is known. Set it here.
 
  Should be called after a successful open().
 */
    void setFirstBeatMs(double ms);
/**
 @brief Shows you where the closest beat is to a specific position.
 
 @param ms The position in milliseconds.
 @param beatIndex Pointer to a beat index value. Set to NULL if beat index is not important. Set to 0 if you want to retrieve the beat index of the position. Set to 1-4 if beat index is important.
*/
    double closestBeatMs(double ms, unsigned char *beatIndex);
    
/**
 @brief "Virtual jog wheel" or "virtual turntable" handling. 
 
 @param ticksPerTurn Sets the sensitivity of the virtual wheel. Use around 2300 for pixel-perfect touchscreen waveform control.
 @param mode Jog wheel mode (scratching, pitch bend, or parameter set in the range 0.0 to 1.0).
 @param scratchSlipMs Enable slip mode for a specific amount of time for scratching, or 0 to not slip.
*/
    void jogTouchBegin(int ticksPerTurn, SuperpoweredAdvancedAudioPlayerJogMode mode, unsigned int scratchSlipMs);
/**
 @brief A jog wheel should send some "ticks" according to the movement. A waveform's movement in pixels for example.
 
 @param value The cumulated ticks value.
 @param bendStretch Use time-stretching for bending or not (false makes it "audible").
 @param bendMaxPercent The maximum tempo change for pitch bend, should be between 0.01f and 0.3f (1% and 30%).
 @param bendHoldMs How long to maintain the bent state. A value >= 1000 will hold until endContinuousPitchBend is called.
 @param parameterMode True: if there was no jogTouchBegin, SuperpoweredAdvancedAudioPlayerJogMode_Parameter applies. False: if there was no jogTouchBegin, SuperpoweredAdvancedAudioPlayerJogMode_PitchBend applies.
*/
    void jogTick(int value, bool bendStretch, float bendMaxPercent, unsigned int bendHoldMs, bool parameterMode);
/**
 @brief Call this when the jog touch ends.
 
 @param decelerate The decelerating rate for momentum. Set to 0.0f for automatic.
 @param synchronisedStart Beat-synced start after decelerating.
 */
    void jogTouchEnd(float decelerate, bool synchronisedStart);
/**
 @brief Sets the relative tempo of the playback.
 
 @param tempo 1.0f is "original speed".
 @param masterTempo Enable or disable time-stretching.
 */
    void setTempo(double tempo, bool masterTempo);
/**
 @brief Sets the pitch shift value. Needs masterTempo enabled.
 
 @param pitchShift Note offset from -12 to 12. 0 means no pitch shift.
 */
    void setPitchShift(int pitchShift);
    
/**
 @brief Sets the pitch shift value with greater precision. Calling this method requires magnitudes more CPU than setPitchShift.
 
 @param pitchShiftCents Limited to >= -1200 and <= 1200. 0 means no pitch shift.
 */
    void setPitchShiftCents(int pitchShiftCents);

/**
 @brief Sets playback direction.
 
 @param reverse Playback direction.
 @param slipMs Enable slip mode for a specific amount of time, or 0 to not slip.
 */
    void setReverse(bool reverse, unsigned int slipMs);
/**
 @brief Pitch bend (temporary tempo change).
 
 @param maxPercent The maximum tempo change for pitch bend, should be between 0.01f and 0.3f (1% and 30%).
 @param bendStretch Use time-stretching for bending or not (false makes it "audible").
 @param faster Playback speed change direction.
 @param holdMs How long to maintain the bent state. A value >= 1000 will hold until endContinuousPitchBend is called.
*/
    void pitchBend(float maxPercent, bool bendStretch, bool faster, unsigned int holdMs);
/**
 @brief Ends pitch bend.
 */
    void endContinuousPitchBend();
/**
 @brief Reserved for future use.
 */
    void resetBendMsOffset();
/**
 @brief Call when scratching starts.
 
 @warning This is an advanced method, use it only if you don't want the jogT... methods.
 
 @param slipMs Enable slip mode for a specific amount of time for scratching, or 0 to not slip.
 @param stopImmediately Stop now or not.
 */
    void startScratch(unsigned int slipMs, bool stopImmediately);
/**
 @brief Scratch movement.
 
 @warning This is an advanced method, use it only if you don't want the jogT... methods.
 
 @param pitch The current speed.
 @param smoothing Should be between 0.05f (max. smoothing) and 1.0f (no smoothing).
 */
    void scratch(double pitch, float smoothing);
/**
 @brief Ends scratching.
 
 @warning This is an advanced method, use it only if you don't want the jogT... methods.
 
 @param returnToStateBeforeScratch Return to the previous playback state (direction, speed) or not.
 */
    void endScratch(bool returnToStateBeforeScratch);
/**
 @brief Returns the last process() numberOfSamples converted to milliseconds.
 */
    double lastProcessMs();
/**
 @brief Sets the sample rate.
     
 @param sampleRate 44100, 48000, etc.
*/
    void setSamplerate(unsigned int sampleRate);
/**
 @brief Call this on a phone call or other interruption.
 
 Apple's built-in codec may be used in some cases, for example ALAC files. 
 Call this after a media server reset or audio session interrupt to resume playback.
*/
    void onMediaserverInterrupt();
/**
 @brief Reserved for future use.

 @param phase Reserved for future use.
 @param quantum Reserved for future use.
 */
    double getMsDifference(double phase, double quantum);

/**
 @brief Processes the audio, stereo version.
 
 @return Put something into output or not.
 
 @param buffer 32-bit interleaved stereo input/output buffer. Should be numberOfSamples * 8 + 64 bytes big.
 @param bufferAdd If true, the contents of buffer will be preserved and audio will be added to them. If false, buffer is completely overwritten.
 @param numberOfSamples The number of samples to provide.
 @param volume 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
 @param masterBpm A bpm value to sync with. Use 0.0f for no syncing.
 @param masterMsElapsedSinceLastBeat How many milliseconds elapsed since the last beat on the other stuff we are syncing to. Use -1.0 to ignore.
 @param phase Reserved for future use.
 @param quantum Reserved for future use.
*/
    bool process(float *buffer, bool bufferAdd, unsigned int numberOfSamples, float volume = 1.0f, double masterBpm = 0.0f, double masterMsElapsedSinceLastBeat = -1.0, double phase = -1.0, double quantum = -1.0);

/**
 @brief Processes the audio, multi-channel version.

 @return Put something into output or not.

 @param buffers 32-bit interleaved stereo input/output buffer pairs. Each pair should be numberOfSamples * 8 + 64 bytes big.
 @param bufferAdds If true, the contents of buffer will be preserved and audio will be added to them. If false, buffer is completely overwritten.
 @param numberOfSamples The number of samples to provide.
 @param volumes 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
 @param masterBpm A bpm value to sync with. Use 0.0f for no syncing.
 @param masterMsElapsedSinceLastBeat How many milliseconds elapsed since the last beat on the other audio we are syncing to. Use -1.0 to ignore.
 @param phase Reserved for future use.
 @param quantum Reserved for future use.
 */
    bool processMulti(float **buffers, bool *bufferAdds, unsigned int numberOfSamples, float *volumes, double masterBpm = 0.0f, double masterMsElapsedSinceLastBeat = -1.0, double phase = -1.0, double quantum = -1.0);
    
private:
    SuperpoweredAdvancedAudioPlayerInternals *internals;
    SuperpoweredAdvancedAudioPlayerBase *base;
    SuperpoweredAdvancedAudioPlayer(const SuperpoweredAdvancedAudioPlayer&);
    SuperpoweredAdvancedAudioPlayer& operator=(const SuperpoweredAdvancedAudioPlayer&);
=======
    
/// @return Returns with the latest player event. This method should be used in a periodically running code, at one place only, because it returns a specific event just once per open() call. Best to be used in a UI loop.
    JSWASM PlayerEvent getLatestEvent();

/// @return If getLatestEvent returns with OpenFailed, retrieve the error code or HTTP status code here.
    JSWASM int getOpenErrorCode();
    
/// @return Returns with the full filesystem path of the locally cached file if the player is in the PlayerEvent_Opened_ProgressiveDownloadFinished state, NULL otherwise.
    const char *getFullyDownloadedFilePath();
    
/// @return Returns true if end-of-file has been reached recently (will never indicate end-of-file if loopOnEOF is true). This method should be used in a periodically running code at one place only, because it returns a specific end-of-file event just once. Best to be used in a UI loop.
    JSWASM bool eofRecently();
 
/// @return Indicates if the player is waiting for data (such as waiting for a network download).
    JSWASM bool isWaitingForBuffering();
    
/// @return Returns with the length of the digital silence at the beginning of the file if open...() was called with skipSilenceAtBeginning = true, 0 otherwise.
    JSWASM double getAudioStartMs();
    
/// @return Returns with the length of the digital silence at the end of the file if open...() was called with measureSilenceAtEnd = true, 0 otherwise.
    JSWASM double getAudioEndMs();
            
/// @return The current playhead position in milliseconds. Not changed by any pending setPosition() or seek() call, always accurate regardless of time-stretching and other transformations.
    JSWASM double getPositionMs();
    
/// @return The current position in milliseconds, immediately updated after setPosition() or seek(). Use this for UI display.
    JSWASM double getDisplayPositionMs();
    
/// @return Similar to getDisplayPositionMs(), but as a percentage (0 to 1).
    JSWASM float getDisplayPositionPercent();
    
/// @return Similar to getDisplayPositionMs(), but as seconds elapsed.
    JSWASM int getDisplayPositionSeconds();
    
/// @return The position in milliseconds where the player will continue playback after slip mode ends.
    JSWASM double afterSlipModeWillJumpBackToPositionMs();
    
/// @return The duration of the current track in milliseconds. Returns UINT_MAX for live streams.
    JSWASM unsigned int getDurationMs();
    
/// @return The duration of the current track in seconds. Returns UINT_MAX for live streams.
    JSWASM unsigned int getDurationSeconds();
    
/// @brief Starts playback immediately without any synchronization.
    JSWASM void play();
    
/// @brief Starts beat or tempo synchronized playback.
    JSWASM void playSynchronized();
    
/// @brief Starts playback at a specific position. isPlaying() will return false and the position will not be updated until this function succeeds starting playback at the specified position.
/// You can call this in a real-time thread (audio processing callback) with a continuously updated time for a precise on-the-fly launch.
/// @param positionMs Start position in milliseconds.
    JSWASM void playSynchronizedToPosition(double positionMs);
    
/// @brief Pause playback.
/// There is no need for a "stop" method, this player is very efficient with the battery and has no significant "stand-by" processing.
/// @param decelerateSeconds Optional momentum. 0 means to pause immediately.
/// @param slipMs Enable slip mode for a specific amount of time, or 0 to not slip.
    JSWASM void pause(float decelerateSeconds = 0, unsigned int slipMs = 0);
    
/// @brief Toggle play/pause (no synchronization).
    JSWASM void togglePlayback();
    
/// @return Indicates if the player is playing or paused.
    JSWASM bool isPlaying();
    
/// @brief Simple seeking to a percentage.
/// @param percent The position in percentage.
    JSWASM void seek(double percent);
    
/// @brief Precise seeking.
/// @param ms Position in milliseconds.
/// @param andStop If true, stops playback.
/// @param synchronisedStart If andStop is false, makes a beat-synced start possible.
/// @param forceDefaultQuantum If true and using quantized synchronization, will use the defaultQuantum instead of the syncToQuantum.
/// @param preferWaitingforSynchronisedStart Wait or start immediately when synchronized.
    JSWASM void setPosition(double ms, bool andStop, bool synchronisedStart, bool forceDefaultQuantum = false, bool preferWaitingforSynchronisedStart = false);
    
/// @brief Caches a position for zero latency seeking.
/// @param ms Position in milliseconds.
/// @param pointID Use this to provide a custom identifier, so you can overwrite the same point later. Use 255 for a point with no identifier.
    JSWASM void cachePosition(double ms, unsigned char pointID = 255);
            
/// @brief Outputs audio, stereo version.
/// @return True: buffer has audio output from the player. False: the contents of the buffers were not changed (typically happens when the player is paused).
/// @warning Duration may change to a more precise value after this, because some file formats have no precise duration information.
/// @param buffer Pointer to floating point numbers. 32-bit interleaved stereo input/output buffer. Should be numberOfFrames * 8 + 64 bytes big.
/// @param mix If true, the player output will be mixed with the contents of buffer. If false, the contents of buffer will be overwritten with the player output.
/// @param numberOfFrames The number of frames requested.
/// @param volume 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
    JSWASM bool processStereo(float *buffer, bool mix, unsigned int numberOfFrames, float volume = 1.0f);

/// @brief Outputs audio, 8 channels version.
/// @return True: buffers has audio output from the player. False: the contents of buffer were not changed (typically happens when the player is paused).
/// @warning Duration may change to a more precise value after this, because some file formats have no precise duration information.
/// @param buffer0 Pointer to floating point numbers. 32-bit interleaved stereo input/output buffer for the 1st stereo channels. Should be numberOfFrames * 8 + 64 bytes big.
/// @param buffer1 Pointer to floating point numbers. 32-bit interleaved stereo input/output buffer for the 2nd stereo channels. Should be numberOfFrames * 8 + 64 bytes big.
/// @param buffer2 Pointer to floating point numbers. 32-bit interleaved stereo input/output buffer for the 3rd stereo channels. Should be numberOfFrames * 8 + 64 bytes big.
/// @param buffer3 Pointer to floating point numbers. 32-bit interleaved stereo input/output buffer for the 4th stereo channels. Should be numberOfFrames * 8 + 64 bytes big.
/// @param mix If true, the player output will be added to the contents of buffers. If false, the contents of buffers will be overwritten with the player output.
/// @param numberOfFrames The number of frames requested.
/// @param volume0 Volume for buffer0. 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
/// @param volume1 Volume for buffer1. 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
/// @param volume2 Volume for buffer2. 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
/// @param volume3 Volume for buffer3. 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
    JSWASM bool process8Channels(float *buffer0, float *buffer1, float *buffer2, float *buffer3, bool mix, unsigned int numberOfFrames, float volume0, float volume1, float volume2, float volume3);
    
/// @return Returns true if a STEMS file was loaded (and the player was initialized with enableStems == true).
    JSWASM bool isStems();
    
/// @brief Performs the last stage of STEMS processing, the master compressor and limiter. Works only if a STEMS file was loaded.
/// @param input Pointer to floating point numbers. 32-bit interleaved stereo input buffer.
/// @param output Pointer to floating point numbers. 32-bit interleaved stereo output buffer.
/// @param numberOfFrames The number of frames to process.
/// @param volume Output volume. 0.0f is silence, 1.0f is "original volume". Changes are automatically smoothed between consecutive processes.
    JSWASM void processSTEMSMaster(float *input, float *output, unsigned int numberOfFrames, float volume = 1.0f);
    
/// @return Returns with a stem's name if a STEMS file was loaded, NULL otherwise.
/// @param index The index of the stem.
    JSWASM const char *getStemName(unsigned char index);
    
/// @return Returns with a stem's color if a STEMS file was loaded, NULL otherwise.
/// @param index The index of the stem.
    JSWASM const char *getStemColor(unsigned char index);
    
/// @brief Apple's built-in codec may be used in some cases, such as decoding ALAC files. Call this after a media server reset or audio session interrupt to resume playback.
    void onMediaserverInterrupt();
    
/// @return Returns with the beginning of the buffered part. Will always be 0 for non-network sources (such as local files).
    float getBufferedStartPercent();
    
/// @return Returns with the end of the buffered part. Will always be 1.0f for non-network sources (such as local files).
    float getBufferedEndPercent();
    
/// @return For HLS only. Returns with the actual network throughput (for best stream selection).
    unsigned int getCurrentHLSBPS();
    
/// @return The current bpm of the track (as changed by the playback rate).
    JSWASM double getCurrentBpm();
        
/// @return How many milliseconds elapsed since the last beat.
    JSWASM double getMsElapsedSinceLastBeat();
        
/// @return Which beat has just happened. Possible values:
/// 0        : unknown
/// 1 - 1.999: first beat
/// 2 - 2.999: second beat
/// 3 - 3.999: third beat
/// 4 - 4.999: fourth beat
    JSWASM float getBeatIndex();
        
/// @return Returns with the current phase for quantized synchronization, between 0 (beginning of the quantum) and 1 (end of the quantum).
    JSWASM double getPhase();
        
/// @return Returns with the current quantum for quantized synchronization, such as 2 for two beats, 4 for four beats, etc...
    JSWASM double getQuantum();
    
/// @return Returns with the distance (in milliseconds) to a specific quantum and phase for quantized synchronization.
/// @param phase The phase to calculate against.
/// @param quantum The quantum to calculate against.
    JSWASM double getMsDifference(double phase, double quantum);
    
/// @return If the player is waiting to a synchronization event (such as synchronized playback start or restarting a loop), the return value indicates the time remaining in milliseconds (continously updated). 0 means not waiting to such event.
    JSWASM double getMsRemainingToSyncEvent();
    
/// @brief Loop from a start point to some length.
/// @param startMs Loop from this milliseconds.
/// @param lengthMs Loop length in milliseconds.
/// @param jumpToStartMs If the playhead is within the loop, jump to startMs or not.
/// @param pointID Looping caches startMs, therefore you can specify a pointID too (or set to 255 if you don't care).
/// @param synchronisedStart Beat-synced start.
/// @param numLoops Number of times to loop. 0 means: until exitLoop() is called.
/// @param forceDefaultQuantum If true and using quantized synchronization, will use the defaultQuantum instead of the syncToQuantum.
/// @param preferWaitingforSynchronisedStart Wait or start immediately when synchronized.
    JSWASM void loop(double startMs, double lengthMs, bool jumpToStartMs, unsigned char pointID, bool synchronisedStart, unsigned int numLoops = 0, bool forceDefaultQuantum = false, bool preferWaitingforSynchronisedStart = false);

/// @brief Loop between a start and end points.
/// @param startMs Loop from this milliseconds.
/// @param endMs Loop to this milliseconds.
/// @param jumpToStartMs If the playhead is within the loop, jump to startMs or not.
/// @param pointID Looping caches startMs, therefore you can specify a pointID too (or set to 255 if you don't care).
/// @param synchronisedStart Beat-synced start.
/// @param numLoops Number of times to loop. 0 means: until exitLoop() is called.
/// @param forceDefaultQuantum If true and using quantized synchronization, will use the defaultQuantum instead of the syncToQuantum.
/// @param preferWaitingforSynchronisedStart Wait or start immediately when synchronized.
    JSWASM void loopBetween(double startMs, double endMs, bool jumpToStartMs, unsigned char pointID, bool synchronisedStart, unsigned int numLoops = 0, bool forceDefaultQuantum = false, bool preferWaitingforSynchronisedStart = false);
        
/// @brief Exit from the current loop.
/// @param synchronisedStart Synchronized start or re-synchronization after the loop exit.
    JSWASM void exitLoop(bool synchronisedStart = false);
    
/// @return Indicates if looping is enabled.
    JSWASM bool isLooping();
        
/// @return Returns true if a position is inside the current loop.
/// @param ms The position in milliseconds.
    JSWASM bool msInLoop(double ms);
    
/// @return Returns with the position of the closest beat.
/// @param ms The position in milliseconds where to find the closest beat.
/// @param beatIndex Set to 1-4 to retrieve the position of a specific beat index relative to ms, or 0 for any beat index.
    JSWASM double closestBeatMs(double ms, unsigned char beatIndex = 0);
    
/// @return Returns with the beat index of the closest beat.
/// @param ms The position in milliseconds where to find the closest beat.
    JSWASM unsigned char closestBeatIndex(double ms);
    
/// @brief Sets playback direction.
/// @param reverse True: reverse. False: forward.
/// @param slipMs Enable slip mode for a specific amount of time, or 0 to not slip.
    JSWASM void setReverse(bool reverse, unsigned int slipMs = 0);
    
/// @return If true, the player is playing backwards.
    JSWASM bool isReverse();

/// @brief Starts on changes pitch bend (temporary playback rate change).
/// @param maxPercent The maximum playback rate range for pitch bend, should be between 0.01f and 0.3f (1% and 30%).
/// @param bendStretch Use time-stretching for pitch bend or not (false makes it "audible").
/// @param faster True: faster, false: slower.
/// @param holdMs How long to maintain the pitch bend state. A value >= 1000 will hold until endContinuousPitchBend is called.
    JSWASM void pitchBend(float maxPercent, bool bendStretch, bool faster, unsigned int holdMs);
        
/// @brief Ends pitch bend.
    JSWASM void endContinuousPitchBend();
    
/// @return Returns with the distance (in milliseconds) to the beatgrid while using pitch bend for correction.
    JSWASM double getBendOffsetMs();
    
/// @brief Reset the pitch bend offset to the beatgrid to zero.
    JSWASM void resetBendMsOffset();
    
/// @return Indicates if returning from scratching or reverse playback will maintain the playback position as if the player had never entered into scratching or reverse playback.
    JSWASM bool isPerformingSlip();
    
/// @brief "Virtual jog wheel" or "virtual turntable" handling.
/// @param ticksPerTurn Sets the sensitivity of the virtual wheel. Use around 2300 for pixel-perfect touchscreen waveform control.
/// @param mode Jog wheel mode (scratching, pitch bend, or parameter set in the 0-1 range).
/// @param scratchSlipMs Enables slip mode for a specific amount of time for scratching, or 0 to not slip.
    JSWASM void jogTouchBegin(int ticksPerTurn, JogMode mode, unsigned int scratchSlipMs = 0);
        
/// @brief A jog wheel should send some "ticks" with the movement. A waveform's movement in pixels for example.
/// @param value The ticks value.
/// @param bendStretch Use time-stretching for pitch bend or not (false makes it "audible").
/// @param bendMaxPercent The maximum playback rate change for pitch bend, should be between 0.01f and 0.3f (1% and 30%).
/// @param bendHoldMs How long to maintain the pitch bend state. A value >= 1000 will hold until endContinuousPitchBend is called.
/// @param parameterModeIfNoJogTouchBegin True: if there was no jogTouchBegin, turn to JogMode_Parameter mode. False: if there was no jogTouchBegin, turn to JogMode_PitchBend mode.
    JSWASM void jogTick(int value, bool bendStretch, float bendMaxPercent, unsigned int bendHoldMs, bool parameterModeIfNoJogTouchBegin);

/// @brief Call this when the jog touch ends.
/// @param decelerate The decelerating rate for momentum. Set to 0.0f for automatic.
/// @param synchronisedStart Beat-synced start after decelerating.
    JSWASM void jogTouchEnd(float decelerate, bool synchronisedStart);
    
/// @brief Direct turntable handling. Call this when scratching starts.
/// @warning This is an advanced method, use it only if not using the jogT... methods.
/// @param slipMs Enable slip mode for a specific amount of time for scratching, or 0 to not slip.
/// @param stopImmediately Stop playback or not.
    JSWASM void startScratch(unsigned int slipMs, bool stopImmediately);
        
/// @brief Scratch movement.
/// @warning This is an advanced method, use it only if not using the jogT... methods.
/// @param pitch The current speed.
/// @param smoothing Should be between 0.05f (max. smoothing) and 1.0f (no smoothing).
    JSWASM void scratch(double pitch, float smoothing);
        
/// @brief Ends scratching.
/// @warning This is an advanced method, use it only if not using the jogT... methods.
/// @param returnToStateBeforeScratch Return to the previous playback state (direction, speed) or not.
    JSWASM void endScratch(bool returnToStateBeforeScratch);
    
/// @return Indicates if the player is in scratching mode.
    JSWASM bool isScratching();
    
/// @return If jog wheel mode is JogMode_Parameter, returns with the current parameter typically in the range of -1 to 1, or less than -1000000.0 if there was no jog wheel movement. processStereo or processMulti updates this value, therefore it's recommended to read it after those calls were made, in the same thread.
    JSWASM double getJogParameter();
    
private:
    PlayerInternals *internals;
    AdvancedAudioPlayer(const AdvancedAudioPlayer&);
    AdvancedAudioPlayer& operator=(const AdvancedAudioPlayer&);
>>>>>>> master
};

#endif
