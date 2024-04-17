#include <stdio.h>
#include "midi.h"
#include "controller.h"
#include "katana.h"

#define _AMD64_
#include <synchapi.h>
using namespace KatanaFootController;

Controller* CONTROLLER = NULL;
Katana* KATANA = NULL;

int main()
{
    CONTROLLER = new Controller();
    KATANA = new Katana();

    KATANA->SetAmplifierModel(AmplifierModel::brown2);
    KATANA->SetGain(50);
    KATANA->SetVolume(100);
    KATANA->SetEQ(EqualizerBand::Bass, 36);
    KATANA->SetEQ(EqualizerBand::Middle, 48);
    KATANA->SetEQ(EqualizerBand::Treble, 60);

    KATANA->~Katana();
    CONTROLLER->~Controller();
    return 0;
}