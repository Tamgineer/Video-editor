#pragma once
#include <string>
class ITrack
{
public:
	std::string Name{};
	int WIDTH{};
	int HEIGHT{};
	double DURATION{};
	double s_timestamp{};
	double e_timestamp{};
	double fps{};

	ITrack(std::string name) : Name(name) {}

	//this is a dummy function, in the future
	//we'll make it return an image for our frame
	//NB: Oh and make sure it's virtual
	void Display() {

	}

	void Split() {
		//TODO:: implement
	}
private:
};


/*
Things to consider:
- Track should only concern itself with outputing an RGB output.
- Tracks will have a width and a height
- Tracks can be transformed (translate, rotate and scaled)
- Tracks have a length
- Tracks store it's beginning and ending timestamps.
- Tracks store information about FPS.
- Tracks can be attached to a transition
- Tracks can have a visual effect?
*/