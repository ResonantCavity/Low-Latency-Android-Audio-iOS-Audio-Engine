#ifndef Header_SuperpoweredAudioBuffers
#define Header_SuperpoweredAudioBuffers

#include <stdint.h>

struct bufferPoolInternals;
struct pointerListInternals;
struct SuperpoweredAudiobufferlistElement;

/**
 @brief This object manages an audio buffer pool.
 
 It reduces the number of memory allocation requests, increasing efficiency of audio applications.
 Check the SuperpoweredOfflineProcessingExample project on how to use.
 */
class SuperpoweredAudiobufferPool {
public:
/**
 @brief Do not use this.
 */
    static void initialize();
/**
 @brief Creates a buffer with retain count set to 1, similar to an NSObject in Objective-C. Use releaseBuffer() to release.
 
 @return The buffer.
 
 Never blocks, never locks, very fast and safe to use in a realtime thread -- only if the fixed memory region is able to satisfy the request.
 @see allocBuffer otherwise.
 Can be called concurrently.
 
 @param sizeBytes The buffer's size in bytes.
 */
    static void *getBuffer(unsigned int sizeBytes);
/**
 @brief Allocates a buffer using malloc, aligned to 16 bytes. Retain count will be set to 1, similar to an NSObject in Objective-C. Use releaseBuffer() to release.
 
 Don't use this function in a realtime thread, as it calls malloc.
 The returned buffer however can safely be used and released in any kind of thread.
 Can not be called concurrently.
 
 @return The buffer.
 
 @param sizeBytes The buffer's size in bytes.
 */
    static void *allocBuffer(unsigned int sizeBytes);
/**
 @brief Release a buffer, similar to an NSObject in Objective-C (decreases the retain count by 1, the memory will be freed after retain count reaches 0).
 
 Never blocks, never locks, very fast and safe to use in a realtime thread. Can be called concurrently.
 
 @param buffer The buffer.
 */
    static void releaseBuffer(void *buffer);
/**
 @brief Retain a buffer, similar to Objective-C (increases the retain count by 1, similar to an NSObject in Objective-C).
 
 Never blocks, never locks, very fast and safe to use in a realtime thread. Can be called concurrently.
 
 @param buffer The buffer.
*/
    static void retainBuffer(void *buffer);

private:
    bufferPoolInternals *internals;
    SuperpoweredAudiobufferPool(const SuperpoweredAudiobufferPool&);
    SuperpoweredAudiobufferPool& operator=(const SuperpoweredAudiobufferPool&);
};

<<<<<<< HEAD
=======
/// @brief An audio buffer list item, inside an AudiopointerList.
typedef struct AudiopointerlistElement {
    void *buffers[4];       ///< The buffers, coming from Superpowered AudiobufferPool.
    int firstFrame;         ///< The index of the first frame in the buffer.
    int lastFrame;          ///< The index of last frame in the buffer. The length of the buffer: lastFrame - firstFrame.
    int positionFrames;     ///< Can be used to track position information.
    float framesUsed;       ///< Can be used to track how many "original" frames were used to create this chunk of audio. Useful for time-stretching or resampling to precisely track the movement of the playhead.
} AudiopointerlistElement;
>>>>>>> master

/**
 @brief This object manages an audio buffer list.
 
 Instead of circular buffers and too many memmove/memcpy, this object maintains an audio buffer "chain". You can append, insert, truncate, slice, extend, etc. this without the expensive memory operations.
 Check the SuperpoweredOfflineProcessingExample project on how to use.
 
 @param sampleLength The number of samples inside this list.
 */
