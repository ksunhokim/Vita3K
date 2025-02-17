#pragma once

#include <ngs/system.h>

namespace ngs::player {
    struct BufferParameter {
        Ptr<void> buffer;
        std::int32_t bytes_count;
        std::int16_t loop_count;
        std::int16_t next_buffer_index;
        std::int16_t samples_discard_start_off;
        std::int16_t samples_discard_end_off;
    };

    static constexpr std::uint32_t MAX_BUFFER_PARAMS = 4;

    struct Parameters {
        ngs::ModuleParameterHeader header;
        BufferParameter buffer_params[MAX_BUFFER_PARAMS];
        float playback_frequency;
        float playback_scalar;
        std::int32_t lead_in_samples;
        std::int32_t limit_number_of_samples_played;
        std::int32_t start_bytes;
        std::int8_t channels;
        std::int8_t channel_map[2];
        std::int8_t type;
        std::int8_t unk60;
        std::int8_t start_buffer;
        std::int8_t unk62;
        std::int8_t unk63;
    };

    struct Module: public ngs::Module {
        explicit Module();
        void process(const MemState &mem, Voice *voice) override;
        void get_expectation(AudioDataType *expect_audio_type, std::int16_t *expect_channel_count) override { }
    };

    struct VoiceDefinition: public ngs::VoiceDefinition {
        std::unique_ptr<ngs::Module> new_module() override;
        std::size_t get_buffer_parameter_size() const override;
    };
};