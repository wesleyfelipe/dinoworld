#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <GL/glew.h>
#include "Asset.h"
#include "camera.h"
#include <vector>

class Manager
{
public:
	Manager();
	~Manager();

	std::string resourcePath;
	std::vector<Asset> ObjectList;
	GLint currentAssetIndex;

	void CreateObject(std::string meshPath, std::string diffPath, std::string specPath, Shader* shader);
	Asset BuildObject(std::string meshPath, std::string diffPath, std::string specPath, Shader* shader);

	void DrawObjects(const Camera& camera);

	int getSelectedObject();
	void setSelectedObject(int selectedObject);

private:
	int selectedObject;
};

#endif