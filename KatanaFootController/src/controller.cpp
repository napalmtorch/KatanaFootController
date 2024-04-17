#include "controller.h"
#include "util.h"

#define _AMD64_
#include <synchapi.h>

namespace KatanaFootController
{
    Controller::Controller()
    {
        _input    = nullptr;
        _output   = nullptr;
        _port_in  = -1;
        _port_out = -1;
        memset(_buffer, 0, sizeof(_buffer));

        try 
        {
            _input = new RtMidiIn(); 
            for (size_t i = 0; i < _input->getPortCount(); i++)
            {
                std::string name = _input->getPortName(i).substr(0, _input->getPortName(i).size() - 2);
                if (name == "KATANA") { _port_in = (int)i; _input->openPort(i); break; }
            }
            if (!_input->isPortOpen()) { errorf("Failed to open input port"); }
            printf("Located input port '%s'\n", _input->getPortName(_port_in).c_str());
        }
        catch (RtMidiError& error) { error.printMessage(); exit(EXIT_FAILURE); }

        try
        {
            _output = new RtMidiOut();
            for (size_t i = 0; i < _output->getPortCount(); i++)
            {
                std::string name = _output->getPortName(i).substr(0, _output->getPortName(i).size() - 2);
                if (name == "KATANA") { _port_out = (int)i; _output->openPort(i); break; }
            }
            if (!_output->isPortOpen()) { errorf("Failed to open output port"); }
            printf("Located output port '%s'\n", _output->getPortName(_port_out).c_str());
        }
        catch (RtMidiError& error) { error.printMessage(); exit(EXIT_FAILURE); }

        printf("Initialized MIDI communication controller instance\n");
    }

    Controller::~Controller()
    {
        printf("Disposed MIDI communication controller instance\n");
    }

    RtMidiOut& Controller::GetOutputDevice()
    {
        if (_output == NULL) { errorf("No output device detected"); }
        return *_output;
    }

    RtMidiIn& Controller::GetInputDevice()
    {
        if (_input == NULL) { errorf("No input device detected"); }
        return *_input;

    }

    int Controller::GetOutputPort() { return _port_out; }

    int Controller::GetInputPort() { return _port_in; }

    std::vector<uint8_t> Controller::CreateMessage(MessageType type, const std::vector<uint8_t>& params)
    {
        std::vector<uint8_t> data;
        for (size_t i = 0; i < sizeof(SYSEX_HEADER); i++) { data.push_back(SYSEX_HEADER[i]); }
        data.push_back((uint8_t)type);

        for (auto b : params) { data.push_back(b); }
        uint8_t chksm = CalculateChecksum(params.data(), 0, params.size());
        data.push_back(chksm);
        data.push_back(SYSEX_END);
        return data;
    }

    uint8_t Controller::CalculateChecksum(const uint8_t* msg, int offset, size_t sz)
    {
        uint8_t accum = 0;
        for (size_t i = 0; i < sz; i++) { accum = (uint8_t)((accum + msg[offset + i] & 0x7F)); }
        uint8_t chksm = (uint8_t)((0x80 - accum) & 0x7F);
        return chksm;
    }

    int Controller::ConvertRange(int orig_start, int orig_end, int start, int end, int value)
    {
        float scale = (float)((float)end - start) / ((float)orig_end - orig_start);
        return (int)(start + (((float)value - orig_start) * scale));
    }

    void Controller::SendMessage(const std::vector<uint8_t>& msg)
    {
        _output->sendMessage(msg.data(), msg.size());
        Sleep(100);
    }
}