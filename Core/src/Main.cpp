#include <iostream>
#include "Project.h"

void CreateNewProjectExample() {
	//Create a new project
	Project p{ 400, 400 };
	p.SetName("MyProject");
	p.SetFPS(24.0);
	//NB: dialogue to overwrite
	p.SetFilepath("../Example/");
	p.Save();
	//p.Render("../Example/MyProject.mp4");
}

void LoadExistingProjectExample() {
	Project p{ "../Example/MyProject.tc" };
	p.PrintProperties();
}

int main(){
	LoadExistingProjectExample();
	//CreateNewProjectExample();
	return 0;
}