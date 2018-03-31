#include "audio_player.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <stdint.h>

//----------------------------------------------------------

namespace AudioPlayer
{

//----------------------------------------------------------
    
bool clip_finished;

class Mp3Notify
{
public:
    static void OnError(uint16_t errorCode) {}
    static void OnCardOnline(uint16_t code) {}
    static void OnCardInserted(uint16_t code) {}
    static void OnCardRemoved(uint16_t code) {}

    static void OnPlayFinished(uint16_t globalTrack)
    { 
        clip_finished = true;
    }
};

#define DFP_RX      9
#define DFP_TX      8

SoftwareSerial serial(DFP_RX, DFP_TX);
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(serial);

//----------------------------------------------------------

void init()
{
    mp3.begin();
}

//----------------------------------------------------------

void process()
{
    mp3.loop();
}

//----------------------------------------------------------

void set_volume(int volume)
{
    mp3.setVolume(100);
}

//----------------------------------------------------------

void play_track(int id)
{
    clip_finished = false;
    mp3.playMp3FolderTrack(id);
}

//----------------------------------------------------------

bool is_finished()
{
    return clip_finished;
}

//----------------------------------------------------------

}