class SuperpoweredAudiopointerList {
public:    
    int sampleLength;
    
<<<<<<< HEAD
/**
 @brief Creates an audio buffer list.
 
 @param bytesPerSample Sample size. For example: 4 for 16-bit stereo, 8 for 32-bit stereo audio.
 @param typicalNumElements Each list item uses 28 bytes memory on a 64-bit device. This number sets the initial memory usage of this list.
 */
    SuperpoweredAudiopointerList(unsigned int bytesPerSample, unsigned int typicalNumElements);
    ~SuperpoweredAudiopointerList();
=======
/// @brief Append a buffer to the end of the list. The list will increase the retain count of the buffer by 1, similar to Objective-C.
/// Not safe to use in a real-time thread, because it may use blocking memory operations.
/// @param buffer The buffer to append.
    void append(AudiopointerlistElement *buffer);

/// @brief Insert a buffer before the beginning of the list. The list will increase the retain count of the buffer by 1, similar to Objective-C.
/// Not safe to use in a real-time thread, because it may use blocking memory operations.
/// @param buffer The buffer to insert.
    void insert(AudiopointerlistElement *buffer);
        
/// @brief Append all buffers to another buffer list. The anotherList will increase the retain count of all buffers by 1.
/// Not safe to use in a real-time thread, because it may use blocking memory operations.
    void copyAllBuffersTo(AudiopointerList *anotherList);
    
/// @brief Remove frames from the beginning. If all of a buffer's contents are from this list, it will decrease the buffer's retain count by 1.
/// Safe to use in a real-time thread.
/// @param numFrames The number of frames to remove.
    void removeFromStart(int numFrames);
>>>>>>> master
    
/**
 @brief Append a buffer to the end of the list. The list will increase the retain count of the buffer by 1, similar to Objective-C.
 */
    void append(SuperpoweredAudiobufferlistElement *buffer);
/**
 @brief Insert a buffer before the beginning of the list. The list will increase the retain count of the buffer by 1, similar to Objective-C.
 */
    void insert(SuperpoweredAudiobufferlistElement *buffer);
/**
 @brief Remove everything from the list. It will decrease the retain count of all buffers by 1.
 */
    void clear();
/**
 @brief Appends all buffers to another buffer list. The anotherList will increase the retain count of all buffers by 1.
 */
    void copyAllBuffersTo(SuperpoweredAudiopointerList *anotherList);
/**
 @brief Removes samples from the beginning or the end. If a buffer is fully truncated from this list, it will decrease the buffer's retain count by 1.
 
 @param numSamples The number of samples to remove.
 @param fromTheBeginning From the end or the beginning.
 */
    void truncate(int numSamples, bool fromTheBeginning);
/**
 @brief Returns the buffer list beginning's sample position in an audio file or stream.
 */
    int64_t startSamplePosition();
/**
 @brief Returns the buffer list end's sample position in an audio file or stream, plus 1.
*/
    int64_t nextSamplePosition();
    
<<<<<<< HEAD
/**
 @brief Creates a "virtual slice" from this list.
 
 @param fromSample The slice will start from this sample.
 @param lengthSamples The slice will contain this number of samples.
 */
    bool makeSlice(int fromSample, int lengthSamples);
/**
 @brief Returns the slice beginning's sample position in an audio file or stream.
 */
    int64_t samplePositionOfSliceBeginning();
=======
/// @return Returns with the length of audio in the list.
    int getLengthFrames();
    
/// @brief Returns the start position in an audio file or stream.
/// Safe to use in a real-time thread.
    int getPositionFrames();
    
/// @brief Returns the end position in an audio file or stream, plus 1.
/// Safe to use in a real-time thread.
    int getNextPositionFrames();
    
/// @brief Creates a "virtual slice" from this list.
/// Safe to use in a real-time thread.
/// @param fromFrame The slice will start from this frame.
/// @param lengthFrames The slice will contain this number of frames.
/// @return True if succeeded, false if could not provide a slice with these arguments.
    bool makeSlice(int fromFrame, int lengthFrames);
>>>>>>> master

/**
 @return This the slice's forward enumerator method to go through all buffers in it. Returns a pointer to the audio, or NULL.

 @param lengthSamples Returns the number of samples in audio.
 @param samplesUsed Returns the number of original number of samples, creating this chunk of audio. Good for time-stretching for example, to track the movement of the playhead.
 @param stereoPairIndex Not implemented yet.
 @param nextSamplePosition Not implemented yet.
 */
    void *nextSliceItem(int *lengthSamples, float *samplesUsed = 0, int stereoPairIndex = 0, int64_t *nextSamplePosition = 0);
/**
 @brief Returns the slice enumerator to the first buffer.
 */
    void rewindSlice();
/**
 @brief Jumps the enumerator to the last buffer.
 */
    void forwardToLastSliceBuffer();
<<<<<<< HEAD
/**
 @return This the slice's backwards (reverse) enumerator method to go through all buffers in it. Returns a pointer to the audio, or NULL.

 @param lengthSamples Returns the number of samples in audio.
 @param samplesUsed Returns the number of original number of samples, creating this chunk of audio. Good for time-stretching for example, to track the movement of the playhead.
 @param stereoPairIndex Not implemented yet.
*/
    void *prevSliceItem(int *lengthSamples, float *samplesUsed = 0, int stereoPairIndex = 0);
=======
    
/// @brief Returns the slice start position in an audio file or stream.
/// Safe to use in a real-time thread.
    int getSlicePositionFrames();
    
>>>>>>> master
private:
    pointerListInternals *internals;
    SuperpoweredAudiopointerList(const SuperpoweredAudiopointerList&);
    SuperpoweredAudiopointerList& operator=(const SuperpoweredAudiopointerList&);
};

/**
 @brief An audio buffer list item.

 @param buffers The buffers, coming from SuperpoweredAudiobufferPool.
 @param samplePosition The buffer beginning's sample position in an audio file or stream.
 @param startSample The first sample in the buffer.
 @param endSample The last sample in the buffer.
 @param samplesUsed How many "original" samples were used to create this chunk of audio. Good for time-stretching for example, to track the movement of the playhead.
 */
typedef struct SuperpoweredAudiobufferlistElement {
    void *buffers[4];
    int64_t samplePosition;
	int startSample, endSample;
    float samplesUsed;
} SuperpoweredAudiobufferlistElement;

#endif
