#include "katana.h"
#include "util.h"

namespace KatanaFootController
{
    Katana::Katana()
    {
        printf("Initialized Katana\n");
    }

    Katana::~Katana()
    {

    }

    void Katana::SetGain(int value)
    {
        uint8_t gain = CONTROLLER->ConvertRange(0, 100, 0x14, 0x64, value);
        std::vector<uint8_t> params;
        params.insert(params.end(), &SYSEX_PARAMS_GAIN[0], &SYSEX_PARAMS_GAIN[sizeof(SYSEX_PARAMS_GAIN)]);
        params.push_back(gain);
        std::vector<uint8_t> msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);
    }

    void Katana::SetVolume(int value)
    {
        uint8_t volume = CONTROLLER->ConvertRange(0, 100, 0, 0x64, value);
        std::vector<uint8_t> params;
        params.insert(params.end(), &SYSEX_PARAMS_VOLUME[0], &SYSEX_PARAMS_VOLUME[sizeof(SYSEX_PARAMS_VOLUME)]);
        params.push_back(volume);
        std::vector<uint8_t> msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);
    }

    void Katana::SetAmplifierModel(AmplifierModel model)
    {
        std::vector<uint8_t> params;
        params.insert(params.end(), &SYSEX_PARAMS_AMP_MODEL[0], &SYSEX_PARAMS_AMP_MODEL[sizeof(SYSEX_PARAMS_AMP_MODEL)]);
        params.push_back((uint8_t)model);
        std::vector<uint8_t> msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);
    }

    void Katana::SetEQ(EqualizerBand band, int value)
    {
        uint8_t v = CONTROLLER->ConvertRange(0, 100, 0, 0x64, value);
        std::vector<uint8_t> params;
        params.insert(params.end(), &SYSEX_PARAMS_EQ_BASS[0], &SYSEX_PARAMS_EQ_BASS[sizeof(SYSEX_PARAMS_EQ_BASS) - 1]);
        params.push_back((uint8_t)band);
        params.push_back(v);
        std::vector<uint8_t> msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);
    }

    void Katana::SetBoost(BoostModel model, int value)
    {
        std::vector<uint8_t> params;
        params.insert(params.end(), &SYSEX_PARAMS_BOOST_MODEL[0], &SYSEX_PARAMS_BOOST_MODEL[sizeof(SYSEX_PARAMS_BOOST_MODEL)]);
        params.push_back((uint8_t)model);
        std::vector<uint8_t> msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);

        uint8_t v = CONTROLLER->ConvertRange(0, 100, 0, 120, value);
        params.clear();
        params.insert(params.end(), &SYSEX_PARAMS_BOOST_LEVEL[0], &SYSEX_PARAMS_BOOST_LEVEL[sizeof(SYSEX_PARAMS_BOOST_LEVEL)]);
        params.push_back(v);
        msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);
    }

    void Katana::SetModifier(ModifierModel model, int value)
    {
        std::vector<uint8_t> params;
        params.insert(params.end(), &SYSEX_PARAMS_MOD_MODEL[0], &SYSEX_PARAMS_MOD_MODEL[sizeof(SYSEX_PARAMS_MOD_MODEL)]);
        params.push_back((uint8_t)model);
        std::vector<uint8_t> msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);

        uint8_t v = CONTROLLER->ConvertRange(0, 100, 0, 50, value);
        params.clear();
        params.insert(params.end(), &SYSEX_PARAMS_MOD_LEVEL[0], &SYSEX_PARAMS_MOD_LEVEL[sizeof(SYSEX_PARAMS_MOD_LEVEL)]);
        params.push_back(v);
        msg = CONTROLLER->CreateMessage(MessageType::setting, params);
        CONTROLLER->SendMessage(msg);
    }
}