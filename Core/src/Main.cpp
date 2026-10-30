#include <iostream>
#include "Project.h"

int main(){
	//Create a new project
	Project p{400, 400};
	p.SetFPS(24.0);
	p.Save();
	p.Render("../Example/MyProject.txt");
	std::cout << "hello world\n";
	return 0;
}