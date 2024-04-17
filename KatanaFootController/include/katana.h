#pragma once
#include "controller.h"

namespace KatanaFootController
{
    class Katana
    {
        public:
            Katana();
            ~Katana();

        public:
            void SetGain(int value);
            void SetVolume(int value);
            void SetAmplifierModel(AmplifierModel model);
            void SetEQ(EqualizerBand band, int value);
            void SetBoost(BoostModel model, int value);
            void SetModifier(ModifierModel model, int value);
    };
}