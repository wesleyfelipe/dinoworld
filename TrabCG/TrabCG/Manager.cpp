#include "Manager.h"



Manager::Manager()
{
	this->resourcePath = "../res/";
}


Manager::~Manager()
{
}

//Create an object
void Manager::CreateObject(std::string meshPath, std::string diffPath, std::string specPath, Shader* shader)
{
	this->ObjectList.push_back(BuildObject(meshPath, diffPath, specPath, shader));
}

Asset Manager::BuildObject(std::string meshPath, std::string diffPath, std::string specPath, Shader* shader)
{
	Asset tempAsset;

	tempAsset.id = ObjectList.size();

	//Set Mesh
	tempAsset.SetMesh(meshPath);

	//Set Shader
	tempAsset.SetShader(shader);

	//Set Material
	tempAsset.SetMaterial(diffPath, specPath);

	return tempAsset;
}

void Manager::DrawObjects(const Camera& camera)
{
	for each (Asset object in this->ObjectList)
	{
		object.Draw(camera);
	}
}
