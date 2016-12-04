#include "Manager.h"



Manager::Manager()
{
	this->resourcePath = "../res/";
	this->selectedObjectIndex = - 1;
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

void Manager::setSelectedObjectIndex(int selectedObjectIndex) {
	this->selectedObjectIndex = selectedObjectIndex;
}

int Manager::getSelectedObjectIndex() {
	return this->selectedObjectIndex;
}

Asset Manager::getSelectedObject() {
	return this->ObjectList.at(this->selectedObjectIndex);
}

void Manager::removeSelectedObject() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.erase(this->ObjectList.begin() + this->getSelectedObjectIndex());
		this->selectedObjectIndex = -1;
	}
}

void Manager::aumentarObjetoSelecionado() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).aumentar();
	}
}

void Manager::reduzirObjetoSelecionado() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).reduzir();
	}
}

void Manager::moverObjetoSelecionadoDireita() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).moverDireita();
	}
}

void Manager::moverObjetoSelecionadoEsquerda() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).moverEsquerda();
	}
}

void Manager::moverObjetoSelecionadoParaFrente() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).moverParaFrente();
	}
}

void Manager::moverObjetoSelecionadoParaTras() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).moverParaTras();
	}
}

void Manager::rotacionarObjetoSelecionadoParaDireita() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).rotacionarDireita();
	}
}

void Manager::rotacionarObjetoSelecionadoParaEsquerda() {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		this->ObjectList.at(this->selectedObjectIndex).rotacionarEsquerda();
	}
}

void Manager::alterarModeloObjetoSelecionado(Asset a) {
	if (this->selectedObjectIndex >= 0 && this->selectedObjectIndex < this->ObjectList.size()) {
		a.SetPos(this->getSelectedObject().GetPos());
		a.SetRot(glm::vec3(a.getRot().x, this->getSelectedObject().getRot().y, a.getRot().z));
		a.SetScale(this->getSelectedObject().getScale());
		this->ObjectList[this->selectedObjectIndex] = a;
	}
} 

