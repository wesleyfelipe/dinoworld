#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <GL/glew.h>
#include <string>
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

class Asset
{
public:
	Asset();
	~Asset();

	GLuint id;
	std::string assetName;

	void SetMesh(const std::string& meshPath);
	void SetShader(Shader* shader);

	glm::vec3 GetPos();
	glm::vec3 getRot();
	glm::vec3 getScale();

	//Transform Functions
	void SetPos(glm::vec3 pos);
	void SetRot(glm::vec3 rot);
	void SetScale(glm::vec3 scale);

	void SetMaterial(std::string diffPath, std::string specPath);

	void Draw(const Camera& camera);

	void aumentar();
	void reduzir();
	void moverDireita();
	void moverEsquerda();
	void moverParaFrente();
	void moverParaTras();
	void rotacionarDireita();
	void rotacionarEsquerda();

protected:
private:
	Mesh* m_mesh;
	Shader* m_shader;
	Texture* m_diffuse;
	Texture* m_specular;
	Transform m_transform;

	void alterarEscala(float a);
	void mover(float x1, float x2, float x3);
	void rotacionar(float a);
};

#endif