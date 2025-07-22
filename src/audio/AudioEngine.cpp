#include "AudioEngine.h"

#include <algorithm>
#include <random>

#include <SDL3/SDL_init.h>

AudioEngine::AudioEngine()
{
    SDL_AudioSpec spec;
    spec.channels = 2;
    spec.format = SDL_AUDIO_F32;
    spec.freq = _sampleRate;

    _stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, FeedAudioCallback, this);

    SDL_ResumeAudioStreamDevice(_stream);
}

AudioEngine::~AudioEngine()
{
    //which one?
    //SDL_DestroyAudioStream(_stream);
    SDL_ClearAudioStream(_stream);
}

void AudioEngine::PlaySynthSoundMix(float frequency, float duration, float volume)
{
    if (duration <= 0.f)
    {
        return;
    }

    duration = std::max(duration, _minDuration);

    AudioData audioData;
    audioData.Frequency = frequency;
    audioData.Duration = duration;
    audioData.Volume = volume;
    audioData.Elapsed = 0.f;
    audioData.Phase = 0.f;

    _activeAudios.push_back(audioData);
}

int AudioEngine::GetNumSamples(float duration) const
{
    int numSamples = static_cast<int>(_sampleRate * duration);
    return numSamples;
}

void AudioEngine::FeedAudioCallback(void* userdata, SDL_AudioStream* stream, int additional, int total)
{
    auto* engine = static_cast<AudioEngine*>(userdata);
    if (!engine)
    {
        return;
    }

    /*if (additional > 0)
    {
        // Generate silence or procedural audio for now
        Uint8* buffer = SDL_stack_alloc(Uint8, additional);
        if (buffer)
        {
            SDL_memset(buffer, 0, additional); // Silence for now
            SDL_PutAudioStreamData(stream, buffer, additional);
            SDL_stack_free(buffer);
        }
    }*/

    additional /= sizeof(float);

    if (engine->_activeAudios.empty())
    {
        return;
    }

    while (additional > 0)
    {
        const int count = SDL_min(additional, 128);
        float samples[128] = {0.0f};

        for (AudioData& voice : engine->_activeAudios)
        {
            if (voice.Elapsed >= voice.Duration)
                continue;

            engine->HandleAudio(voice, samples, count);
        }

        for (int i = 0; i < count; ++i)
        {
            samples[i] *= engine->_baseVolume;
            samples[i] = std::clamp(samples[i], -1.0f, 1.0f);
        }

        SDL_PutAudioStreamData(stream, samples, static_cast<int>(count) * sizeof(float));
        additional -= count;
    }

    std::erase_if(engine->_activeAudios,
                  [](const AudioData& v)
                  {
                      return v.Elapsed >= v.Duration;
                  });
}