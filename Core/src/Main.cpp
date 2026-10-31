#include <iostream>
#include "Project.h"

void CreateNewProjectExample() {
	//Create a new project
	Project p{ 400, 400 };
	p.SetFPS(24.0);
	//NB: dialogue to overwrite
	p.SetFilepath("../Example/MyProject.tc");
	p.Save();
	//p.Render("../Example/MyProject.mp4");
}

void LoadExistingProjectExample() {
	Project p{ "../Example/MyProject.tc" };
}

int main(){
	LoadExistingProjectExample();
	return 0;
}