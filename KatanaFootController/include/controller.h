#pragma once
#include "midi.h"
#include <vector>

namespace KatanaFootController
{
    class Controller;
}

extern KatanaFootController::Controller* CONTROLLER;

namespace KatanaFootController
{
    static const uint8_t SYSEX_HEADER[] = { 0xF0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x33 };
    static const uint8_t SYSEX_END      = 0xF7;

    static const uint8_t SYSEX_PARAMS_GAIN[]   = { 0x60, 0x00, 0x00, 0x22 };
    static const uint8_t SYSEX_PARAMS_VOLUME[] = { 0x60, 0x00, 0x00, 0x28 };

    static const uint8_t SYSEX_PARAMS_EQ_BASS[]   = { 0x60, 0x00, 0x00, 0x24 };
    static const uint8_t SYSEX_PARAMS_EQ_MID[]    = { 0x60, 0x00, 0x00, 0x25 };
    static const uint8_t SYSEX_PARAMS_EQ_TREBLE[] = { 0x60, 0x00, 0x00, 0x26 };
    static const uint8_t SYSEX_PARAMS_AMP_MODEL[] = { 0x60, 0x00, 0x00, 0x21 };

    static const uint8_t SYSEX_PARAMS_BOOST_MODEL[] = { 0x60, 0x00, 0x06, 0x25 };
    static const uint8_t SYSEX_PARAMS_BOOST_LEVEL[] = { 0x60, 0x00, 0x00, 0x12 };

    static const uint8_t SYSEX_PARAMS_MOD_MODEL[] = { 0x60, 0x00, 0x06, 0x28 };
    static const uint8_t SYSEX_PARAMS_MOD_LEVEL[]  = { 0x60, 0x00, 0x02, 0x0B };

    enum class MessageType : uint8_t
    {
        query   = 0x11,
        setting = 0x12,
    };

    enum class EqualizerBand : uint8_t
    {
        Bass   = 0x24,
        Middle = 0x25,
        Treble = 0x26,
    };

    enum class AmplifierModel : uint8_t
    {
        brown1      = 0x17,
        lead1       = 0x18,
        crunch1     = 0x0B,
        clean1      = 0x08,
        acoustic1   = 0x01,
        brown2      = 0x20,
        lead2       = 0x1F,
        crunch2     = 0x1E,
        clean2      = 0x1D,
        acoustic2   = 0x1C,
    };

    enum class BoostModel : uint8_t
    {
        clean           = 0x01,
        treble          = 0x02,
        mid             = 0x00,
        crunch_od       = 0x03,
        blues_drive     = 0x0A,
        overdrive       = 0x0B,
        natural_od      = 0x04,
        warm_od         = 0x05,
        turbo_od        = 0x0D,
        t_scream        = 0x0C,
        distortion      = 0x0E,
        fat_ds          = 0x06,
        dst_plus        = 0x11,
        guv_ds          = 0x10,
        rat             = 0x0F,
        metal_zone      = 0x12,
        metal_ds        = 0x08,
        fuzz_60s        = 0x13,
        fuzz_muff       = 0x14,
        fuzz_oct        = 0x09,
        hm2             = 0x15,
        metal_core      = 0x16,
        centa_od        = 0x5E,
    };

    enum class ModifierModel : uint8_t
    {
        chorus = 0x1D,
        flanger = 0x14,
        phaser = 0x13,
        uni_v = 0x17,
        tremolo = 0x15,
        vibrato = 0x1A,
        rotary = 0x16,
        ring_mod = 0x1B,
        slow_gear = 0x0A,
        slicer = 0x19,
        comp = 0x03,
        limiter = 0x04,
        t_wah = 0x00,
        auto_wah = 0x01,
        pedal_wah = 0x02,
        graphic_eq = 0x06,
        parametric_eq = 0x07,
        guitar_sim = 0x09,
        ac_guitar_sim = 0x1F,
        ac_processor = 0x12,
        wave_synth = 0x0C,
        octave = 0x0E,
        heavy_octave = 0x27,
        pitch_shifter = 0x0F,
        harmonist = 0x10,
        humanizer = 0x1C,
        phaser_90e = 0x23,
        flanger_117e = 0x24,
        wah_95e = 0x25,
        dc_30 = 0x26,
        pedal_bend = 0x28,
    };

    class Controller
    {
        private:
            RtMidiOut* _output;
            RtMidiIn*  _input;
            int        _port_in;
            int        _port_out;
            uint8_t    _buffer[64];

        public:
            Controller();
            ~Controller();

        public:
            RtMidiOut& GetOutputDevice();
            RtMidiIn& GetInputDevice();
            int GetOutputPort();
            int GetInputPort();

        public:
            std::vector<uint8_t> CreateMessage(MessageType type, const std::vector<uint8_t>& params);
            uint8_t CalculateChecksum(const uint8_t* msg, int offset, size_t sz);
            int ConvertRange(int orig_start, int orig_end, int start, int end, int value);
            void SendMessage(const std::vector<uint8_t>& msg);
    };
}