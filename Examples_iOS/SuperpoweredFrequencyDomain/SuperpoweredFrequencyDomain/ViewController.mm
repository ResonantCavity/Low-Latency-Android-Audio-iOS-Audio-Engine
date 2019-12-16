#import "ViewController.h"
#import "SuperpoweredIOSAudioIO.h"
#include "Superpowered.h"
#include "SuperpoweredFrequencyDomain.h"
#include "SuperpoweredSimple.h"

@implementation ViewController {
    SuperpoweredIOSAudioIO *audioIO;
    Superpowered::FrequencyDomain *frequencyDomain;
    float *magnitudeLeft, *magnitudeRight, *phaseLeft, *phaseRight, *fifoOutput;
    int fifoOutputFirstSample, fifoOutputLastSample, fftSize, fifoCapacity;
}

#define FFT_LOG_SIZE 11 // 2^11 = 2048
#define OVERLAP_RATIO 4 // The default overlap ratio is 4:1, so we will receive this amount of frames from the frequency domain in one step.

// This callback is called periodically by the audio system.
static bool audioProcessing(void *clientdata, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfFrames, unsigned int samplerate, uint64_t hostTime) {
    __unsafe_unretained ViewController *self = (__bridge ViewController *)clientdata;
    NSLog(@"input channels %d, output channels %d, samples %d, rate %d", inputChannels, outputChannels, numberOfSamples, samplerate);
    // Input goes to the frequency domain.
    float interleaved[numberOfFrames * 2];
    Superpowered::Interleave(inputBuffers[0], inputBuffers[1], interleaved, numberOfFrames);
    self->frequencyDomain->addInput(interleaved, numberOfFrames);

    // In the frequency domain we are working with 1024 magnitudes and phases for every channel (left, right), if the fft size is 2048.
    while (self->frequencyDomain->timeDomainToFrequencyDomain(self->magnitudeLeft, self->magnitudeRight, self->phaseLeft, self->phaseRight)) {
        // You can work with frequency domain data from this point.

        // This is just a quick example: we remove the magnitude of the first 20 bins, meaning total bass cut between 0-430 Hz.
        memset(self->magnitudeLeft, 0, 80);
        memset(self->magnitudeRight, 0, 80);

        // We are done working with frequency domain data. Let's go back to the time domain.

        // Check if we have enough room in the fifo buffer for the output. If not, move the existing audio data back to the buffer's beginning.
        if (self->fifoOutputLastSample + self->fftSize / OVERLAP_RATIO >= self->fifoCapacity) { // This will be true for every 100th iteration only, so we save precious memory bandwidth.
            int samplesInFifo = self->fifoOutputLastSample - self->fifoOutputFirstSample;
            if (samplesInFifo > 0) memmove(self->fifoOutput, self->fifoOutput + self->fifoOutputFirstSample * 2, samplesInFifo * sizeof(float) * 2);
            self->fifoOutputFirstSample = 0;
            self->fifoOutputLastSample = samplesInFifo;
        };

        // Transforming back to the time domain.
        self->frequencyDomain->frequencyDomainToTimeDomain(self->magnitudeLeft, self->magnitudeRight, self->phaseLeft, self->phaseRight, self->fifoOutput + self->fifoOutputLastSample * 2);
        self->frequencyDomain->advance();
        self->fifoOutputLastSample += self->fftSize / OVERLAP_RATIO;
    };

    // If we have enough samples in the fifo output buffer, pass them to the audio output.
    if (self->fifoOutputLastSample - self->fifoOutputFirstSample >= numberOfFrames) {
        Superpowered::DeInterleave(self->fifoOutput + self->fifoOutputFirstSample * 2, outputBuffers[0], outputBuffers[1], numberOfFrames);
        self->fifoOutputFirstSample += numberOfFrames;
        return true;
    } else return false;
}

- (void)viewDidLoad {
    [super viewDidLoad];
#ifdef __IPHONE_13_0
    if (@available(iOS 13, *)) self.overrideUserInterfaceStyle = UIUserInterfaceStyleLight;
#endif
    
    Superpowered::Initialize(
                             "ExampleLicenseKey-WillExpire-OnNextUpdate",
                             false, // enableAudioAnalysis (using SuperpoweredAnalyzer, SuperpoweredLiveAnalyzer, SuperpoweredWaveform or SuperpoweredBandpassFilterbank)
                             true, // enableFFTAndFrequencyDomain (using SuperpoweredFrequencyDomain, SuperpoweredFFTComplex, SuperpoweredFFTReal or SuperpoweredPolarFFT)
                             false, // enableAudioTimeStretching (using SuperpoweredTimeStretching)
                             false, // enableAudioEffects (using any SuperpoweredFX class)
                             false, // enableAudioPlayerAndDecoder (using SuperpoweredAdvancedAudioPlayer or SuperpoweredDecoder)
                             false, // enableCryptographics (using Superpowered::RSAPublicKey, Superpowered::RSAPrivateKey, Superpowered::hasher or Superpowered::AES)
                             false  // enableNetworking (using Superpowered::httpRequest)
                             );

    frequencyDomain = new Superpowered::FrequencyDomain(FFT_LOG_SIZE); // This will do the main "magic".
    fftSize = 1 << FFT_LOG_SIZE;

    // Frequency domain data goes into these buffers:
    magnitudeLeft = (float *)malloc(fftSize * sizeof(float));
    magnitudeRight = (float *)malloc(fftSize * sizeof(float));
    phaseLeft = (float *)malloc(fftSize * sizeof(float));
    phaseRight = (float *)malloc(fftSize * sizeof(float));

    // Time domain result goes into a FIFO (first-in, first-out) buffer
    fifoOutputFirstSample = fifoOutputLastSample = 0;
    fifoCapacity = fftSize / OVERLAP_RATIO * 100; // Let's make the fifo's size 100 times more than the step size, so we save memory bandwidth.
    fifoOutput = (float *)malloc(fifoCapacity * sizeof(float) * 2 + 128);

    // Audio input/output handling.
    audioIO = [[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredSamplerate:44100 audioSessionCategory:AVAudioSessionCategoryPlayAndRecord channels:2 audioProcessingCallback:audioProcessing clientdata:(__bridge void *)self];
    [audioIO start];
}

- (void)dealloc {
    audioIO = nil;
    delete frequencyDomain;
    free(magnitudeLeft);
    free(magnitudeRight);
    free(phaseLeft);
    free(phaseRight);
    free(fifoOutput);
}

@end
