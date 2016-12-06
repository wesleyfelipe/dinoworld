#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <GL/glew.h>
#include "Object.h"
#include "camera.h"
#include <vector>

class Manager
{
public:
	Manager();
	~Manager();

	std::string resourcePath;
	std::vector<Object> ObjectList;
	GLint currentAssetIndex;

	void CreateObject(std::string meshPath, std::string diffPath, std::string specPath, Shader* shader);
	Object BuildObject(std::string meshPath, std::string diffPath, std::string specPath, Shader* shader);

	void DrawObjects(const Camera& camera);

	int getSelectedObjectIndex();
	void setSelectedObjectIndex(int selectedObjectIndex);

	Object getSelectedObject();

	void removeSelectedObject();

	void aumentarObjetoSelecionado();
	void reduzirObjetoSelecionado();
	void moverObjetoSelecionadoDireita();
	void moverObjetoSelecionadoEsquerda();
	void moverObjetoSelecionadoParaFrente();
	void moverObjetoSelecionadoParaTras();
	void rotacionarObjetoSelecionadoParaDireita();
	void rotacionarObjetoSelecionadoParaEsquerda();
	void alterarModeloObjetoSelecionado(Object a);

private:
	int selectedObjectIndex;
};

#endif