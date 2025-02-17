#pragma once

#include <ngs/system.h>

#include <codec/state.h>

namespace ngs::atrac9 {
    struct BufferParameter {
        Ptr<void> buffer;
        std::int32_t bytes_count;
        std::int16_t loop_count;
        std::int16_t next_buffer_index;
        std::int16_t samples_discard_start_off;
        std::int16_t samples_discard_end_off;
    };

    struct SkipBufferInfo {
        std::int32_t start_byte_offset;
        std::int32_t num_bytes;
        std::int16_t start_skip;
        std::int16_t end_skip;
        std::int32_t is_super_packet;
    };

    static constexpr std::uint32_t MAX_BUFFER_PARAMS = 4;

    struct Parameters {
        ngs::ModuleParameterHeader header;
        BufferParameter buffer_params[MAX_BUFFER_PARAMS];
        float playback_frequency;
        float playback_scalar;
        std::int32_t lead_in_samples;
        std::int32_t limit_number_of_samples_played;
        std::int8_t channels;
        std::int8_t channel_map[2];
        std::int8_t unk5B;
        std::uint32_t config_data;
    };

    struct State {
        std::int32_t current_byte_position_in_buffer;
        std::int32_t current_buffer;
        std::int32_t samples_generated_since_key_on;
        std::int32_t bytes_consumed_since_key_on;
        std::int32_t total_bytes_consumed;
        std::int8_t current_loop_count;
    };

    struct Module: public ngs::Module {
    private:
        std::unique_ptr<Atrac9DecoderState> decoder;

        PCMChannelBuf decoded_pending;
        std::uint32_t decoded_samples_pending;
        std::uint32_t decoded_passed;

    public:
        explicit Module();
        void process(const MemState &mem, Voice *voice) override;
        void get_expectation(AudioDataType *expect_audio_type, std::int16_t *expect_channel_count) override { }
    };

    struct VoiceDefinition: public ngs::VoiceDefinition {
        std::unique_ptr<ngs::Module> new_module() override;
        std::size_t get_buffer_parameter_size() const override;
    };

    void get_buffer_parameter(std::uint32_t start_sample, std::uint32_t
        num_samples, std::uint32_t info, SkipBufferInfo &parameter);
};