// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "core/Actor.h"
#include "AudioData.h"
#include "AudioSettings.h"

class AudioEmitter : public Actor
{
public:
    AudioEmitter() = default;

    void SetAudioData(const AudioData& audioData) { _audioData = audioData; }
    const AudioData& GetAudioData() const { return _audioData; }

    void SetAudioSettings(const AudioSettings& audioSettings) { _audioSettings = audioSettings; }
    const AudioSettings& GetAudioSettings() const { return _audioSettings; }
    AudioSettings& GetAudioSettings() { return _audioSettings; }

private:
    AudioData _audioData;
    AudioSettings _audioSettings;
};
