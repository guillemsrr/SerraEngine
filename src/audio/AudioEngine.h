// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include <vector>
#include "AudioData.h"

#include <SDL3/SDL_audio.h>

class AudioEngine
{
public:
    AudioEngine();

protected:
    ~AudioEngine();

public:
    void PlaySynthSoundMix(float frequency, float duration, float volume = 1.f);

protected:
    SDL_AudioStream* _stream = nullptr;

    int _sampleRate = 48000;

    const float _minDuration = 0.1f;
    const float _baseVolume = 0.5f;

    virtual void HandleAudio(AudioData& voice, float* samples, int count)
    {
    }

    std::vector<AudioData> _activeAudios;

    int GetNumSamples(float duration) const;

private:
    static void SDLCALL FeedAudioCallback(void* userdata, SDL_AudioStream* stream, int additional, int total);
};