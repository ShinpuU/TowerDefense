#pragma once
#include <SFML/Audio.hpp>
#include <map>


using namespace sf;
using namespace std;



class MSound {

	map<string, SoundBuffer* > sounds;
	sf::Music music;
	sf::Sound sound;

public:



	MSound() {
		
		music.openFromFile("assets/music.wav");

		sf::SoundBuffer* clickBuffer = new SoundBuffer();
		clickBuffer->loadFromFile("assets/clickBtn.wav");


		sf::SoundBuffer* explosionBuffer = new SoundBuffer();
		explosionBuffer->loadFromFile("assets/explosion.wav");
		

		sounds.insert(pair<string, SoundBuffer*>("click", clickBuffer));
		sounds.insert(pair<string, SoundBuffer*>("explosion", explosionBuffer));
	}

	void playMusic() {
		music.stop();
		music.play();
		music.setLoop(true);
	}

	void playSound(string key) {
		//printf("%f \n", *sounds[key].getDuration().asSeconds());
		sound.setBuffer(*sounds[key]);
		sound.play();
	}

	static MSound& get() {
		static MSound INSTANCE;
		return INSTANCE;
	}
	
};