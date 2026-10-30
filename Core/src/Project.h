#pragma once
#include <fstream>
#include "NotImplemented.h"

#include "ITrack.h"
class Project {
public:
	std::string Name{};
	double FPS{};
	int WIDTH{};
	int HEIGHT{};
	std::string Filepath{};
	//mediapool
	//timeline

	//if the project already exists somewhere
	Project(std::string path, int width, int height) : WIDTH(width), HEIGHT(height) {
		Load(path);
	}

	//Otherwise
	Project(int width, int height) : WIDTH(width), HEIGHT(height) {

	}

	void Render(std::string output) {
		throw NotImplemented();
	}

	void Save() {
		throw NotImplemented();
	}

	void SetFPS(double fps) {
		FPS = { fps };
	}
private:
	//TODO: return error codes
	void Load(std::string path) {
		throw NotImplemented();
	}
};