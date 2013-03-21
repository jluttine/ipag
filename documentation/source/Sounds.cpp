#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include "Sounds.h"

/**
 * Class Sounds.
 * Plays all audio.
 * @author Lasse Hakulinen
 */


/**
 * Constructor.
 * @param rate - audio rate
 * @param format - audio format
 * @param channels - number of channels (mono or stereo)
 * @param buffers - size of buffer
 */
Sounds::Sounds(int rate, Uint16 format, int channels, int buffers){
	#ifdef SOUND
	this->init(rate, format, channels, buffers);
	this->loadAudio();
	this->setVolume(35);
	#endif
}

/**
 * Frees all memory allocated for audio
 */
Sounds::~Sounds(){
	#ifdef SOUND
	Mix_CloseAudio();
	this->destroySounds();
	#endif
}

/**
* Initializes sounds
* @return true if successful.
*/
bool Sounds::init(int rate, Uint16 format, int channels, int buffers){
	#ifdef SOUND
	if (SDL_Init(SDL_INIT_AUDIO) < 0){
		fprintf(stderr, "Could not initialize SDL_mixer: %s\n",
                SDL_GetError());
		        
		return false;
	}

	if (Mix_OpenAudio(rate, format, channels, buffers)){
        fputs("Failed to initialize audio.\n", stderr);
		return false;
	}
	#else
		fputs("No sound.\n", stderr);
	#endif
	
	return true;
}

/**
* Loads audio from files to vector sounds
*/
void Sounds::loadAudio(){
	#ifdef SOUND
	
	this->soundsOn = true;
	this->volume = 0;

	this->sounds.push_back(Mix_LoadWAV("data/click.wav"));
	this->sounds.push_back(Mix_LoadWAV("data/tick.wav"));
	this->sounds.push_back(Mix_LoadWAV("data/cashreg.wav"));
	
	this->sounds.push_back(Mix_LoadWAV("data/shoot1.wav"));
	this->sounds.push_back(Mix_LoadWAV("data/shoot2.wav"));
	this->sounds.push_back(Mix_LoadWAV("data/laser.wav"));
	
	this->sounds.push_back(Mix_LoadWAV("data/explosion1.wav"));
	this->sounds.push_back(Mix_LoadWAV("data/explosion2.wav"));
	this->sounds.push_back(Mix_LoadWAV("data/explosion3.wav"));
	this->sounds.push_back(Mix_LoadWAV("data/explosion4.wav"));
	
	#endif
}

/**
* Plays a sound
* @param *sound - pointer to the sound that is played
*/
#ifdef SOUND
void const Sounds::playSound(Mix_Chunk *sound){
	Mix_PlayChannel(-1, sound, 0);
}
#endif

/**
* Plays a sound of a certain index
* @param index - index of the sound
*/
void const Sounds::playSound(int index){
	#ifdef SOUND
	if (this->soundsOn){
		if (index < 0 || index >= (int)this->sounds.size()){
//			fputs("Sounds::playSound Invalid index\n", stderr);
		}
		else {
			this->playSound(this->sounds[index]);
		}
	}
	#endif
}

/**
* Disables all sounds
*/
void Sounds::disableSounds(){
	
	this->soundsOn = false;
}

/**
* Enables all sounds
*/
void Sounds::enableSounds(){
	
	this->soundsOn = true;
}

/**
* Sets the general volume of the played sounds
* Minimum volume = 0, maximum = 128
* @param volume - new volume
*/
void Sounds::setVolume(int volume){
	if (volume < 0){
		this->volume = 0;
	}
	
	else if (volume > 128){
		this->volume = 128;
	}

	else {
		this->volume = volume;
	}
	
	#ifdef SOUND
	Mix_Volume(-1, volume);
	#endif
}

/**
* Increases the volume (or decreases if amount < 0)
* @param amount - amount that the volume is increased
*/ 
void Sounds::increaseVolume(int amount){

	this->setVolume(this->volume + amount);
}

/**
* Frees all memory allocated for sounds
*/
void Sounds::destroySounds() {
	#ifdef SOUND
	for (int i=0; i < (int)this->sounds.size(); i++) {
		Mix_FreeChunk(this->sounds[i]);
	}
	#endif
}
