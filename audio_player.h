#ifndef AUDIO_PLAYER_H_
#define AUDIO_PLAYER_H_

//----------------------------------------------------------

namespace AudioPlayer
{

void init();
void process();
void set_volume(int volume);
void play_track(int id);
bool is_finished();

}

//----------------------------------------------------------

#endif