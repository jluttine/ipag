#ifndef _SOUNDS_H_
#define _SOUNDS_H_

//SOUNDS ON
//#define SOUND

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <SDL/SDL.h>

#ifdef SOUND
//	#include "SDL_mixer.h"
	#include <SDL/SDL_mixer.h>
#endif

using std::vector;

 
/**
 * Class Sounds.
 * Plays all audio.
 * @author Lasse Hakulinen
 */

class Sounds {

public:

	/**
	 * Constructor.
	 * @param rate - audio rate
	 * @param format - audio format
	 * @param channels - number of channels (mono or stereo)
	 * @param buffers - size of buffer
	 */
	Sounds(int rate, Uint16 format, int channels, int buffers);
	
	/**
	 * Frees all memory allocated for audio
	 */
	~Sounds();
	
	/**
	 * Plays a sound of a certain index
	 * @param index - index of the sound
	 */
	void const playSound(int index);
	
	/**
	 * Disables all sounds
	 */
	void disableSounds();
	
	/**
	 * Enables all sounds
	 */
	void enableSounds();
	
	/**
	 * Sets the general volume of the played sounds
	 * Minimum volume = 0, maximum = 128
	 * @param volume - new volume
	 */
	void setVolume(int volume);
	
	/**
	 * Increases the volume (or decreases if amount < 0)
	 * @param amount - amount that the volume is increased
	 */ 
	void increaseVolume(int amount);


private:

	#ifdef SOUND
	vector<Mix_Chunk *> sounds;
	#endif
	
	bool soundsOn;
	int volume;
	
	/**
	 * Initializes sounds
	 * @return true if successful.
	 */
	bool init(int audio_rate, Uint16 audio_format,
              int audio_channels, int audio_buffers);
	
	/**
	 * Loads audio from files to vector sounds
	 */
	void loadAudio();
	
	/**
	 * Plays a sound
	 * @param *sound - pointer to the sound that is played
	 */
	#ifdef SOUND
	void const playSound(Mix_Chunk *sound);
	#endif
	
	/**
	 * Frees all memory allocated for sounds
	 */
	void destroySounds();

};

#endif //_SOUNDS_H_
